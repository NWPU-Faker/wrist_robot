#ifndef SERIALPROCESS_H
#define SERIALPROCESS_H

#include <QByteArray>
#include <QString>

class SerialProcess
{
private:
    QByteArray zero_array;
    QByteArray command_chirao;
    QByteArray command_qushen;
    QByteArray command_huizhuan;

    QByteArray command_dengsu;
    QByteArray command_dengzhang;
    QByteArray command_dengchang;


    int zero_position_pulse_1 = 526844;     //1号电机（屈伸）的零位置脉冲值，16进制为809fc
    int zero_position_pulse_2 = 276624;     //2号电机（尺桡偏）的零位置脉冲值，16进制为43890
    int zero_position_pulse_3 = 3719119;    //3号电机（旋前旋后）的零位置脉冲值，16进制为38bfcf

    int pulse_per_degree_1 = 7146;          //1号电机（屈伸）运动一度的脉冲数
    int pulse_per_degree_2 = 7146;          //2号电机（尺桡偏）运动一度的脉冲数
    int pulse_per_degree_3 = 45000;         //3号电机（旋前旋后）运动一度的脉冲数

    int positive20;
    int positive21;
    int positive22;
    int positive23;
    int negative20;
    int negative21;
    int negative22;
    int negative23;

    int zero20;
    int zero21;
    int zero22;
    int zero23;

    bool PtoN;
public:
    bool is_initialized;
    SerialProcess();
    void ini_all(int test_category);
    QByteArray dengsu(QString citann, QString citapp, QString speed,
                      int direction, float current_position);
};

#endif // SERIALPROCESS_H
