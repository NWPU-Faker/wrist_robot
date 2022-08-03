#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include <QMouseEvent>

#include <QMessageBox>//password need
#include <QFontDatabase>
#include <QDebug>

#pragma execution_character_set("utf-8")


QString user;
QString passw;

//登陆界面的构造函数
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    oksql=0;

    dd=new Dialog();

    ui->setupUi(this);

    //showFullScreen();
    //去窗口边框
    ui->widget->hide();
    ui->password->setEchoMode(QLineEdit::Password);//输入的密码以圆点隐藏


            setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //把窗口背景设置为透明;
    setAttribute(Qt::WA_TranslucentBackground);

    //时间显示
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);



    timer1 = new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(close_log()));

    num<<ui->pushButton_00<<ui->pushButton_01<<ui->pushButton_02<<ui->pushButton_03<<ui->pushButton_04<<ui->pushButton_05<<ui->pushButton_06<<ui->pushButton_07<<ui->pushButton_08<<ui->pushButton_09;
    for(int i=0;i<num.count();i++)
    {
        connect(num[i], SIGNAL(clicked(bool)), this, SLOT(num_insert()));
    }


    ui->widget_2->hide();


    int fontId = QFontDatabase::addApplicationFont(":/new/prefix1/fontawesome-webfont.ttf");
     QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
     QFont font;
     font.setFamily(fontFamilies.at(0));
     //QRect textRect = QRect(10, 0, ui->label_5->width(),  ui->label_5->width());
     ui->label_5->setGeometry(rect().x()+923, rect().y()+343,30, 40);
     //chanel1->setParent(this);

     ui->label_5->setFont(font);
     ui->label_5->setText(QChar(0xf007));
     ui->label_5->setContentsMargins(0,0,0,0);
     ui->label_5->setStyleSheet("font-size : 35px");

     ui->label_6->setGeometry(rect().x()+925, rect().y()+424,30, 40);
     ui->label_6->setFont(font);
     ui->label_6->setText(QChar(0xf13e));
     ui->label_6->setStyleSheet("color: rgb(0,0,0);");
     ui->label_6->setContentsMargins(0,0,0,0);
     ui->label_6->setStyleSheet("font-size : 35px");

     ui->sqlok->setFont(font);
     ui->sqlok->setText(QChar(0xf05d));
     ui->sqlok->setContentsMargins(0,0,0,0);
     ui->sqlok->setStyleSheet("color:rgb(56,232,83);font-size : 44px");
     ui->sqlok_2->setFont(font);
     ui->sqlok_2->setText(QChar(0xf05e));
     ui->sqlok_2->setContentsMargins(0,0,0,0);
     ui->sqlok_2->setStyleSheet("color:rgb(255,55,29);font-size : 44px");
     //mysql连接
     ui->widget_3->hide();
     ui->widget_4->hide();
     oksql=sql->connect_mysql();
     QTimer* timer2 = new QTimer(this);
     connect(timer2,SIGNAL(timeout()),this,SLOT(close_sql()));

     if(oksql==1)
     {
         ui->widget_3->show();
         timer2->start(2000);

     }
     else
     {
         ui->widget_4->show();
         timer2->start(3000);
     }


     QByteArray inita;
     for(int i=0;i<81;i++)
     {
         inita[i]=0;
     }

     //位姿调制指令，设备进入随动状态
     dd->position_setting_start=inita;
     dd->position_setting_start[0]=0xFA;
     dd->position_setting_start[1]=0x05;
     dd->position_setting_start[79]=0xFF;
     dd->position_setting_start[80]=0xFB;




     //位姿调制结束指令，设备进入静止状态
     dd->position_setting_end=dd->position_setting_start;
     dd->position_setting_end[79]=0xFE;
     dd->position_setting_end[1]=0x04;


     //暂停指令
     dd->halt=inita;
     dd->halt[0]=0xFA;
     dd->halt[1]=0x02;
     dd->halt[80]=0xFB;
     dd->halt[79]=0xFC;

     //开始运动指令->
     dd->start=dd->halt;
     dd->start[1]=0x01;
     dd->start[5]=0x01;
     dd->start[80]=0xFB;



     dd->end_moving=inita;
     dd->end_moving[0]=0xFA;
     dd->end_moving[1]=0x02;
     dd->end_moving[80]=0xFB;
     dd->end_moving[79]=0xFC;


     ui->username->installEventFilter(this); ui->username->setMouseTracking(true);
     ui->password->installEventFilter(this); ui->password->setMouseTracking(true);


}




//事件过滤器：处理鼠标按下弹出小键盘
bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress&&(obj==ui->username))
    {
        user=0;
        ui->widget_2->show();
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress&&(obj==ui->password))
    {
        user=1;
        ui->widget_2->show();
        return true;
    }

    return QWidget::eventFilter(obj,event);


}





//登陆界面的析构函数
Widget::~Widget()
{
    delete ui;
    delete dd;
    delete timer;
    delete timer1;



}

//打开界面时，数据库连接成功或失败会弹出提示框显示3秒
void Widget::close_sql()
{
    ui->widget_3->hide();
    ui->widget_4->hide();
}


//函数功能为在虚拟键盘按下某个数字按钮，则在用户名或密码输入栏中插入该数字
void Widget::num_insert()
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
    if(user==0)
    {

       QString s = QString::number(temp);
       ui->username->insert(s);

    }
    else if(user==1)
    {

       QString s = QString::number(temp);
       ui->password->insert(s);


    }



}


//登陆界面右上角的最小化按钮
void Widget::on_toolButton_clicked()
{
     showMinimized();
}
//登陆界面右上角的关闭按钮
void Widget::on_toolButton_2_clicked()
{
    close();
    this->~Widget();
}


//登陆界面右下角的时间显示的实现函数
void Widget::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_3->setText(str);
}


//登陆成功，关闭此界面，打开主系统界面
void Widget::close_log()
{
    hide();
    //this->~Widget();
}

//登录按钮的功能实现函数，点击按钮后会查询数据库对用户名和密码进行确认。如果正确的话，将登陆界面隐藏，将用户主界面设为显示。如果错误，弹出登陆失败提示框
void Widget::on_pushButton_clicked()
{
    ui->widget_2->hide();

    QString name = ui->username->text();
    sql->m_Model->setTable("user");
    sql->m_Model->setFilter(QString("username = '%1'").arg(name));
    sql->m_Model->select();
    int log1=sql->m_Model->rowCount();

    if(log1!=0)
    {
        QString password1 = sql->m_Model->record(0).value("password").toString();
        QString password2 = ui->password->text();
        if(password1==password2)
        {
            timer->stop();
            dd->show();
            timer1->start(700);
        }
        else
        {
            this->ui->widget->show();
        }
    }
    else
    {
        this->ui->widget->show();
    }
}



//登录失败提示框上的确认按钮，点击后提示框消失
void Widget::on_pushButton_2_clicked()
{
    this->ui->widget->close();



}


//虚拟键盘上的确认按钮，点击后虚拟键盘消失
void Widget::on_pushButton_14_clicked()
{
    ui->widget_2->hide();
}


//点击虚拟键盘的回退按钮，会根据情况将用户名和密码输入栏的输入进行清楚
void Widget::on_pushButton_11_clicked()
{
    if(user==0)
    {
        ui->username->backspace();
    }
    else if(user==1)
    {
        ui->password->backspace();
    }
}
