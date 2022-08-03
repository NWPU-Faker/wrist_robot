#ifndef SERIAL_PROCESS_H
#define SERIAL_PROCESS_H
#include <QByteArray>
class SerialProcess
{
private:
    QByteArray inital;
    QByteArray buff_huodong_chirao;
    QByteArray buff_huodong_qushen;
    QByteArray buff_huodong_huizhuan;
    QByteArray buff_dengsu;
    QByteArray buff_dengzhang;
    QByteArray buff_dengchang;


    int zero_qushen=526844;   //1号电机（屈伸）的零位置脉冲值，16进制为809fc
    int val_pers_qushen=7146;   //1号电机（屈伸）运动一度的脉冲数
    int zero_chirao=276624;   //2号电机（尺桡偏）的零位置脉冲值，16进制为43890
    int val_pers_chirao=7146;   //2号电机（尺桡偏）运动一度的脉冲数
    int zero_huizhuan=3719119;   //3号电机（回转）的零位置脉冲值，16进制为38bfcf
    int val_pers_huizhuan=45000;   //3号电机（回转）运动一度的脉冲数


    int postive20;
    int postive21;
    int postive22;
    int postive23;
    int negative20;
    int negative21;
    int negative22;
    int negative23;

    int zero20;
    int zero21;
    int zero22;
    int zero23;

    int PtoN;
public:

    int ini;   //测试开始时初始化
    void ini_all(int test_category);
    QByteArray dengsu(QString citann,QString citapp,QString speed,int dir,float position_now);
    QByteArray huodong(int num_range_direction,int speed,float force);
    QByteArray dengzhang(QString citann,QString citapp,int dir,int speed,float force);
    QByteArray dengchang(QString citann,QString citapp,int dir,float position_now);


};



#endif // SERIAL_PROCESS_H

/*
void SerialProcess()
{
    for(int i=0;i<81;i++)
    {
        inital[i]=0;
    }
    buff_dengsu=inital;
    buff_dengchang=inital;
    buff_dengzhang=inital;
}
~SerialProcess();
*/
