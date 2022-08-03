#include "dialog.h"
#include "ui_dialog.h"
#include"icon_help.h"
#include<QPainter>
#include <QMouseEvent>
#include <QFontDatabase>
#include <QDebug>
#include<QTimer>
#include "lunarcalendarwidget.h"
#include <excpt.h>



#pragma execution_character_set("utf-8")



//主界面的构造函数，包括对界面内各个部件元素的初始化构造，以及通信串口、辅助线程的构建
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    aaa=0;           //参数设置提示功能部分使用的一个条件变量

    bigData.AorB=0;
    times=0;

    num_range_direction=-1;
    use_patient=0;
    time_data_str=0;
    speed_intime1=0;
    speed_intime2=0;
    speed_intime3=0;

    test_category=0;
    base_time=0.01;

    ongoing=0;
    direction_btn=0;
    force_btn=0;
    speed_btn=0;
    range_btn=0;

    is_stop=0;
    recv_start=0;
    recv_num=0;
    last_buff[0]=0x00;
    is_train=0;
    temp_test=0;

    train_category_id=0;
    test_category_id=0;

    ui->setupUi(this);
    //showFullScreen();
    this->initForm();
    this->initForm_user();
    this->initForm_test_train();
    this->initForm_history();
    this->initForm_play();

    ui->widget_15->hide();
    ui->widget_14->hide();
    ui->widget_16->hide();

    /*
    ui->pushButton_4->setFixedSize(70,60);
    ui->pushButton_5->setFixedSize(70,60);
    */

    timerset = new QTimer;  //初始化定时器
    data_time=new QTimer;
    connect(data_time,SIGNAL(timeout()),this,SLOT(time_rec()));


    TimeRecord = new QTime(0,2,30); //初始化时间
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
    connect(timerset,SIGNAL(timeout()),this,SLOT(time_minus()));

    //更改界面元素
    ui->label_25->setStyleSheet("font-family:HGHP_CNKI;font-size:26pt;color: rgb(0, 119, 170)");
    ui->label_20->setStyleSheet("font-family:HGHP_CNKI;font-size:26pt;color: rgb(0, 119, 170)");
    ui->label_21->setStyleSheet("font-family:HGHP_CNKI;font-size:26pt;color: rgb(0, 119, 170)");
    ui->label_22->setStyleSheet("font-family:HGHP_CNKI;font-size:26pt;color: rgb(0, 119, 170)");
    ui->label_23->setStyleSheet("font-family:HGHP_CNKI;font-size:26pt;color: rgb(0, 119, 170)");
    //去窗口边框
            setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
            setAttribute(Qt::WA_TranslucentBackground);
    //时间显示
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(closemention()));

    direction1= new QTimer(this);
    connect(direction1,SIGNAL(timeout()),this,SLOT(warmest_ment()));


    this->hide();
     /*
     QPalette pa;
     pa.setColor(QPalette::WindowText,Qt::red);
     ui->label_13->setPalette(pa);
     */

    ui->widget_cover->hide();
    ui->widget_run->hide();
    ui->widget_18->hide();




     QList<QWidget*> w_u;
     w_u<<ui->w_user1<<ui->w_user2<<ui->w_user3<<ui->w_user4<<ui->w_user5;
     for(int i=0;i<5;i++)
     {
         w_u[i]->setParent(this);
         w_u[i]->hide();
     }


    b_direction<<ui->chiraopian<<ui->qushen<<ui->huizhuan<<ui->ouhe;
    b_speed<<ui->slow<<ui->medium<<ui->fast;
    b_force<<ui->slow_2<<ui->medium_2<<ui->fast_2;
    b_range<<ui->range_s<<ui->range_m<<ui->range_b;
    for(int i=0;i<b_speed.count();i++)
    {
        connect(b_speed[i], SIGNAL(clicked(bool)), this, SLOT(button_SpeedChoice()));
    }
    for(int i=0;i<b_direction.count();i++)
    {
        connect(b_direction[i], SIGNAL(clicked(bool)), this, SLOT(button_DirectionChoice()));
    }
    for(int i=0;i<b_force.count();i++)
    {
        connect(b_force[i], SIGNAL(clicked(bool)), this, SLOT(button_ForceChoice()));
    }
    for(int i=0;i<b_range.count();i++)
    {
        connect(b_range[i], SIGNAL(clicked(bool)), this, SLOT(button_RangeChoice()));
    }

    arrow<<ui->label_arrow1<<ui->label_arrow2<<ui->label_arrow3<<ui->label_arrow4;

    fontId = QFontDatabase::addApplicationFont(":/new/prefix1/fontawesome-webfont.ttf");
     fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
     QFont font;
     font.setFamily(fontFamilies.at(0));

     ui->label_26->setFont(font);
    ui->label_26->setText(QChar(0xf08b));
     ui->label_26->setContentsMargins(0,0,0,0);
     ui->label_26->setStyleSheet("color: rgb(77, 212, 183);font-size : 40px");
  //QRect textRect = QRect(10, 0, ui->label_5->width(),  ui->label_5->width());
    // ui->label_17->setGeometry(rect().x()+40, rect().y()+20,30, 40);
  //chanel1->setParent(this);
     ui->label_no1->setGeometry(rect().x()+42, rect().y()+170,230, 230);
      ui->label_no1->setFont(font);
     ui->label_no1->setText(QChar(0xf05e));
      ui->label_no1->setContentsMargins(0,0,0,0);
      ui->label_no1->setStyleSheet("color:rgb(0, 125, 180,80%);font-size : 230px");

      ui->label_no2->setGeometry(rect().x()+385, rect().y()+215,260, 260);
       ui->label_no2->setFont(font);
      ui->label_no2->setText(QChar(0xf05e));
       ui->label_no2->setContentsMargins(0,0,0,0);
       ui->label_no2->setStyleSheet("color:rgb(0, 125, 180,80%);font-size : 260px");

       ui->label_no3->setGeometry(rect().x()+778, rect().y()+92,200, 200);
        ui->label_no3->setFont(font);
       ui->label_no3->setText(QChar(0xf05e));
        ui->label_no3->setContentsMargins(0,0,0,0);
        ui->label_no3->setStyleSheet("color:rgb(0, 125, 180,80%);font-size : 200px");

        ui->label_no4->setGeometry(rect().x()+778, rect().y()+380,200, 200);
         ui->label_no4->setFont(font);
        ui->label_no4->setText(QChar(0xf05e));
         ui->label_no4->setContentsMargins(0,0,0,0);
         ui->label_no4->setStyleSheet("color:rgb(0, 125, 180,80%);font-size : 200px");



    ui->label_arrow1->setGeometry(rect().x()+22, rect().y()+100,32, 32);
    ui->label_arrow1->setFont(font);
    ui->label_arrow1->setText(QChar(0xf054));
    ui->label_arrow1->setContentsMargins(0,0,0,0);
    ui->label_arrow1->setStyleSheet("color:rgb(1, 212, 153);font-size : 32px");


    ui->label_arrow2->setGeometry(rect().x()+22, rect().y()+182,32, 32);
    ui->label_arrow2->setFont(font);
    ui->label_arrow2->setText(QChar(0xf054));
    ui->label_arrow2->setContentsMargins(0,0,0,0);
    ui->label_arrow2->setStyleSheet("color:rgb(1, 212, 153);font-size : 32px");


    ui->label_arrow3->setGeometry(rect().x()+22, rect().y()+266,32, 32);
    ui->label_arrow3->setFont(font);
    ui->label_arrow3->setText(QChar(0xf054));
    ui->label_arrow3->setContentsMargins(0,0,0,0);
    ui->label_arrow3->setStyleSheet("color:rgb(1, 212, 153);font-size : 32px");

    ui->label_arrow4->setGeometry(rect().x()+22, rect().y()+346,32, 32);
    ui->label_arrow4->setFont(font);
    ui->label_arrow4->setText(QChar(0xf054));
    ui->label_arrow4->setContentsMargins(0,0,0,0);
    ui->label_arrow4->setStyleSheet("color:rgb(1, 212, 153);font-size : 32px");

    ui->label_no1->hide();
    ui->label_no2->hide();
    ui->label_no3->hide();
    ui->label_no4->hide();
    ui->label_nodire->hide();
    ui->label_noforce->hide();
    ui->label_norange->hide();
    ui->label_nospe->hide();
    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();

    ui->time_add->setFont(font);
    ui->time_add->setText(QChar(0xf0fe));
    ui->time_add->setStyleSheet("font-size : 58px");
    ui->time_minus->setFont(font);
    ui->time_minus->setText(QChar(0xf146));
    ui->time_minus->setStyleSheet("font-size : 58px");


    //测试或训练结果图表显示
    ui->widget_12->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_12->load(QUrl("D:/Qt_pro/login/htmlE/line-simple.html"));
    ui->widget_12->hide();
    ui->widget_13->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_13->load(QUrl("D:/Qt_pro/login/htmlE/line-function.html"));
    ui->widget_13->hide();
    ui->widget_17->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_17->load(QUrl("D:/Qt_pro/login/htmlE/area-simple.html"));
    ui->widget_17->hide();
    ui->widget_19->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_19->load(QUrl("D:/Qt_pro/login/htmlE/dengzhang.html"));
    ui->widget_19->hide();
    ui->widget_20->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_20->load(QUrl("D:/Qt_pro/login/htmlE/dengchang.html"));
    ui->widget_20->hide();


    ui->lunarC=new LunarCalendarWidget();

