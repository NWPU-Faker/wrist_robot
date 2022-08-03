#pragma execution_character_set("utf-8")
#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QDialog>
#include<QTimer>
#include<QDateTime>
#include<QLabel>

//#include"icon_help.h"
#include"new_button.h"
#include"test_widget.h"
#include"serial_process.h"
#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include "mythread.h"

namespace Ui {
class Dialog;
}


//构建用户主界面
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    //串口对象,与下位机通信
    QSerialPort* serial;   //串口对象

    SerialProcess sp;   //向下位机发送的81字节数据处理类
    QByteArray position_setting_start;   //81字节数据包（开始位姿调整）
    QByteArray position_setting_end;   //81字节数据包（结束位姿调整）
    QByteArray start;          //81字节数据包（运动开始指令）
    QByteArray halt;          //81字节数据包（运动暂停指令）
    QByteArray end_moving;          //81字节数据包（运动结束指令）

    QByteArray recv_buff;          //从串口每次读取到的数据缓存（不确定长度）
    QByteArray save_buff;          //目前已累计的数据缓存（不满一整包数据时，会将每次读取的数据进行累计）
    QByteArray last_buff;          //读到一包数据时，记录最后一个字节，用来判断整包数据间是否连贯



protected:
    //void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    //void mousePressEvent(QMouseEvent *e);//鼠标按下移动
    bool Dialog::eventFilter(QObject *obj, QEvent *event);

private slots:
    //按键的失能与使能函数
    void unable();
    void enable();
    //主按键栏初始化
    void initForm();
    void initForm_user();
    void initForm_test_train();
    void initForm_test();
    void initForm_train();
    void initForm_history();
    void initForm_play();
    //最小化和关闭
    //void on_toolButton_clicked();
    //void on_toolButton_2_clicked();
    //时间显示
    void timerUpdate(void);
    void closemention(void);


    //方向、速度、阻力、运动范围的选择按钮的功能函数
    void buttonClick2();
    void buttonClick_test();
    void button_DirectionChoice();
    void button_SpeedChoice();
    void button_ForceChoice();
    void button_RangeChoice();


    void on_pushButton_1_clicked();

    //void on_pushButton_clicked();

    //5个主要运动的初始化函数和一个运动参数置零函数
    void range_init();      //活动范围测试初始化
    void speed_init();      //等速运动（测试/训练）初始化
    void z_init();      //等张运动（测试/训练）初始化
    void c_init();      //等长运动（测试/训练）初始化
    void w_init();     //等长测试界面初始化
    void test_set_zero();    //变量置零函数



    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_time_minus_clicked();
    void on_time_add_clicked();
    void time_minus();
    void time_rec();
    void warmest_ment();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void serial_recv();
    void serial_send(float position_now,int speed_intime,float six_force);
    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
    void on_range_change1_clicked();
    void on_range_change2_clicked();
    void on_range_change3_clicked();
    void on_range_change4_clicked();
    void on_speed_change1_clicked();
    void on_speed_change2_clicked();
    void on_force_change1_clicked();
    void on_force_change2_clicked();
    void on_pushButton_7_clicked();
    void dnum_insert();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_17_clicked();
    void on_regis_btn_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
signals:
    // 发送信号触发线程
    void operate(const int);

