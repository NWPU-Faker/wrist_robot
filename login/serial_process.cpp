#include<serial_process.h>
#include<QString>
#include<QDebug>


void SerialProcess::ini_all(int test_category)
{
    //buff_dengsu
    //buff_dengchang
    //buff_dengzhang
    for(int i=0;i<81;i++)
    {
        inital[i]=0;
    }
    buff_dengsu=inital;
    buff_dengchang=inital;
    buff_dengzhang=inital;
    buff_huodong_qushen=inital;
    buff_huodong_chirao=inital;
    buff_huodong_huizhuan=inital;


    //buff_huodong默认值设置
    if(test_category==0)
    {
        buff_huodong_qushen[0]=0xfa;
        buff_huodong_qushen[80]=0xfb;
        buff_huodong_qushen[1]=0x01;
        buff_huodong_qushen[2]=0x02;
        buff_huodong_qushen[3]=0x09;
        buff_huodong_qushen[4]=0x03;
        buff_huodong_qushen[5]=0x01;
        buff_huodong_qushen[15]=0x0A;
        //电机加速度设置根据通讯协议表对应位数值设置
        buff_huodong_qushen[16]=0;
        buff_huodong_qushen[17]=50;
        buff_huodong_qushen[18]=0;
        buff_huodong_qushen[19]=50;
        for(int i=0;i<79;i++)
        {
            buff_huodong_qushen[79]=buff_huodong_qushen[79]+buff_huodong_qushen[i];
        }
    }

    //buff_dengzhang默认值设置
    else if(test_category==2)
    {
        buff_dengzhang[0]=0xfa;
        buff_dengzhang[80]=0xfb;
        buff_dengzhang[1]=0x01;
        buff_dengzhang[2]=0x02;
        buff_dengzhang[3]=0x07;//历史遗留问题
        buff_dengzhang[5]=0x01;
    }

    //buff_dengsu默认值设置
    else if(test_category==1)
    {
        buff_dengsu[0]=0xfa;
        buff_dengsu[80]=0xfb;
        buff_dengsu[1]=0x01;
        buff_dengsu[2]=0x02;
        buff_dengsu[3]=0x07;//历史遗留问题
        buff_dengsu[5]=0x01;
    }
    PtoN=0;
}