//ui->lunarC->setStyleSheet("LunarCalendarWidget#lunarC{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
   // ui->widget_12->setContextMenuPolicy(Qt::NoContextMenu);
    //ui->widget_12->load(QUrl());
    //ui->widget_13->load(QUrl());
    //ui->widget_17->load(QUrl());

/*
    ui->widget_12->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_12->load(QUrl("C:/htmlE/line-simple.html"));
    ui->widget_12->hide();
    ui->widget_13->setContextMenuPolicy(Qt::NoContextMenu);
    ui->widget_13->load(QUrl("C:/htmlE/line-function.html"));
    ui->widget_13->hide();
    */
//串口声明及串口属性设置
    serial=new QSerialPort();
    //串口名称
    serial->setPortName("COM3");
    //设置波特率
    serial->setBaudRate(230400);
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(serial,&QSerialPort::readyRead,this,&Dialog::serial_recv);//连接串口接受函数和触发信号

/*
    serial1=new QSerialPort();
    //串口名称
    serial1->setPortName("COM3");
    //设置波特率
    serial1->setBaudRate(230400);
    //设置数据位数
    serial1->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial1->setParity(QSerialPort::NoParity);
    //设置停止位
    serial1->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial1->setFlowControl(QSerialPort::NoFlowControl);
    //打开串口
    if(!serial1->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口失败";
        return ;
    }
    else
    {
         qDebug()<<"打开串口成功";
    }

*/
    // 创建新线程用来分担存储负载，弥补存储与串口接收之间的冲突
    myThrd = new MyThread();
    // 该线程结束时销毁
    connect(myThrd, SIGNAL(&QThread::finished), this, SLOT(&QObject::deleteLater));

    // 启动该线程
    myThrd->start();

    //sql->query.exec("insert into train_data values("+bigData.data1.F[0][0]+")");


}


//析构函数，包含对界面对象内各成员空间的释放
Dialog::~Dialog()
{

    //myThrd->quit();
    myThrd->terminate();
    myThrd->wait();

    delete ui;
    delete serial;
    delete timer2 ;
    delete timerset;
    delete TimeRecord;



}


void Dialog::initForm()
{
    ui->nbt1->setFixedSize(220,70);
    ui->nbt2->setFixedSize(220,70);
    ui->nbt3->setFixedSize(220,70);
    ui->nbt4->setFixedSize(220,70);
    ui->nbt5->setFixedSize(220,70);
    ui->nbt6->setFixedSize(220,70);

    quint32 size = 55;
    quint32 pixWidth = 55;
    quint32 pixHeight = 55;
    QList<int> icons;

    //左侧页面选择框图标设置  在http://www.fontawesome.com.cn/icons/查找图标编号
    icons << 0xf0c0 << 0xf0f1 << 0xf1d9 << 0xf073 <<0xf11b<<0xf002;
    btn1<<ui->nbt1<<ui->nbt2<<ui->nbt3<<ui->nbt4<<ui->nbt5<<ui->nbt6;
    QColor normalBgColor = QColor("#183e61");
    QColor hoverBgColor = QColor("#187294");
    QColor checkBgColor = QColor("#2D9191");
    QColor normalTextColor = QColor("#FFFFFF");
    QColor hoverTextColor = QColor("#FFFFFF");
    QColor checkTextColor = QColor("#FFFFFF");
    for(int i=0;i<btn1.count();i++)
    {
            New_Button *btn = btn1.at(i);
            btn->setPaddingLeft(37);
            btn->setLineSpace(0);
            btn->setLineWidth(14);
            btn->setLineColor(QColor(255, 107, 107));
            btn->setShowTriangle(true);

            btn->setShowIcon(true);
            btn->setIconSpace(23);
            btn->setIconSize(QSize(26, 26));

            //分开设置图标
            int icon = icons.at(i);
            QPixmap iconNormal = IconHelper::getPixmap(normalTextColor.name(), icon, size, pixWidth, pixHeight);
            QPixmap iconHover = IconHelper::getPixmap(hoverTextColor.name(), icon, size, pixWidth, pixHeight);
            QPixmap iconCheck = IconHelper::getPixmap(checkTextColor.name(), icon, size, pixWidth, pixHeight);

            btn->setIconNormal(iconNormal);
            btn->setIconHover(iconHover);
            btn->setIconCheck(iconCheck);

            btn->setNormalBgColor(normalBgColor);
            btn->setHoverBgColor(hoverBgColor);
            btn->setCheckBgColor(checkBgColor);
            btn->setNormalTextColor(normalTextColor);
            btn->setHoverTextColor(hoverTextColor);
            btn->setCheckTextColor(checkTextColor);


            connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick2()));
        }
    //ui->nbt1->setChecked(true);
    ui->num_1->hide();
    ui->num_2->hide();
    ui->num_3->hide();
    ui->pushButton_9->hide();
    ui->mention_regis->hide();
}





void Dialog::initForm_user()
{
    ui->userid->installEventFilter(this);
    num<<ui->pushButton_00<<ui->pushButton_01<<ui->pushButton_02<<ui->pushButton_03<<ui->pushButton_04<<ui->pushButton_05<<ui->pushButton_06<<ui->pushButton_07<<ui->pushButton_08<<ui->pushButton_09;
    for(int i=0;i<num.count();i++)
    {
        connect(num[i], SIGNAL(clicked(bool)), this, SLOT(dnum_insert()));
    }
}

void Dialog::dnum_insert()
{
    int temp;
    QPushButton *b = (QPushButton *)sender();
    for(int i=0;i<10;i++)
    {
        if(b==num[i])
        {
            temp=i;
        }
    }
       QString s = QString::number(temp);
       ui->userid->insert(s);
}


bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress&&(obj==ui->userid))
    {
        ui->widget_18->show();
        return true;
    }

    return QWidget::eventFilter(obj,event);


}

void Dialog::initForm_test_train()
{
//font: 70pt "华光淡古印_CNKI";
//color: rgb(102, 113, 161);

    ui->widget_4->hide();

    fontId = QFontDatabase::addApplicationFont(":/new/prefix1/fontawesome-webfont.ttf");
    fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies.at(0));

    ui->finger->setFont(font);
    ui->finger->setText(QChar(0xf0a4));
    ui->finger->setStyleSheet("color:rgb(0, 85, 127);font-size : 40px");
    ui->finger->hide();
    ui->weiwancheng->hide();

    ui->label_24->setFont(font);
    ui->label_24->setText(QChar(0xf07d));
    ui->label_24->setStyleSheet("color:rgb(102, 113, 161);font-size : 54px");
 //QRect textRect = QRect(10, 0, ui->label_5->width(),  ui->label_5->width());
    ui->label_13->setGeometry(rect().x()+40, rect().y()+7,30, 40);
 //chanel1->setParent(this);

     ui->label_13->setFont(font);
    ui->label_13->setText(QChar(0xf046));
     ui->label_13->setContentsMargins(0,0,0,0);
     ui->label_13->setStyleSheet("color:rgb(0, 160, 230);font-size : 30px");
     ui->label_14->setGeometry(rect().x()+77, rect().y()+12,167, 30);
     ui->label_14->setStyleSheet("color:rgb(0, 160, 230);font-family:SimHei;font-size : 28px");
