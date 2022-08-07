#include "serialprocess.h"

SerialProcess::SerialProcess()
{

}
void SerialProcess::ini_all(int test_category)
{
    for (int i = 0; i < 81; i++)
    {
        zero_array[i] = 0;
    }
    command_dengsu = zero_array;
    command_dengchang = zero_array;
    command_dengzhang = zero_array;
    buff_huodong_qushen = zero_array;
    buff_huodong_chirao = zero_array;
    buff_huodong_huizhuan = zero_array;

    if (test_category = 0)
    {
        ;
    }


    else if (test_category = 1)     //等速运动默认的发送的指令（后续根据商量的下位机程序修改）
    {
        command_dengsu[0] = 0xFA;
        command_dengsu[1] = 0xfb;
        command_dengsu[2] = 0x01;
        command_dengsu[80] = 0xFB;
    }

}