QByteArray SerialProcess::dengsu(QString citann,QString citapp,QString speedd,int dir,float position_now)
{

    int citan=citann.toInt();
    int citap=citapp.toInt();
    int speed=speedd.toInt();
    //qDebug()<<position_now<<citan<<citap;

    //buff_dengsu[4]运动方向选择，0x01尺桡偏 0x02屈伸 0x03回转
    if(dir==0)   //尺桡偏等速运动参数设置
    {
        if(ini==0)
        {
            //运动方向选择
            buff_dengsu[4]=0x01;
            //正运动范围
            int p_maichong =zero_chirao-val_pers_chirao*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            //负运动范围
            int n_maichong =zero_chirao-val_pers_chirao*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            //零点位置
            zero20=0x00;
            zero21=0x04;
            zero22=0x38;
            zero23=0x90;

            //加速度
            buff_dengsu[35]=0x00;
            buff_dengsu[36]=0xC0;
            buff_dengsu[37]=0x00;
            buff_dengsu[38]=0xC0;

            //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
            buff_dengsu[33]=speed*429/256;
            buff_dengsu[34]=speed*429%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {
                buff_dengsu[39]=negative20;
                buff_dengsu[40]=negative21;
                buff_dengsu[41]=negative22;
                buff_dengsu[42]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {
                buff_dengsu[39]=postive20;
                buff_dengsu[40]=postive21;
                buff_dengsu[41]=postive22;
                buff_dengsu[42]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {
                if(PtoN==1)
                {
                    buff_dengsu[39]=negative20;
                    buff_dengsu[40]=negative21;
                    buff_dengsu[41]=negative22;
                    buff_dengsu[42]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[39]=postive20;
                    buff_dengsu[40]=postive21;
                    buff_dengsu[41]=postive22;
                    buff_dengsu[42]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }

    }

    if(dir==1)   //屈伸等速运动参数设置
    {

        if(ini==0)
        {
            buff_dengsu[4]=0x02;
            int p_maichong =zero_qushen-val_pers_qushen*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_qushen-val_pers_qushen*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x08;
            zero22=0x09;
            zero23=0xfc;

            //加速度
            buff_dengsu[16]=0x00;
            buff_dengsu[17]=0xC0;
            buff_dengsu[18]=0x00;
            buff_dengsu[19]=0xC0;

            //buff_dengsu[14\15]屈伸方向电机角速度值，1°/s=429（十进制）
            buff_dengsu[14]=speed*429/256;
            buff_dengsu[15]=speed*429%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {

                buff_dengsu[20]=negative20;
                buff_dengsu[21]=negative21;
                buff_dengsu[22]=negative22;
                buff_dengsu[23]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {

                buff_dengsu[20]=postive20;
                buff_dengsu[21]=postive21;
                buff_dengsu[22]=postive22;
                buff_dengsu[23]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {

                if(PtoN==1)
                {
                    buff_dengsu[20]=negative20;
                    buff_dengsu[21]=negative21;
                    buff_dengsu[22]=negative22;
                    buff_dengsu[23]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[20]=postive20;
                    buff_dengsu[21]=postive21;
                    buff_dengsu[22]=postive22;
                    buff_dengsu[23]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }

    }

    if(dir==2)   //回转等速运动参数设置
    {
        if(ini==0)
        {
            buff_dengsu[4]=0x03;
            int p_maichong =zero_huizhuan-val_pers_huizhuan*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_huizhuan-val_pers_huizhuan*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x38;
            zero22=0xbf;
            zero23=0xcf;

            //加速度
            buff_dengsu[54]=0x00;
            buff_dengsu[55]=0xC0;
            buff_dengsu[56]=0x00;
            buff_dengsu[57]=0xC0;

            //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
            buff_dengsu[52]=speed*2696/256;
            buff_dengsu[53]=speed*2696%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {
                buff_dengsu[58]=negative20;
                buff_dengsu[59]=negative21;
                buff_dengsu[60]=negative22;
                buff_dengsu[61]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {
                buff_dengsu[58]=postive20;
                buff_dengsu[59]=postive21;
                buff_dengsu[60]=postive22;
                buff_dengsu[61]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {
                if(PtoN==1)
                {
                    buff_dengsu[58]=negative20;
                    buff_dengsu[59]=negative21;
                    buff_dengsu[60]=negative22;
                    buff_dengsu[61]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[58]=postive20;
                    buff_dengsu[59]=postive21;
                    buff_dengsu[60]=postive22;
                    buff_dengsu[61]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }
    }
    return buff_dengsu;
}




QByteArray SerialProcess::dengzhang(QString citann,QString citapp,int dir,int speed,float force)
{
    int citan=citann.toInt();
    int citap=citapp.toInt();

    //buff_dengsu[4]运动方向选择，0x01尺桡偏 0x02屈伸 0x03回转

    if(dir==0)   //尺桡偏等张运动参数设置
    {

        if(ini==0)
        {
            //运动方向选择
            buff_dengsu[4]=0x01;
            //正运动范围
            int p_maichong =zero_chirao-val_pers_chirao*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            //负运动范围
            int n_maichong =zero_chirao-val_pers_chirao*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            //零点位置
            zero20=0x00;
            zero21=0x04;
            zero22=0x38;
            zero23=0x90;

            //加速度
            buff_dengsu[35]=0x00;
            buff_dengsu[36]=0xC0;
            buff_dengsu[37]=0x00;
            buff_dengsu[38]=0xC0;

            ini=1;
        }


            if(force<0)
            {
                buff_dengsu[39]=negative20;
                buff_dengsu[40]=negative21;
                buff_dengsu[41]=negative22;
                buff_dengsu[42]=negative23;
                //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
                buff_dengsu[34]=speed*429%256;
                buff_dengsu[33]=speed*429/256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengsu;
            }
            else if(force>0)
            {
                buff_dengsu[39]=postive20;
                buff_dengsu[40]=postive21;
                buff_dengsu[41]=postive22;
                buff_dengsu[42]=postive23;
                //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
                buff_dengsu[34]=speed*429%256;
                buff_dengsu[33]=speed*429/256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengsu;
            }

    }

    if(dir==1)   //屈伸等速运动参数设置
    {

        if(ini==0)
        {
            buff_dengzhang[4]=0x02;
            int p_maichong =zero_qushen-val_pers_qushen*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_qushen-val_pers_qushen*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x08;
            zero22=0x09;
            zero23=0xfc;

            //加速度
            buff_dengzhang[16]=0x00;
            buff_dengzhang[17]=0xC0;
            buff_dengzhang[18]=0x00;
            buff_dengzhang[19]=0xC0;




            ini=1;
        }


            if(force<0)
            {

                buff_dengzhang[20]=negative20;
                buff_dengzhang[21]=negative21;
                buff_dengzhang[22]=negative22;
                buff_dengzhang[23]=negative23;
                //buff_dengzhang[14\15]屈伸方向电机角速度值，1°/s=429（十进制）
                buff_dengzhang[15]=speed*429%256;
                buff_dengzhang[14]=speed*429/256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengzhang;
            }
            else if(force>0)
            {

                buff_dengzhang[20]=postive20;
                buff_dengzhang[21]=postive21;
                buff_dengzhang[22]=postive22;
                buff_dengzhang[23]=postive23;
                //buff_dengzhang[14\15]屈伸方向电机角速度值，1°/s=429（十进制）
                buff_dengzhang[15]=speed*429%256;
                buff_dengzhang[14]=speed*429/256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengzhang;
            }
    }

    if(dir==2)   //回转等速运动参数设置
    {

        if(ini==0)
        {
            buff_dengzhang[4]=0x03;
            int p_maichong =zero_huizhuan-val_pers_huizhuan*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_huizhuan-val_pers_huizhuan*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x38;
            zero22=0xbf;
            zero23=0xcf;

            //加速度
            buff_dengzhang[54]=0x00;
            buff_dengzhang[55]=0xC0;
            buff_dengzhang[56]=0x00;
            buff_dengzhang[57]=0xC0;




            ini=1;
        }


            if(force>0)
            {
                buff_dengzhang[58]=negative20;
                buff_dengzhang[59]=negative21;
                buff_dengzhang[60]=negative22;
                buff_dengzhang[61]=negative23;
                //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
                buff_dengzhang[52]=speed*2696/256;
                buff_dengzhang[53]=speed*2696%256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengzhang;
            }
            else if(force<0)
            {
                buff_dengzhang[58]=postive20;
                buff_dengzhang[59]=postive21;
                buff_dengzhang[60]=postive22;
                buff_dengzhang[61]=postive23;
                //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
                buff_dengzhang[52]=speed*2696/256;
                buff_dengzhang[53]=speed*2696%256;

                for(int i=0;i<79;i++)
                {
                    buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                }
                return buff_dengzhang;
            }            
    }
    return buff_dengzhang;
}



QByteArray SerialProcess::dengchang(QString citann,QString citapp,int dir,float position_now)
{
    //qDebug()<<position_now;
    int citan=citann.toInt();
    int citap=citapp.toInt();
    int speed=5;

    //buff_dengsu[4]运动方向选择，0x01尺桡偏 0x02屈伸 0x03回转
    if(dir==0)   //尺桡偏等速运动参数设置
    {
        if(ini==0)
        {
            //运动方向选择
            buff_dengsu[4]=0x01;
            //正运动范围
            int p_maichong =zero_chirao-val_pers_chirao*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            //负运动范围
            int n_maichong =zero_chirao-val_pers_chirao*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            //零点位置
            zero20=0x00;
            zero21=0x04;
            zero22=0x38;
            zero23=0x90;

            //加速度
            buff_dengsu[35]=0x00;
            buff_dengsu[36]=0xC0;
            buff_dengsu[37]=0x00;
            buff_dengsu[38]=0xC0;

            //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
            buff_dengsu[33]=speed*429/256;
            buff_dengsu[34]=speed*429%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {
                buff_dengsu[39]=negative20;
                buff_dengsu[40]=negative21;
                buff_dengsu[41]=negative22;
                buff_dengsu[42]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {
                buff_dengsu[39]=postive20;
                buff_dengsu[40]=postive21;
                buff_dengsu[41]=postive22;
                buff_dengsu[42]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {
                if(PtoN==1)
                {
                    buff_dengsu[39]=negative20;
                    buff_dengsu[40]=negative21;
                    buff_dengsu[41]=negative22;
                    buff_dengsu[42]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[39]=postive20;
                    buff_dengsu[40]=postive21;
                    buff_dengsu[41]=postive22;
                    buff_dengsu[42]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }

    }

    if(dir==1)   //屈伸等速运动参数设置
    {

        if(ini==0)
        {
            buff_dengsu[4]=0x02;
            int p_maichong =zero_qushen-val_pers_qushen*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_qushen-val_pers_qushen*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x08;
            zero22=0x09;
            zero23=0xfc;

            //加速度
            buff_dengsu[16]=0x00;
            buff_dengsu[17]=0xC0;
            buff_dengsu[18]=0x00;
            buff_dengsu[19]=0xC0;

            //buff_dengsu[14\15]屈伸方向电机角速度值，1°/s=429（十进制）
            buff_dengsu[14]=speed*429/256;
            buff_dengsu[15]=speed*429%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {

                buff_dengsu[20]=negative20;
                buff_dengsu[21]=negative21;
                buff_dengsu[22]=negative22;
                buff_dengsu[23]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {

                buff_dengsu[20]=postive20;
                buff_dengsu[21]=postive21;
                buff_dengsu[22]=postive22;
                buff_dengsu[23]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {

                if(PtoN==1)
                {
                    buff_dengsu[20]=negative20;
                    buff_dengsu[21]=negative21;
                    buff_dengsu[22]=negative22;
                    buff_dengsu[23]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[20]=postive20;
                    buff_dengsu[21]=postive21;
                    buff_dengsu[22]=postive22;
                    buff_dengsu[23]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }

    }

    if(dir==2)   //回转等速运动参数设置
    {
        if(ini==0)
        {
            buff_dengsu[4]=0x03;
            int p_maichong =zero_huizhuan-val_pers_huizhuan*citap;
            int p_head4=p_maichong/65536;
            int p_late4=p_maichong%65536;
            postive20=p_head4/256;
            postive21=p_head4%256;
            postive22=p_late4/256;
            postive23=p_late4%256;

            int n_maichong =zero_huizhuan-val_pers_huizhuan*citan;
            int n_head4=n_maichong/65536;
            int n_late4=n_maichong%65536;
            negative20=n_head4/256;
            negative21=n_head4%256;
            negative22=n_late4/256;
            negative23=n_late4%256;

            zero20=0x00;
            zero21=0x38;
            zero22=0xbf;
            zero23=0xcf;

            //加速度
            buff_dengsu[54]=0x00;
            buff_dengsu[55]=0xC0;
            buff_dengsu[56]=0x00;
            buff_dengsu[57]=0xC0;

            //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
            buff_dengsu[52]=speed*2696/256;
            buff_dengsu[53]=speed*2696%256;


            PtoN=0;
            ini=1;
        }


            if(position_now>=citap)
            {
                buff_dengsu[58]=negative20;
                buff_dengsu[59]=negative21;
                buff_dengsu[60]=negative22;
                buff_dengsu[61]=negative23;
                PtoN=1;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now<=(citan+1))
            {
                buff_dengsu[58]=postive20;
                buff_dengsu[59]=postive21;
                buff_dengsu[60]=postive22;
                buff_dengsu[61]=postive23;
                PtoN=0;
                for(int i=0;i<79;i++)
                {
                    buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                }
                return buff_dengsu;
            }
            else if(position_now>citan&&position_now<citap)
            {
                if(PtoN==1)
                {
                    buff_dengsu[58]=negative20;
                    buff_dengsu[59]=negative21;
                    buff_dengsu[60]=negative22;
                    buff_dengsu[61]=negative23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
                else if(PtoN==0)
                {
                    buff_dengsu[58]=postive20;
                    buff_dengsu[59]=postive21;
                    buff_dengsu[60]=postive22;
                    buff_dengsu[61]=postive23;
                    for(int i=0;i<79;i++)
                    {
                        buff_dengsu[79]=buff_dengsu[79]+buff_dengsu[i];
                    }
                    return buff_dengsu;
                }
            }
    }
    return buff_dengsu;
}

QByteArray SerialProcess::huodong(int num_range_direction,int speed,float force)
{
    int citan=-200;
    int citap=200;
    if(num_range_direction==0)  //尺桡偏
    {
            if(ini==0)
            {
                //运动方向选择
                buff_dengsu[4]=0x01;
                //正运动范围
                int p_maichong =zero_chirao-val_pers_chirao*citap;
                int p_head4=p_maichong/65536;
                int p_late4=p_maichong%65536;
                postive20=p_head4/256;
                postive21=p_head4%256;
                postive22=p_late4/256;
                postive23=p_late4%256;

                //负运动范围
                int n_maichong =zero_chirao-val_pers_chirao*citan;
                int n_head4=n_maichong/65536;
                int n_late4=n_maichong%65536;
                negative20=n_head4/256;
                negative21=n_head4%256;
                negative22=n_late4/256;
                negative23=n_late4%256;

                //零点位置
                zero20=0x00;
                zero21=0x04;
                zero22=0x38;
                zero23=0x90;

                //加速度
                buff_dengsu[35]=0x00;
                buff_dengsu[36]=0xC0;
                buff_dengsu[37]=0x00;
                buff_dengsu[38]=0xC0;

                ini=1;
            }


                if(force<0)
                {
                    buff_dengsu[39]=negative20;
                    buff_dengsu[40]=negative21;
                    buff_dengsu[41]=negative22;
                    buff_dengsu[42]=negative23;
                    //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
                    buff_dengsu[34]=speed*429%256;
                    buff_dengsu[33]=speed*429/256;

                    for(int i=0;i<79;i++)
                    {
                        buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                    }
                    return buff_dengsu;
                }
                else if(force>0)
                {
                    buff_dengsu[39]=postive20;
                    buff_dengsu[40]=postive21;
                    buff_dengsu[41]=postive22;
                    buff_dengsu[42]=postive23;
                    //buff_dengsu[33\34]尺桡偏方向电机角速度值，1°/s=429（十进制）
                    buff_dengsu[34]=speed*429%256;
                    buff_dengsu[33]=speed*429/256;

                    for(int i=0;i<79;i++)
                    {
                        buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                    }
                    return buff_dengsu;
                }
    }
    else if(num_range_direction==1)
    {
        return buff_huodong_qushen;
    }
    else if(num_range_direction==2)  //回转
    {
            if(ini==0)
            {
                buff_dengzhang[4]=0x03;
                int p_maichong =zero_huizhuan-val_pers_huizhuan*citap;
                int p_head4=p_maichong/65536;
                int p_late4=p_maichong%65536;
                postive20=p_head4/256;
                postive21=p_head4%256;
                postive22=p_late4/256;
                postive23=p_late4%256;

                int n_maichong =zero_huizhuan-val_pers_huizhuan*citan;
                int n_head4=n_maichong/65536;
                int n_late4=n_maichong%65536;
                negative20=n_head4/256;
                negative21=n_head4%256;
                negative22=n_late4/256;
                negative23=n_late4%256;

                zero20=0x00;
                zero21=0x38;
                zero22=0xbf;
                zero23=0xcf;

                //加速度
                buff_dengzhang[54]=0x00;
                buff_dengzhang[55]=0xC0;
                buff_dengzhang[56]=0x00;
                buff_dengzhang[57]=0xC0;
                ini=1;
            }


                if(force>0)
                {
                    buff_dengzhang[58]=negative20;
                    buff_dengzhang[59]=negative21;
                    buff_dengzhang[60]=negative22;
                    buff_dengzhang[61]=negative23;
                    //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
                    buff_dengzhang[52]=speed*2696/256;
                    buff_dengzhang[53]=speed*2696%256;

                    for(int i=0;i<79;i++)
                    {
                        buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                    }
                    return buff_dengzhang;
                }
                else if(force<0)
                {
                    buff_dengzhang[58]=postive20;
                    buff_dengzhang[59]=postive21;
                    buff_dengzhang[60]=postive22;
                    buff_dengzhang[61]=postive23;
                    //buff_dengsu[52\53]回转方向电机角速度值，1°/s=2696（十进制）
                    buff_dengzhang[52]=speed*2696/256;
                    buff_dengzhang[53]=speed*2696%256;

                    for(int i=0;i<79;i++)
                    {
                        buff_dengzhang[79]=buff_dengzhang[79]+buff_dengzhang[i];
                    }
                    return buff_dengzhang;
                }
        }
        return buff_dengzhang;

}