// ui->label_13->setStyleSheet("font-size : 30px");
     ui->label_15->setGeometry(rect().x()+25, rect().y()+6,40, 40);
     ui->label_15->setFont(font);
    ui->label_15->setText(QChar(0xf085));
    ui->label_15->setStyleSheet("color:rgb(0, 160, 230);font-size : 30px");
    ui->label_16->setGeometry(rect().x()+22, rect().y()+11,155, 30);
    ui->label_16->setStyleSheet("color:rgb(0, 160, 230);font-family:SimHei;font-size : 28px");

    ui->label_17->setGeometry(rect().x()+280, rect().y()+260,60, 60);


     ui->label_17->setFont(font);
    ui->label_17->setText(QChar(0xf061));
     ui->label_17->setContentsMargins(0,0,0,0);
     //0, 160, 230
     ui->label_17->setStyleSheet("color:rgb(0, 160, 230);font-size : 60px");
    ui->label_17->hide();

      ui->label_18->setGeometry(rect().x()+660, rect().y()+195,55, 55);
     ui->label_18->setFont(font);
    ui->label_18->setText(QChar(0xf061));
     ui->label_18->setContentsMargins(0,0,0,0);
     ui->label_18->setStyleSheet("color:rgb(0, 160, 230);font-size : 55px");
     ui->label_18->hide();

      ui->label_19->setGeometry(rect().x()+660, rect().y()+395,55, 55);
     ui->label_19->setFont(font);
    ui->label_19->setText(QChar(0xf061));
     ui->label_19->setContentsMargins(0,0,0,0);
     ui->label_19->setStyleSheet("color:rgb(0, 160, 230);font-size : 55px");
    ui->label_19->hide();

   ui->range_change1->setFont(font);
   ui->range_change1->setText(QChar(0xf056));
   ui->range_change1->setStyleSheet("font-size : 55px");
   ui->range_change1->hide();
   ui->range_change2->setFont(font);
   ui->range_change2->setText(QChar(0xf055));
   ui->range_change2->setStyleSheet("font-size : 55px");
   ui->range_change2->hide();
   ui->range_change3->setFont(font);
   ui->range_change3->setText(QChar(0xf056));
   ui->range_change3->setStyleSheet("font-size : 55px");
   ui->range_change3->hide();
   ui->range_change4->setFont(font);
   ui->range_change4->setText(QChar(0xf055));
   ui->range_change4->setStyleSheet("font-size : 55px");
   ui->range_change4->hide();
   ui->speed_change1->setFont(font);
   ui->speed_change1->setText(QChar(0xf056));
   ui->speed_change1->setStyleSheet("font-size : 55px");
   ui->speed_change1->hide();
   ui->speed_change2->setFont(font);
   ui->speed_change2->setText(QChar(0xf055));
   ui->speed_change2->setStyleSheet("font-size : 55px");
   ui->speed_change2->hide();
   ui->force_change1->setFont(font);
   ui->force_change1->setText(QChar(0xf056));
   ui->force_change1->setStyleSheet("font-size : 55px");
   ui->force_change1->hide();
   ui->force_change2->setFont(font);
   ui->force_change2->setText(QChar(0xf055));
   ui->force_change2->setStyleSheet("font-size : 55px");
   ui->force_change2->hide();




     btn_test<<ui->pushButton_1<<ui->pushButton_2<<ui->pushButton_3<<ui->pushButton_4<<ui->pushButton_5;
    for (int i = 0; i < btn_test.count(); i++) {
     QPushButton *btn = btn_test.at(i);

     //btn->setStyleSheet("color:rgb(0, 160, 230);font-family:SimHei;font-size : 20px");
     connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick_test()));



     QFont font;
     font.setFamily(fontFamilies.at(0));
  //QRect textRect = QRect(10, 0, ui->label_5->width(),  ui->label_5->width());
     //ui->label_13->setGeometry(rect().x()+40, rect().y()+25,30, 40);
  //chanel1->setParent(this);
      //sett(font,fontFamilies,ui->label_p,0xf05d);
     /*
      ui->label_p->setFont(font);
      ui->label_p->setText(QChar(0xf10c));
      ui->label_p->setContentsMargins(0,0,0,0);
      ui->label_p->setStyleSheet("color:rgb(141, 141, 141);font-size : 36px");
      ui->label_pp->setFont(font);
      ui->label_pp->setText(QChar(0xf05d));
      ui->label_pp->setContentsMargins(0,0,0,0);
      ui->label_pp->setStyleSheet("color:rgb(56,232,83);font-size : 36px");
      ui->label_pp->hide();


*/
     ui->check_1->setFont(font);
     ui->check_1->setText(QChar(0xf05d));
     ui->check_1->setContentsMargins(0,0,0,0);
     ui->check_1->setStyleSheet("color:rgb(56,232,83);font-size : 38px");
     ui->check_1->hide();
     ui->check_2->setFont(font);
     ui->check_2->setText(QChar(0xf05d));
     ui->check_2->setContentsMargins(0,0,0,0);
     ui->check_2->setStyleSheet("color:rgb(56,232,83);font-size : 38px");
     ui->check_2->hide();
     ui->check_3->setFont(font);
     ui->check_3->setText(QChar(0xf05d));
     ui->check_3->setContentsMargins(0,0,0,0);
     ui->check_3->setStyleSheet("color:rgb(56,232,83);font-size : 38px");
     ui->check_3->hide();


     ui->pushButton_8->hide();


 }

}


void Dialog::initForm_train()
{
    ui->label_14->setText("选择训练类别");
    ui->pushButton_1->setText("C P M 训练");

    ui->pushButton_2->setText("等速肌力训练");

    ui->pushButton_3->setText("等张肌力训练");
    ui->pushButton_4->setText("等长肌力训练");
    ui->pushButton_5->hide();
    ui->label_25->setText("训练时间");
    ui->pushButton_6->setText("开始训练");
}

void Dialog::initForm_test()
{
    ui->label_14->setText("选择测试类别");
    ui->pushButton_1->setText("活动范围测试");
    ui->pushButton_2->setText("等速肌力测试");
    ui->pushButton_3->setText("等张肌力测试");
    ui->pushButton_4->setText("等长肌力测试");
    ui->pushButton_5->setText("握力测试");
    ui->pushButton_5->show();
    ui->label_25->setText("测试时间");
    ui->pushButton_6->setText("开始测试");
}

void Dialog::initForm_history()
{

}


void Dialog::initForm_play()
{

}
/*
void sett(const QFont& font,QStringList fontFamilies,QLabel p,int cha)
{
    font.setFamily(fontFamilies.at(0));
    p->setFont(font);
    p->setText(QChar(cha));
    p->setContentsMargins(0,0,0,0);
    p->setStyleSheet("color:rgb(108, 108, 108);font-size : 30px");
}
*/