private:

    QTimer *timer2 ;  //时钟
    QTimer *timerset;  //倒计时
    QTime *TimeRecord;
    QTimer *data_time;  //数据时间戳的响应间隔10ms
    QTimer *direction1;  //先选运动方向提醒


    Ui::Dialog *ui;
    QList<New_Button*> btn1; //主界面左侧不同功能界面选择框的按钮集合
    QList<QPushButton*> btn_test;  //界面上策不同运动类别的按钮集合
    //4个主界面
    QWidget w_user1;  //用户信息界面
    QWidget w_user2;  //测试界面
    QWidget w_user3;  //训练界面
    QWidget w_user4;  //历史记录界面
    int num_range_direction;    //运动方向判断，0为尺桡偏，1为屈伸，2为回转，默认为-1.
    QStringList fontFamilies;   //界面图标使用的矢量图片所需的变量
    bool aaa;        //参数设置提示功能部分使用的一个条件变量
    int fontId;       //界面图标使用的矢量图片所需的变量
    int temp_test;     //此变量用于开始按钮上方的参数设置步骤提示符号在不同运动模式下的区别显示
    //初始值，测试用,1尺桡偏，2屈伸，3回转，   速度，阻力和运动范围据分为小，中，大三个等级
    int speed[3][3]={{3,6,9},{3,7,12},{5,9,15}};
    int force[3][3]={{10,15,20},{8,12,16},{8,12,16}};
    int range[3][3][2]={{{-2,6},{-5,11},{-7,19}},{{-15,20},{-25,30},{-40,45}},{{-30,30},{-40,40},{-60,60}}};
    int test_category ;//1~5个测试类别选择
    int check[3]={0,0,0};//最多三个checkory
    int Force;    //用于等张模式中，判断六维力值是否大于设置的运动阈值

    int is_train;    //1为训练模式，0为测试模式
    int train_category_id;      //训练模式的各个项目
    int test_category_id;        //测试模式的各个项目
    int go_on=0;       //判断机器人目前处于暂停状态还是运动状态
    int aaaa=6;

    int min;      //运动倒计时的分钟
    int sec;       //运动倒计时的秒
    int time_all;   //总运动时间（秒）
    int save_once;  //每次被动接受数据的大小（字节）
    int recv_start;   //标志未找到包头，开始寻找包头
    int recv_num;      //找到包头后顺带第一次接收数据量
    int widgett[4]={0,0,0,0};   //用于判断主界面目前处于哪个
    int speed_btn;
    int force_btn;
    int range_btn;
    int direction_btn;
    int ongoing;
    float position_now11;    //1号电机目前运动位置值
    float position_now22;    //2号电机目前运动位置值
    float position_now33;    //3号电机目前运动位置值
    float position_now;      //电机目前运动位置值（由串口读取的16进制向10进制转换过程中的中转用）
    int position_now1;      //1号电机目前运动位置值（近似整数值）
    int position_now2;      //2号电机目前运动位置值（近似整数值）
    int position_now3;      //3号电机目前运动位置值（近似整数值）
    int is_stop;//电机已停止
    QByteArray buf1;        //用于提取一包数据中的71，72字节（1号电机角度）
    QByteArray buf2;        //用于提取一包数据中的73，74字节（2号电机角度）
    QByteArray buf3;        //用于提取一包数据中的75，76字节（3号电机角度）

    int times;     //每100包数据向mysql存储一次，此变量记录已存缓存数

   float time_data_str;       //每包数据采集到的时间
    float base_time;          //time_data_str的记录间隔0.01秒

    QThread* myThrd;       //辅助线程，用于帮助主线程进行读取和存储

    float six_force_value[6];    //六维力数据
    QString six_force_value_str;    //六维力数据（接收时以字符串形式中转）
    int six_force_value_hex;       //六维力数据（16进制形式）
    int speed_intime1;        //1号电机速度值
    int speed_intime3;        //2号电机速度值
    int speed_intime2;        //3号电机速度值
    int speed_intime;         //电机速度值（由窗口读取的16进制向10进制转换过程中的中转用）
    float six_force;        //六维力数据中的某项（根据条件确定）用于传给serial_send函数中的形参用于电机运动指令的参数计算
    int use_patient;         //当前使用用户ID

    QList<QPushButton*> b_direction;    //运动方向按钮集合
    QList<QPushButton*> b_speed;      //运动速度调整按钮集合（大中小）
    QList<QPushButton*> b_force;      //运动阻力调整按钮集合（大中小）
    QList<QPushButton*> b_range;      //运动范围调整按钮集合（大中小）
    QList<QLabel*> arrow;      //界面上各参数设置框之间显示的蓝色指示箭头
    QList<QPushButton*> num;       //运动参数调整按钮集合（数值调整+-）


};

#endif // DIALOG_H
