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
    command_qushen = zero_array;
    command_chirao = zero_array;        //志杰后面就压根没再使用这个变量
    command_huizhuan = zero_array;      //志杰后面压根就没再使用这个变量

    if (test_category = 0)              //屈伸默认设置
    {
        command_qushen[0] = 0xFA;
        command_qushen[1] = 0x01;
        command_qushen[2] = 0x02;
        command_qushen[3] = 0x09;
        command_qushen[4] = 0x03;       //?????
        command_qushen[5] = 0x01;
        command_qushen[15] = 0x0A;      //“14~15”对应1号电机速度值；
        command_qushen[16] = 0;         //“16~17”对应1号电机加速度值；
        command_qushen[17] = 50;

        command_qushen[18] = 0;         //“18~19”对应1号电机速度值；
        command_qushen[19] = 50;
        command_qushen[80] = 0xFB;

        for (int i = 0; i < 79; i++)    //和校验位；
        {
            command_qushen[79] = command_qushen[79] + command_qushen[i];
        }

        ;
    }


    else if (test_category = 1)         //等速运动默认的发送的指令（后续根据商量的下位机程序修改）
    {
        command_dengsu[0] = 0xFA;
        command_dengsu[1] = 0x01;
        command_dengsu[2] = 0x02;
        command_dengsu[3] = 0x07;
        command_dengsu[5] = 0x01;       //后续应该需要修改
        command_dengsu[80] = 0xFB;
    }
    else if (test_category = 2)         //等张运动默认的发送的指令（后续根据商量的下位机程序修改）
    {
        command_dengsu[0] = 0xFA;
        command_dengsu[1] = 0x01;
        command_dengsu[2] = 0x02;
        command_dengsu[3] = 0x07;
        command_dengsu[5] = 0x01;       //后续应该需要修改
        command_dengsu[80] = 0xFB;
    }

}

QByteArray SerialProcess::dengsu(QString citann, QString citapp, QString speedd,
                                 int direction, float current_position)
{
    int citan = citann.toInt();
    int citap = citapp.toInt();
    int speed = speedd.toInt();

    if (direction = 1)              //屈伸方向的等速运动；
    {
        if (is_initialized = false)
        {
            command_dengsu[4] = 0x02;
            int p_pulse = zero_position_pulse_1 - pulse_per_degree_1 * citap;
            int p_head4 = p_pulse / 65536;
            int p_late4 = p_pulse / 65536;
            positive20 = p_head4 / 256;
            positive21 = p_head4 % 256;
            positive22 = p_late4 / 256;
            positive23 = p_late4 % 256;

            int n_pulse = zero_position_pulse_1 - pulse_per_degree_1 * citan;
            int n_head4 = n_pulse / 65536;
            int n_late4 = n_pulse / 65536;
            negative20 = n_head4 / 256;
            negative21 = n_head4 % 256;
            negative22 = n_late4 / 256;
            negative23 = n_late4 % 256;

            zero20 = 0x00;
            zero21 = 0x08;
            zero22 = 0x09;
            zero23 = 0xFC;

            command_dengsu[14] = speed * 429 / 256;//“15~16”位，对应1号电机（屈伸）速度值；
            //何志杰注释：buff_dengsu[14\15]屈伸方向电机角速度值，1°/s=429（十进制）？
            command_dengsu[15] = speed * 429 % 256;
            command_dengsu[16] = 0x00;  //“16~17”位，对应1号电机（屈伸）加速度值；
            command_dengsu[17] = 0xC0;
            command_dengsu[18] = 0x00;  //“18~19”位，对应1号电机（屈伸）减速度值；
            command_dengsu[19] = 0xC0;

            PtoN = false;//？
            is_initialized = true;
        }

        if (current_position >= citap)
        {
            command_dengsu[20] = negative20;
            command_dengsu[21] = negative21;
            command_dengsu[22] = negative22;
            command_dengsu[23] = negative23;
            PtoN = true;
            for (int i = 0; i < 79; i++)                    //和校验位
            {
                command_dengsu[79] = command_dengsu[79] + command_dengsu[i];
            }
            return command_dengsu;
        }

        else if (current_position <= (citan + 1) )//李振杰：为什么要加个1？
        {
            command_dengsu[20] = positive20;    //“20~23”位，对应1号电机（屈伸）位置值；
            command_dengsu[21] = positive21;
            command_dengsu[22] = positive22;
            command_dengsu[23] = positive23;
            PtoN = false;
            for (int i = 0; i < 79; i++)                    //和校验位
            {
                command_dengsu[79] = command_dengsu[79] + command_dengsu[i];
            }
            return command_dengsu;
        }



    }
    return command_dengsu;

}