void Dialog::range_init()
{
        test_set_zero();
    temp_test=1;
    ui->num_2->setText("1");
    ui->num_2->show();

    ui->chiraopian->show();
    ui->qushen->show();
    ui->huizhuan->show();
    ui->ouhe->show();

    ui->widget_speed1->hide();
    ui->widget_force1->hide();
    ui->widget_10->hide();

    num_range_direction=-1;

    ui->label_r_4->show();
    ui->label_r_5->hide();
    ui->label_r_6->hide();
    ui->label_r_7->hide();

    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();


    ui->label_nodire->hide();
    ui->label_noforce->show();
    ui->label_norange->show();
    ui->label_nospe->show();

    ui->label_no1->hide();
    ui->label_no2->show();
    ui->label_no3->show();
    ui->label_no4->show();


    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();



    if(widgett[0]==0)
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[0]=1;
    }
    if(widgett[1]==1)
    {
        ui->widget_6->setStyleSheet("QWidget#widget_6{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[1]=0;
    }
    if(widgett[2]==1)
    {
         ui->widget_8->setStyleSheet("QWidget#widget_8{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[2]=0;
    }
    if(widgett[3]==1)
    {
        ui->widget_9->setStyleSheet("QWidget#widget_9{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[3]=0;
    }


    /*
    for(int i=0;i<3;i++)
    {
        b_direction[i]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");

    }
     for(int i=0;i<5;i++)
     {
         q[i]->hide();
     }
     */





     ui->widget_4->show();
     // QList<QWidget*> q;
    //q<<ui->widget_c<<ui->widget_r<<ui->widget_s<<ui->widget_w<<ui->widget_z;
}

void Dialog::speed_init()
{
    test_set_zero();
    ui->speed_change1->hide();
    ui->speed_change2->hide();
    ui->range_change1->hide();
    ui->range_change2->hide();
    ui->range_change3->hide();
    ui->range_change4->hide();

    temp_test=0;

    ui->num_1->setText("1");
    ui->num_1->show();
    ui->num_2->setText("2");
    ui->num_2->show();
    ui->num_3->setText("3");
    ui->num_3->show();

    ui->slow->show();

    ui->chiraopian->show();
    ui->qushen->show();
    ui->huizhuan->show();
    ui->ouhe->hide();

    ui->widget_speed1->show();
    ui->widget_force1->hide();
    ui->widget_10->show();
   // ui->gaugepanel->show();

    ui->label_r_4->show();
    ui->label_r_5->show();
    ui->label_r_6->show();
    ui->label_r_7->hide();

    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();


    ui->label_nodire->hide();
    ui->label_noforce->show();
    ui->label_norange->hide();
    ui->label_nospe->hide();

    ui->label_no1->hide();
    ui->label_no2->hide();
    ui->label_no3->hide();
    ui->label_no4->show();

    ui->label_19->hide();

    if(widgett[0]==0)
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[0]=1;
    }
    if(widgett[1]==0)
    {
        ui->widget_6->setStyleSheet("QWidget#widget_6{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[1]=1;
    }
    if(widgett[2]==0)
    {
        ui->widget_8->setStyleSheet("QWidget#widget_8{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[2]=1;
    }
    if(widgett[3]==1)
    {
        ui->widget_9->setStyleSheet("QWidget#widget_9{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[3]=0;
    }


     ui->label_17->show();
     ui->label_17->show();
     ui->label_18->show();
    /*
    num_range_direction=0;
    QFont font;
    font.setFamily(fontFamilies.at(0));
 //QRect textRect = QRect(10, 0, ui->label_5->width(),  ui->label_5->width());
    //ui->label_13->setGeometry(rect().x()+40, rect().y()+25,30, 40);
 //chanel1->setParent(this);
     //sett(font,fontFamilies,ui->label_p,0xf05d);

    ui->label_p->setFont(font);
    ui->label_pp->setFont(font);
    ui->label_p_2->setFont(font);
    ui->label_p_22->setFont(font);
    ui->label_p_3->setFont(font);
    ui->label_p_33->setFont(font);
    ui->label_p->setText(QChar(0xf10c));
    ui->label_p_2->setText(QChar(0xf10c));
    ui->label_p_3->setText(QChar(0xf10c));
    ui->label_p->setContentsMargins(0,0,0,0);
    ui->label_p_2->setContentsMargins(0,0,0,0);
    ui->label_p_3->setContentsMargins(0,0,0,0);
    ui->label_p->setStyleSheet("color:rgb(141, 141, 141);font-size : 36px");
    ui->label_p_2->setStyleSheet("color:rgb(141, 141, 141);font-size : 36px");
    ui->label_p_3->setStyleSheet("color:rgb(141, 141, 141);font-size : 36px");


    ui->label_pp->setText(QChar(0xf05d));
    ui->label_p_22->setText(QChar(0xf05d));
    ui->label_p_33->setText(QChar(0xf05d));
    ui->label_pp->setContentsMargins(0,0,0,0);
    ui->label_p_22->setContentsMargins(0,0,0,0);
    ui->label_p_33->setContentsMargins(0,0,0,0);
    ui->label_pp->setStyleSheet("color:rgb(56,232,83);font-size : 36px");
    ui->label_p_22->setStyleSheet("color:rgb(56,232,83);font-size : 36px");
    ui->label_p_33->setStyleSheet("color:rgb(56,232,83);font-size : 36px");
    ui->label_pp->hide();
    ui->label_p_22->hide();
    ui->label_p_33->hide();

     ui->label_p->show();
     ui->label_r_1->show();
    ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
     QList<QWidget*> q;
     q<<ui->widget_c<<ui->widget_r<<ui->widget_s<<ui->widget_w<<ui->widget_z;
     for(int i=0;i<5;i++)
     {
         q[i]->hide();
     }
     ui->widget_r->show();
     */
     ui->widget_4->show();
}

void Dialog::z_init()
{
    test_set_zero();
    ui->force_change1->hide();
    ui->force_change2->hide();
    ui->range_change1->hide();
    ui->range_change2->hide();
    ui->range_change3->hide();
    ui->range_change4->hide();

    temp_test=0;
    ui->num_1->setText("1");
    ui->num_1->show();
    ui->num_2->setText("2");
    ui->num_2->show();
    ui->num_3->setText("3");
    ui->num_3->show();


    ui->chiraopian->show();
    ui->qushen->show();
    ui->huizhuan->show();
    ui->ouhe->hide();

    ui->widget_speed1->hide();
    ui->widget_force1->show();
    ui->widget_10->show();
    //ui->gaugepanel->show();

    ui->label_r_4->show();
    ui->label_r_5->show();
    ui->label_r_6->hide();
    ui->label_r_7->show();

    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();


    ui->label_nodire->hide();
    ui->label_noforce->hide();
    ui->label_norange->hide();
    ui->label_nospe->show();

    ui->label_no1->hide();
    ui->label_no2->hide();
    ui->label_no3->show();
    ui->label_no4->hide();


    ui->label_18->hide();

    if(widgett[0]==0)
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[0]=1;
    }
    if(widgett[1]==0)
    {
        ui->widget_6->setStyleSheet("QWidget#widget_6{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[1]=1;
    }
    if(widgett[2]==1)
    {
        ui->widget_8->setStyleSheet("QWidget#widget_8{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[2]=0;
    }
    if(widgett[3]==0)
    {
        ui->widget_9->setStyleSheet("QWidget#widget_9{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[3]=1;
    }



    ui->label_17->show();
    ui->label_19->show();

    ui->widget_4->show();
}

void Dialog::c_init()
{
    test_set_zero();
    ui->range_change1->hide();
    ui->range_change2->hide();
    ui->range_change3->hide();
    ui->range_change4->hide();

    temp_test=0;
    ui->num_1->setText("1");
    ui->num_1->show();
    ui->num_2->setText("2");
    ui->num_2->show();
    ui->num_3->hide();

    ui->chiraopian->show();
    ui->qushen->show();
    ui->huizhuan->show();
    ui->ouhe->hide();

    ui->widget_speed1->hide();
    ui->widget_force1->hide();
    ui->widget_10->show();

    //ui->gaugepanel->show();

    ui->label_r_4->show();
    ui->label_r_5->show();
    ui->label_r_6->hide();
    ui->label_r_7->hide();

    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();

    ui->label_nodire->hide();
    ui->label_noforce->show();
    ui->label_norange->hide();
    ui->label_nospe->show();

    ui->label_no1->hide();
    ui->label_no2->hide();
    ui->label_no3->show();
    ui->label_no4->show();

    ui->label_18->hide();
    ui->label_19->hide();

    if(widgett[0]==0)
    {

        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[0]=1;
    }
    if(widgett[1]==0)
    {
        ui->widget_6->setStyleSheet("QWidget#widget_6{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        widgett[1]=1;
    }
    if(widgett[2]==1)
    {
        ui->widget_8->setStyleSheet("QWidget#widget_8{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[2]=0;
    }
    if(widgett[3]==1)
    {
        ui->widget_9->setStyleSheet("QWidget#widget_9{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[3]=0;
    }



     ui->label_17->show();

     ui->widget_4->show();

}

void Dialog::w_init()
{
    test_set_zero();
    temp_test=0;

    ui->chiraopian->hide();
    ui->qushen->hide();
    ui->huizhuan->hide();
    ui->ouhe->hide();



    ui->widget_speed1->hide();
    ui->widget_force1->hide();
    ui->widget_10->hide();

    //ui->gaugepanel->hide();
    ui->label_r_4->hide();
    ui->label_r_5->hide();
    ui->label_r_6->hide();
    ui->label_r_7->hide();

    ui->label_arrow1->hide();
    ui->label_arrow2->hide();
    ui->label_arrow3->hide();
    ui->label_arrow4->hide();

    ui->label_nodire->show();

    ui->label_noforce->show();
    ui->label_norange->show();
    ui->label_nospe->show();

    ui->label_no1->show();
    ui->label_no2->show();
    ui->label_no3->show();
    ui->label_no4->show();


    ui->label_17->hide();
    ui->label_18->hide();
    ui->label_19->hide();

    if(widgett[0]==1)
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[0]=0;
    }
    if(widgett[1]==1)
    {
        ui->widget_6->setStyleSheet("QWidget#widget_6{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[1]=0;
    }
    if(widgett[2]==1)
    {
        ui->widget_8->setStyleSheet("QWidget#widget_8{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[2]=0;
    }
    if(widgett[3]==1)
    {
        ui->widget_9->setStyleSheet("QWidget#widget_9{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181, 181, 181)}");
        widgett[3]=0;
    }




    ui->widget_4->show();


}

void Dialog::test_set_zero()
{
    num_range_direction=-1;
    ui->check_1->hide();
    ui->check_2->hide();
    ui->check_3->hide();
    ui->num_1->hide();
    ui->num_2->hide();
    ui->num_3->hide();
    b_speed[speed_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    b_force[force_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    b_range[range_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    b_direction[direction_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");

    for(int i=0;i<3;i++)
    {
        check[i]=0;
    }

    ui->label_speed->setText("0");
    ui->label_speed_3->setText("0");
    ui->range1->setText("0");
    ui->range_2->setText("0");
}





/*
鼠标移动窗口
void Dialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        //求坐标差值
        //当前点击坐标-窗口左上角坐标
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        //移到左上角
        move(e->globalPos() - p);
    }

}
*/

/*
void Dialog::on_toolButton_clicked()
{
    showMinimized();
}

void Dialog::on_toolButton_2_clicked()
{
     close();
}
*/


void Dialog::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label->setText(str);
}


void Dialog::closemention(void)
{
    ui->finger->hide();
    ui->weiwancheng->hide();
    timer2->stop();
}

/*
void Dialog::on_pushButton_clicked()
{
    ui->nbt1->setStyleSheet("background: rgb(255, 85, 0)");
    ui->nbt2->setStyleSheet("background: rgb(77, 212, 183)");
    ui->nbt4->setStyleSheet("background: rgb(77, 212, 183)");
    ui->nbt3->setStyleSheet("background: rgb(77, 212, 183)");
    this->ui->widget_user->show();
    ui->widget_user2->hide();
    ui->widget_user3->hide();
    ui->widget_user6->hide();
    ui->label_6->setText("hzj");
    ui->label_7->setText("24");
    ui->label_8->setText("男");

}
*/

//主选择栏
void Dialog::buttonClick2()
{
    QList<QWidget*> list1;
    list1<<ui->w_user1<<ui->w_user2<<ui->w_user3<<ui->w_user4<<ui->w_user5<<ui->w_user6;
    New_Button *b = (New_Button *)sender();
    //qDebug() << "当前按下" << b->text();
    for (int i = 0; i < btn1.count(); i++) {
        New_Button *btn = btn1.at(i);
        btn->setChecked(b == btn);
        if(b==btn)
        {

            for(int j=0;j<5;j++)
            {
                list1[j]->hide();
            }
            if(i==2)
            {
                is_train=1;   //训练模式
                for (int i = 0; i < btn_test.count(); i++)
                {
                    btn_test[i]->setStyleSheet("background-color:rgb(181, 181, 181,55%);font-family:SimHei;font-size : 24px;color:rgb(0, 159, 227)");
                }
               ui->widget_4->hide();

               list1[1]->show();
               initForm_train();
            }
            else if(i==1)
            {
                is_train=0;      //测试模式
                for (int i = 0; i < btn_test.count(); i++)
                {
                    btn_test[i]->setStyleSheet("background-color:rgb(181, 181, 181,55%);font-family:SimHei;font-size : 24px;color:rgb(0, 159, 227)");
                }
                ui->widget_4->hide();

               list1[1]->show();
               initForm_test();
            }
            else
               list1[i]->show();

           if(i==1)
           {
                //initForm_test();
        }
        }

    }
}


void Dialog::buttonClick_test()
{
    QPushButton *b = (QPushButton *)sender();
    //qDebug() << "当前按下" << b->text();
    for (int i = 0; i < btn_test.count(); i++) {
        QPushButton *btn = btn_test.at(i);
        btn_test[i]->setStyleSheet("background-color:rgb(181, 181, 181,55%);font-family:SimHei;font-size : 24px;color:rgb(0, 159, 227)");

        if(b==btn)
        {
            btn->setStyleSheet("border-style: solid;border-width: 2px;border-color:rgb(131,104,153);background-color:rgb(255, 130, 5);font-family:SimHei;font-size : 24px;color:rgb(0, 0, 90) ");
            btn->setChecked(true);
            switch(i)
            {
            case 0:
                if(is_train==0)
                {
                    range_init();
                    test_category=i;


                }
                else if(is_train==1)
                {
                    speed_init();
                    test_category=i;
                }
                break;
            case 1:
                speed_init();
                test_category=i;
                break;
            case 2:
                z_init();
                test_category=i;
                break;
            case 3:
                c_init();
                test_category=i;
                break;
            case 4:
                w_init();
                test_category=i;
                break;
            default:
                break;

            }
        }

    }
}

void Dialog::on_pushButton_1_clicked()
{

}
/*
void Dialog::on_pushButton_clicked()
{
    QPushButton *b = (QPushButton *)sender();
    if(num1==1)
    {
        b->setStyleSheet("border-radius: 8px;border-image:url(:/new/prefix1/button_off.jpg)");
        num1=0;
        ui->label_p->hide();
        ui->label_r_1->hide();
        ui->label_pp->show();
    }
    else
    {
        b->setStyleSheet("border-radius: 8px;border-image:url(:/new/prefix1/button_on.jpg)");
        num1=1;
    }
}
*/

void Dialog::button_SpeedChoice()
{


    if(num_range_direction==-1)
    {
        direction1->start(250);
        return;
    }

    ui->speed_change1->show();
    ui->speed_change2->show();
    QPushButton *b = (QPushButton *)sender();
    b_speed[speed_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    for(int i=0;i<3;i++)
    {
        if(b==b_speed[i])
        {


            if(num_range_direction==0) //尺桡偏
            {
                ui->label_speed->setText(QString::number(speed[0][i],10));

            }
            else if(num_range_direction==1) //屈伸
            {
                ui->label_speed->setText(QString::number(speed[1][i],10));

            }
            else if(num_range_direction==2) //回转
            {
                ui->label_speed->setText(QString::number(speed[2][i],10));

            }
            speed_btn=i;
            check[2]=1;
        }
    }
    ui->check_3->show();
    ui->num_3->hide();

    b->setStyleSheet("font-size:24pt;font-family:SimHei;border-style:solid;border-color: rgb(102, 113, 161);border-radius:24px;border-width:6px;color: rgb(70, 0, 106);");
}

void Dialog::button_ForceChoice()
{

    if(num_range_direction==-1)
    {
        direction1->start(250);
        return;
    }

    ui->force_change1->show();
    ui->force_change2->show();
    QPushButton *b = (QPushButton *)sender();
    b_force[force_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    for(int i=0;i<3;i++)
    {

        if(b==b_force[i])
        {


            if(num_range_direction==0) //尺桡偏
            {
                ui->label_speed_3->setText(QString::number(force[0][i],10));
                    Force=force[0][i];


            }
            else if(num_range_direction==1) //屈伸
            {
                ui->label_speed_3->setText(QString::number(force[1][i],10));
                Force=force[1][i];

            }
            else if(num_range_direction==2) //回转
            {
                ui->label_speed_3->setText(QString::number(force[2][i],10));
                Force=force[2][i];

            }
            force_btn=i;
            check[2]=1;
        }
    }
    ui->check_3->show();
    ui->num_3->hide();

    b->setStyleSheet("font-size:24pt;font-family:SimHei;border-style:solid;border-color: rgb(102, 113, 161);border-radius:24px;border-width:6px;color: rgb(70, 0, 106)");
}


void Dialog::button_RangeChoice()
{


    if(num_range_direction==-1)
    {
        direction1->start(250);
        return;
    }

    ui->range_change1->show();
    ui->range_change2->show();
    ui->range_change3->show();
    ui->range_change4->show();
    b_range[range_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");
    QPushButton *b = (QPushButton *)sender();
    for(int i=0;i<3;i++)
    {

        if(b==b_range[i])
        {
            /*
            if(num_range_direction==-1)
            {
                ui->range1->setText(QString::number(0,10));
                ui->range_2->setText(QString::number(0,+10));
                return;
            }
            */
            if(num_range_direction==0) //尺桡偏
            {
                ui->range1->setText(QString::number(range[0][i][0],10));
                ui->range_2->setText(QString::number(range[0][i][1],+10));
            }
            else if(num_range_direction==1) //屈伸
            {
                ui->range1->setText(QString::number(range[1][i][0],10));
                ui->range_2->setText(QString::number(range[1][i][1],+10));
            }
            else if(num_range_direction==2) //回转
            {
                ui->range1->setText(QString::number(range[2][i][0],10));
                ui->range_2->setText(QString::number(range[2][i][1],+10));
            }
            range_btn=i;
            check[1]=1;
        }
    }
    ui->check_2->show();
    ui->num_2->hide();

    b->setStyleSheet("font-size:24pt;font-family:SimHei;border-style:solid;border-color: rgb(102, 113, 161);border-radius:24px;border-width:7px;color: rgb(70, 0, 106)");
}

void Dialog::button_DirectionChoice()
{
    if(test_category==0)
    {

        Dialog::range_init();
    }
    else if(test_category==1)
    {
        speed_init();
    }
    else if(test_category==2)
    {
        z_init();
    }
    else if(test_category==3)
    {
        c_init();
    }
    else if(test_category==4)
    {
        w_init();
    }
    QPushButton *b = (QPushButton *)sender();
    b_direction[direction_btn]->setStyleSheet("background-color: rgb(200, 200, 200);font-family:SimHei;font-size:18pt;color: rgb(70,70,70);border-radius:22px");

    for(int i=0;i<4;i++)
    {

        if(b==b_direction[i])
        {
            direction_btn=i;
            num_range_direction=i;
            check[0]=1;
            for(int j=0;j<4;j++)
            {
                arrow[j]->hide();
            }
            arrow[i]->show();
        }

    }
    b->setStyleSheet("font-size:20pt;font-family:SimHei;border-style:solid;border-color: rgb(102, 113, 161);border-radius:24px;border-width:5px;color: rgb(70, 0, 106);");
    if(temp_test==1)
    {
        ui->check_2->show();
        ui->num_2->hide();
    }
    else
    {
        ui->check_1->show();
        ui->num_1->hide();
    }

    //ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");

}


//运动开始后进行倒计时，倒计时至0后调用结束按钮的功能函数进行运动结束
void Dialog::time_minus()
{
    *TimeRecord = TimeRecord->addSecs(-1);
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
    time_all--;
    if(time_all==0)
    {

       on_pushButton_9_clicked();

    }
}

void Dialog::time_rec()
{
    time_data_str+=base_time;
}


void Dialog::on_pushButton_clicked()
{
    ui->widget_cover->hide();
    ui->widget_17->hide();
    ui->widget_13->hide();
    ui->widget_12->hide();
    ui->widget_run->hide();
    ui->w_user2->show();
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
}




//设置运动持续时间中的减少按钮，每点击一次减少30秒
void Dialog::on_time_minus_clicked()
{
    *TimeRecord = TimeRecord->addSecs(-30);
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
}



//设置运动持续时间中的增加按钮，每点击一次增加30秒
void Dialog::on_time_add_clicked()
{
    *TimeRecord = TimeRecord->addSecs(30);
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
}



//运动开始之后，考虑到安全问题，将界面上的除暂停和结束以外的所有按钮失能（运动期间只能暂停和结束，防止误触）
void Dialog::unable()
{
    for(int i=0;i<btn1.count();i++)
    {
        btn1[i]->setEnabled(false);
    }
    for(int i=0;i<btn_test.count();i++)
    {
        btn_test[i]->setEnabled(false);
    }
    for(int i=0;i<3;i++)
    {

        b_range[i]->setEnabled(false);
        b_force[i]->setEnabled(false);
        b_speed[i]->setEnabled(false);
    }
    for(int i=0;i<4;i++)
    {
        b_direction[i]->setEnabled(false);
    }
    ui->time_add->setEnabled(false);
    ui->time_minus->setEnabled(false);
    ui->range_change1->setEnabled(false);
    ui->range_change2->setEnabled(false);
    ui->range_change3->setEnabled(false);
    ui->range_change4->setEnabled(false);
    ui->speed_change1->setEnabled(false);
    ui->speed_change2->setEnabled(false);
    ui->force_change1->setEnabled(false);
    ui->force_change2->setEnabled(false);

}



//运动结束后，将所有按键使能
void Dialog::enable()
{
    for(int i=0;i<btn1.count();i++)
    {
        btn1[i]->setEnabled(true);
    }
    for(int i=0;i<btn_test.count();i++)
    {
        btn_test[i]->setEnabled(true);
    }
    for(int i=0;i<3;i++)
    {

        b_range[i]->setEnabled(true);
        b_force[i]->setEnabled(true);
        b_speed[i]->setEnabled(true);
    }
    for(int i=0;i<4;i++)
    {
        b_direction[i]->setEnabled(true);
    }
    ui->time_add->setEnabled(true);
    ui->time_minus->setEnabled(true);
    ui->range_change1->setEnabled(true);
    ui->range_change2->setEnabled(true);
    ui->range_change3->setEnabled(true);
    ui->range_change4->setEnabled(true);
    ui->speed_change1->setEnabled(true);
    ui->speed_change2->setEnabled(true);
    ui->force_change1->setEnabled(true);
    ui->force_change2->setEnabled(true);

}


//测试开始按钮的功能函数，点击此按钮会判断
void Dialog::on_pushButton_6_clicked()
{
    //打开串口
    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口失败";
        return ;
    }
    else
    {
         qDebug()<<"打开串口成功";
    }

    if(test_category==3)
    {

    }


    min=TimeRecord->minute();
    sec=TimeRecord->second();
    time_all=min*60+sec;
    if(time_all==0)
    {
        return ;
    }
    if(is_train==0)
    {
        if(test_category==4)
        {
            test_category_id=14;
        }
        else
        {
            test_category_id=1+num_range_direction+test_category*3+(test_category?1:0);
        }
        bigData.test_or_train=0;
        bigData.category=test_category_id;
        sql->query->exec("insert into test_times value()");
        sql->query->exec("select MAX(test_id) from test_times");
        sql->query->first();
        bigData.test_id=sql->query->value(0).toString();
    }
    else if(is_train==1)
    {
        bigData.test_or_train=1;
        train_category_id=1+test_category*3+num_range_direction;
        bigData.category=train_category_id;
        sql->query->exec("insert into train_times value()");
        sql->query->exec("select MAX(train_id) from train_times");
        sql->query->first();
        bigData.train_id=sql->query->value(0).toString();
    }

    sp.ini_all(test_category);
    sp.ini=0;  //每次开始训练或测试时初始化串口参数
    switch (test_category) {
    case 0:
        if(check[0]==1)
        {
            unable();
            ui->widget_5->hide();
            ui->pushButton_6->hide();
            ui->w_user2->hide();
            ui->widget_15->show();

            serial->write(position_setting_start);
            // ui->widget_cover->show();
            ui->pushButton_8->show();
            ui->pushButton_9->show();
            //ui->pushButton_6->setText("训练暂停");
            //ui->pushButton_6->setStyleSheet("color: rgb(255, 200, 2);border-color: rgb(255, 200, 2);border-style:solid;border-width:5px;border-radius:38px");
        }
        else
        {
            ui->finger->show();
            ui->weiwancheng->show();
            timer2->start(2000);
        }
        break;
    case 1:
        if(check[0]==1&&check[1]==1&&check[2]==1)
        {
            unable();
            ui->widget_5->hide();
            ui->pushButton_6->hide();
            serial->write(position_setting_start);
            ui->w_user2->hide();
            ui->widget_15->show();
            //ui->widget_cover->show();
            ui->pushButton_8->show();
            ui->pushButton_9->show();
            //ui->pushButton_6->setText("训练暂停");
        }
        else
        {
            ui->finger->show();
            ui->weiwancheng->show();
            timer2->start(2000);
        }
        break;
    case 2:
        if(check[0]==1&&check[1]==1&&check[2]==1)
        {
            unable();
            ui->widget_5->hide();
            ui->pushButton_6->hide();
            serial->write(position_setting_start);
            ui->w_user2->hide();
            ui->widget_15->show();
           // ui->widget_cover->show();
            ui->pushButton_8->show();
            ui->pushButton_9->show();
            //ui->pushButton_6->setText("训练暂停");
        }
        else
        {
            ui->finger->show();
            ui->weiwancheng->show();
            timer2->start(2000);
        }
        break;
    case 3:
        if(check[0]==1&&check[1]==1)
        {
            unable();
            ui->widget_5->hide();
            ui->pushButton_6->hide();
            serial->write(position_setting_start);
            ui->w_user2->hide();
            ui->widget_15->show();
           // ui->widget_cover->show();
            ui->pushButton_8->show();
            ui->pushButton_9->show();
            //ui->pushButton_6->setText("训练暂停");
        }
        else
        {

            ui->finger->show();
            ui->weiwancheng->show();
            timer2->start(2000);
        }
        break;
    case 4:
        unable();
        ui->widget_5->hide();
        ui->pushButton_6->hide();
        ui->widget_15->show();
        ui->w_user2->hide();
        serial->write(position_setting_start);
       // ui->widget_cover->show();
        ui->pushButton_8->show();
        ui->pushButton_9->show();
        /*
            ui->widget_cover->show();
            ui->widget_run->show();
            ui->w_user2->hide();
        */
            break;
    default:
        break;
    }
}


//运动开始后的暂停/继续按钮的功能函数，包括对电机发送暂停运动和继续运动的指令以及按钮显示“暂停”和“继续”间的切换
void Dialog::on_pushButton_8_clicked()
{
    if(go_on==0)
    {
        ongoing=2;
        ui->pushButton_8->setText("继续");
        speed_intime1=0;
        speed_intime2=0;
        speed_intime3=0;
        go_on=1;
        timerset->stop();
        data_time->stop();
    }
    else
    {
        ongoing=1;
        ui->pushButton_8->setText("暂停");
        go_on=0;
        timerset->start(1000);
        data_time->start(10);
    }

}


//运动结束按钮，结束此次运动，并将运动时间初始化到默认的2分30秒
void Dialog::on_pushButton_9_clicked()
{
    ongoing=2;
    go_on=0;
    ui->pushButton_8->setText("暂停");
    timerset->stop();
    TimeRecord = new QTime(0,2,30); //初始化时间
    speed_intime1=0;
    speed_intime2=0;
    speed_intime3=0;

    time_data_str=0;

    ui->widget_14->show();
    ui->widget_16->show();
    ui->pushButton_6->show();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();



}




//运动过程中对串口所传来的采集数据的接收函数
void Dialog::serial_recv()
{

    bool ok;
    QByteArray buf;
    recv_buff=serial->readAll();//被动接受数据
    save_once=recv_buff.size();//每次被动接受数据的大小
    if(ongoing==1)
    {
        if(save_once<=84)
        {
            if(recv_start==0)//未找到包头时循环寻找包头
            {
                //从每次被动接受的数据中找包头
                for(int i=0;i<save_once;i++)
                {
                    if((recv_buff.at(i)=='\xFA')&&(last_buff[0]=='\xFB'))
                    {
                        for(int j=0;j<(save_once-i);j++)
                        {
                            save_buff[j]=recv_buff[i+j];
                        }
                        recv_num=save_once-i;

                        recv_start=1;
                        qDebug()<<"重新寻找到包头";
                        break;
                    }
                    else
                    {
                        last_buff[0]=recv_buff[i];
                    }
                }
                recv_buff.clear();
            }
            else//已找到包头，取满数据，处理,清空数据包，判断下一组数据包
            {
                if(save_once<=(84-recv_num))//此次读取未取满或刚好取满数据
                {
                    for(int i=0;i<save_once;i++)
                    {
                        save_buff[recv_num++]=recv_buff[i];
                    }
                }
                else
                {//此次读取溢出数据
                    int p=84-recv_num;
                    if(p==0)
                    {
                        last_buff[0]=recv_buff[0];
                    }
                    else
                    {
                        for(int i=0;i<p;i++)
                        {
                            save_buff[recv_num++]=recv_buff[i];
                        }
                        last_buff[0]=recv_buff[p];
                    }
                    if(save_buff[83]=='\xFB')
                    {
                     //六维力数据提取计算
                        for(int i=0;i<6;i++)
                        {
                            buf[0]=save_buff[i*4+9];
                            buf[1]=save_buff[i*4+8];
                            buf[2]=save_buff[i*4+7];
                            buf[3]=save_buff[i*4+6];
                            six_force_value_str=buf.toHex();
                            six_force_value_hex = six_force_value_str.toUInt(0, 16);
                            six_force_value[i] = *(float*)&six_force_value_hex;

                            //qDebug()<<six_force_value[i];
                        }




                       //qDebug()<<six_force_value[0]<<six_force_value[1]<<six_force_value[2]<<six_force_value[3]<<six_force_value[4]<<six_force_value[5];

                        //确认收集到一包完整数据后，提取这包数据中的不同成分进行相应存储和处理
                        buf1=save_buff.mid(71,2);
                        position_now1=buf1.toHex().toInt(&ok,16);
                        if(position_now1<1100&&position_now1>-1100)
                        {
                            position_now11=position_now1/10.0;
                        }
                        else
                        {
                            position_now11=-(position_now1^65535)/10.0;
                        }


                        buf2=save_buff.mid(73,2);
                        position_now2=buf2.toHex().toInt(&ok,16);
                        if(position_now2<1100&&position_now2>-1100)
                        {
                            position_now22=position_now2/10.0;
                        }
                        else
                        {
                            position_now22=-(position_now2^65535)/10.0;
                        }


                        buf3=save_buff.mid(75,2);
                        position_now3=buf3.toHex().toInt(&ok,16);
                        if(position_now3<1100&&position_now3>-1100)
                        {
                            position_now33=position_now3/10.0;
                        }
                        else
                        {
                            position_now33=-(position_now3^65535)/10.0;
                        }



                        if(num_range_direction==1)//屈伸
                        {

                            position_now=position_now11;
                        }
                        else if(num_range_direction==0)//尺桡偏
                        {
                            position_now=position_now22;
                        }
                        else if(num_range_direction==2)//回转
                        {
                            position_now=position_now33;
                            //qDebug()<<position_now;
                        }
                        //qDebug()<<num_range_direction;

                        if(test_category==3)
                        {

                        }

                        if(bigData.AorB==0)
                        {
                            for(int i=0;i<6;i++)
                            {
                                bigData.data1.F[i][times]=QString("%1").arg(six_force_value[i]);

                            }
                            bigData.data1.ele_mach1[times]=QString("%1").arg(position_now11);//屈伸
                            bigData.data1.ele_mach2[times]=QString("%1").arg(position_now22);//尺桡偏
                            bigData.data1.ele_mach3[times]=QString("%1").arg(position_now33);//回转
                            bigData.data1.current_time[times]=QString("%1").arg(time_data_str);
                            bigData.data1.var1[times]="0";
                            bigData.data1.var2[times]="0";
                            bigData.data1.var3[times]="0";
                            bigData.data1.var4[times]="0";
                            bigData.data1.var5[times]="0";
                            bigData.data1.var6[times]="0";
                            bigData.data1.displacement[times]="0";
                            bigData.data1.gyro1[times]="0";
                            bigData.data1.gyro2[times]="0";
                            bigData.data1.gyro3[times]="0";
                            if(test_category==2)
                            {
                                if(num_range_direction==0)//尺桡偏
                                {
                                    speed_intime2=(int)(abs(six_force_value[2])*10);
                                    speed_intime=speed_intime2;
                                    six_force=six_force_value[2];


                                }
                                else if(num_range_direction==1)//屈伸
                                {
                                    speed_intime1=(int)(abs(six_force_value[0])*10);
                                    speed_intime=speed_intime1;
                                    six_force=six_force_value[0];

                                }
                                else if(num_range_direction==2)//回转
                                {
                                    speed_intime3=(int)(abs(six_force_value[4])*10);
                                    speed_intime=speed_intime3;
                                    six_force=six_force_value[4];

                                }

                            }
                            bigData.data1.mach2_speed[times]=QString("%1").arg(speed_intime2);
                            bigData.data1.mach1_speed[times]=QString("%1").arg(speed_intime1);
                            bigData.data1.mach3_speed[times]=QString("%1").arg(speed_intime3);
                            times++;

                        }
                        else
                        {
                            for(int i=0;i<6;i++)
                            {
                                bigData.data2.F[i][times]=QString("%1").arg(six_force_value[i]);
                            }
                            bigData.data2.ele_mach1[times]=QString("%1").arg(position_now11);
                            bigData.data2.ele_mach2[times]=QString("%1").arg(position_now22);
                            bigData.data2.ele_mach3[times]=QString("%1").arg(position_now33);
                            bigData.data2.current_time[times]=QString("%1").arg(time_data_str);
                            //传感器数值未确认准确，后续需要调整
                            bigData.data2.var1[times]="0";
                            bigData.data2.var2[times]="0";
                            bigData.data2.var3[times]="0";
                            bigData.data2.var4[times]="0";
                            bigData.data2.var5[times]="0";
                            bigData.data2.var6[times]="0";
                            bigData.data2.displacement[times]="0";
                            bigData.data2.gyro1[times]="0";
                            bigData.data2.gyro2[times]="0";
                            bigData.data2.gyro3[times]="0";
                            if(test_category==2)
                            {
                                if(num_range_direction==0)//尺桡偏
                                {
                                    speed_intime2=((abs(six_force_value[2]-1.1)*10)>Force)?(int)(abs(six_force_value[2]-1.1)*10-Force):0;
                                    speed_intime=speed_intime2;
                                    six_force=six_force_value[2]-1.1;

                                }
                                else if(num_range_direction==1)//屈伸
                                {
                                    speed_intime1=((abs(six_force_value[0])*10)>Force)?(int)(abs(six_force_value[0])*10-Force):0;
                                    speed_intime=speed_intime1;
                                    six_force=six_force_value[0];

                                }
                                else if(num_range_direction==2)//回转
                                {
                                    speed_intime3=((abs(six_force_value[4])*100)>Force)?(int)(abs(six_force_value[4])*100-Force):0;
                                    speed_intime=speed_intime3;
                                    six_force=six_force_value[4];

                                }

                            }
                            bigData.data2.mach2_speed[times]=QString("%1").arg(speed_intime2);
                            bigData.data2.mach1_speed[times]=QString("%1").arg(speed_intime1);
                            bigData.data2.mach3_speed[times]=QString("%1").arg(speed_intime3);
                            times++;
                        }
                        if(times==100)
                        {

                            bigData.AorB=!bigData.AorB;

                            bigData.ok_insert.wakeAll();
                            times=0;


                            //qDebug()<<bigData.AorB;
                        }

                        //qDebug()<<position_now;
                        if(test_category==0)
                        {
                            if(num_range_direction==0)//尺桡偏
                            {
                                speed_intime2=(abs(six_force_value[2]-1.1)*10);
                                speed_intime=speed_intime2;
                                six_force=six_force_value[2]-1.1;

                            }
                            else if(num_range_direction==1)//屈伸
                            {
                                speed_intime1=(abs(six_force_value[0])*10);
                                speed_intime=speed_intime1;
                                six_force=six_force_value[0];

                            }
                            else if(num_range_direction==2)//回转
                            {
                                speed_intime3=abs(six_force_value[4])*100;
                                speed_intime=speed_intime3;
                                six_force=six_force_value[4];

                            }

                        }



                        serial_send(position_now,speed_intime,six_force);

                        save_buff.clear();//处理一包完整数据后将其清除

                        if(last_buff[0]=='\xFA')//判断接下来是否接着一个整包数据
                        {
                            for(int i=0;i<(save_once-p);i++)
                            {
                                save_buff[i]=recv_buff[p+i];
                            }
                            recv_num=save_once-p;
                        }
                        else
                        {
                            recv_start=0;
                            recv_num=0;
                        }
                    }
                    else
                    {
                        save_buff.clear();//处理一包完整数据后将其清除
                        recv_start=0;
                        recv_num=0;
                    }
                }
            recv_buff.clear();
            }
        }
        else
        {
            recv_buff.clear();
       // serial->write(end_moving);
        }
    }
    else if(ongoing==2)
    {
        for(int i=0;i<100;i++)
        {
            serial->write(halt);
            recv_buff.clear();
        }
        ongoing=0;
        /*
        if(is_stop==0)
        {
            serial->write(halt);
            recv_buff.clear();
            is_stop=1;
        }
        else
        {
            recv_buff.clear();
        }
        */

    }

    else
    {
        recv_buff.clear();
    }
    //emit operate(1);
}



//此函数实现的功能为通过串口向下位机进行运动控制指令发送，此函数由serial_recv函数（上方相邻的函数）在完成采集数据的处理后进行调用，来向下位机发送实时指令
void Dialog::serial_send(float position_now,int speed_intime,float six_force)
{
    if(test_category==0)
    {
        QByteArray sendbuff=sp.huodong(num_range_direction,speed_intime,six_force);
        serial->write(sendbuff);
    }
    else if(test_category==1)
    {

        QByteArray sendbuff=sp.dengsu(ui->range1->text(),ui->range_2->text(),ui->label_speed->text(),num_range_direction, position_now);
        serial->write(sendbuff);
    }
    else if(test_category==2)
    {
        QByteArray sendbuff=sp.dengzhang(ui->range1->text(),ui->range_2->text(),num_range_direction,speed_intime,six_force);
        serial->write(sendbuff);
    }
    else if(test_category==3)
    {
        QByteArray sendbuff=sp.dengchang(ui->range1->text(),ui->range_2->text(),num_range_direction, position_now);
        serial->write(sendbuff);
    }
}



//位姿调整提示框的完成按钮
void Dialog::on_pushButton_10_clicked()
{

    //ui->widget_cover->hide();
    //ui->widget_14->hide();
    serial->write(position_setting_end);

    timerset->start(1000);
    data_time->start(10);

    ui->w_user2->show();
    ui->widget_15->hide();
    ongoing=1;
}

void Dialog::on_pushButton_12_clicked()
{
    ui->widget_14->hide();
    ui->widget_16->hide();
    if(test_category==1)
    {
        ui->widget_20->hide();
        ui->widget_19->hide();
        ui->widget_17->show();
        ui->widget_13->hide();
        ui->widget_12->hide();
    }
    if(test_category==0)
    {
        if(num_range_direction==3)
        {
            ui->widget_20->hide();
            ui->widget_19->hide();
            ui->widget_17->hide();
            ui->widget_13->show();
            ui->widget_12->hide();
        }
        else
        {
            ui->widget_20->hide();
            ui->widget_19->hide();
            ui->widget_17->hide();
            ui->widget_13->hide();
            ui->widget_12->show();

        }
    }
    if(test_category==2)
    {
        ui->widget_20->hide();
        ui->widget_19->show();
        ui->widget_17->hide();
        ui->widget_13->hide();
        ui->widget_12->hide();
    }
    if(test_category==3)
    {
        ui->widget_20->show();
        ui->widget_19->hide();
        ui->widget_17->hide();
        ui->widget_13->hide();
        ui->widget_12->hide();
    }
    enable();
    serial->close();
    ui->widget_5->show();


    ui->widget_cover->show();
    ui->widget_run->show();
    ui->w_user2->hide();
}

void Dialog::on_pushButton_11_clicked()
{
    enable();
    serial->close();
    ui->lcdNumber->display(TimeRecord->toString("mm:ss"));
    ui->widget_14->hide();
    ui->widget_16->hide();
}




//实现运动范围调整功能，并设置运动范围的下限值
void Dialog::on_range_change1_clicked()
{
    int rang1=ui->range1->text().toInt();
    if(rang1<-100)
        return ;
    else
    {
        rang1-=1;
        QString ran1 = QString::number(rang1);

        ui->range1->setText(ran1);
    }
}
void Dialog::on_range_change2_clicked()
{
    int rang1=ui->range1->text().toInt();
    if(rang1>=0)
        return ;
    else
    {
        rang1+=1;
        QString ran1 = QString::number(rang1);
        ui->range1->setText(ran1);
    }
}



//运动范围上限
void Dialog::on_range_change3_clicked()
{
    int rang1=ui->range_2->text().toInt();
    if(rang1<=0)
        return ;
    else
    {
        rang1-=1;
        QString ran1 = QString::number(rang1);
        ui->range_2->setText(ran1);
    }
}

void Dialog::on_range_change4_clicked()
{
    int rang1=ui->range_2->text().toInt();
    if(rang1>100)
        return ;
    else
    {
        rang1+=1;
        QString ran1 = QString::number(rang1);
        ui->range_2->setText(ran1);
    }
}


//运动速度下限
void Dialog::on_speed_change1_clicked()
{
    int rang1=ui->label_speed->text().toInt();
    if(rang1<=0)
        return ;
    else
    {
        rang1-=1;
        QString ran1 = QString::number(rang1);
        ui->label_speed->setText(ran1);
    }
}



//运动速度上限
void Dialog::on_speed_change2_clicked()
{
    int rang1=ui->label_speed->text().toInt();
    if(rang1>100)
        return ;
    else
    {
        rang1+=1;
        QString ran1 = QString::number(rang1);
        ui->label_speed->setText(ran1);
    }
}


//运动阻力下限
void Dialog::on_force_change1_clicked()
{
    int rang1=ui->label_speed_3->text().toInt();
    if(rang1<=0)
        return ;
    else
    {
        rang1-=1;
        QString ran1 = QString::number(rang1);
        ui->label_speed_3->setText(ran1);
    }
}


//运动阻力上限
void Dialog::on_force_change2_clicked()
{
    int rang1=ui->label_speed_3->text().toInt();
    if(rang1>100)
        return ;
    else
    {
        rang1+=1;
        QString ran1 = QString::number(rang1);
        ui->label_speed_3->setText(ran1);
    }
}

void Dialog::on_pushButton_7_clicked()
{
    close();
    this->~Dialog();

}

void Dialog::on_pushButton_14_clicked()
{
    ui->widget_18->hide();
}

void Dialog::on_pushButton_15_clicked()
{
    ui->widget_18->hide();
    //sql->query->exec("insert into test_times value()");
    QString p_id=ui->userid->text();
    sql->query->exec("select patient_id,patient_name,gender,age,address from patient_info where patient_id="+p_id);
    sql->query->first();
    if(p_id==(sql->query->value(0).toString()))
    {
        use_patient=p_id.toInt();

    }
    else
    {
        use_patient=0;
    }
    try
    {
        ui->label_33->setText(sql->query->value(1).toString());
        ui->label_34->setText(sql->query->value(2).toString());
        ui->label_35->setText(sql->query->value(3).toString());
        ui->label_36->setText(sql->query->value(4).toString());
    }
    catch(std::exception e)
    {

    }

    //将个人数据加入系统
    sql->query->exec("select chipian_MAX_range,raopian_MAX_range,wanqu_MAX_range,beishen_MAX_range,xuanqian_MAX_range,xuanhou_MAX_range from patient_move_info where patient_id="+p_id);
    sql->query->first();
    if(p_id==(sql->query->value(0).toString()))
    {
        use_patient=p_id.toInt();

    }


}

void Dialog::on_pushButton_13_clicked()
{
    ui->userid->backspace();
}



void Dialog::on_pushButton_17_clicked()
{

}

void Dialog::on_regis_btn_clicked()   //
{
    ui->mention_regis->show();
    sql->query->exec("insert into patient_info values()");
    sql->query->exec("select patient_id from patient_info order by patient_id desc limit 1");
    sql->query->first();
    QString p_id=sql->query->value(0).toString();
    ui->patient_id->setText(p_id);

}

void Dialog::on_pushButton_18_clicked()                 //用户注册完成确认
{
    QString p_id=ui->patient_id->text();
    sql->query->exec("insert into patient_move_info (patient_id) values("+p_id+")");
    ui->mention_regis->hide();
}





void Dialog::on_pushButton_19_clicked()            //用户注册过程中取消注册时的处理函数
{
    ui->mention_regis->hide();
    QString p_id=ui->patient_id->text();
    sql->query->exec("delete from patient_info where patient_id="+p_id);
}







void Dialog::warmest_ment()      //判断参数设置操作是否恰当（如果参数设置流程错误，点击开始按钮会出现提示况闪动）
{
    if(aaa==0)
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(181,181,181)}");//255,57,39
        ui->label_17->hide();
        aaaa--;
        aaa=1;
    }
    else
    {
        ui->widget_7->setStyleSheet("QWidget#widget_7{border-style:dashed;border-width:3px ;border-radius:15px ;border-color: rgb(0, 117, 172)}");
        ui->label_17->show();
        aaaa--;
        aaa=0;
    }
    if(aaaa==0)
    {
        direction1->stop();
        aaaa=6;
    }
}
