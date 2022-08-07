#ifndef SERIALPROCESS_H
#define SERIALPROCESS_H

#include <QByteArray>

class SerialProcess
{
private:
    QByteArray zero_array;
    QByteArray buff_huodong_chirao;
    QByteArray buff_huodong_qushen;
    QByteArray buff_huodong_huizhuan;

    QByteArray command_dengsu;
    QByteArray command_dengzhang;
    QByteArray command_dengchang;


    int zero_position_pulse_1 = 526844;     //1号电机（屈伸）的零位置脉冲值，16进制为809fc
    int zero_position_pulse_2 = 276624;     //2号电机（尺桡偏）的零位置脉冲值，16进制为43890
    int zero_position_pulse_3 = 3719119;    //3号电机（旋前旋后）的零位置脉冲值，16进制为38bfcf

    int pulse_per_degree_1 = 7146;
    int pulse_per_degree_2 = 7146;
    int pulse_per_degree_3 = 45000;
public:
    SerialProcess();
    void ini_all(int test_category);

};

#endif // SERIALPROCESS_H
