#include "mythread.h"
#include<QDebug>


MyThread::MyThread(QObject *parent)
{

}


//辅助线程的运行函数，data1和data2轮流执行记录串口数据和存储功能，通过变量bigData.AorB判断哪方存储哪方记录，通过条件变量bigData.mut判断开始存储
void MyThread::run()
{
    while(1)
    {
        bigData.mut.lock();
        bigData.ok_insert.wait(&bigData.mut);
        try
        {
            if(bigData.test_or_train==0)  //存储的是测试数据
            {
                if(bigData.AorB==false)
                {
                    qDebug()<<bigData.AorB;
                    for(int i=0;i<100;i++)
                    {
                        sql->query->exec("insert into test_data values("+bigData.test_id+","+bigData.data2.current_time[i]+","+bigData.data2.F[0][i]+","+bigData.data2.F[1][i]+","+bigData.data2.F[2][i]+","+bigData.data2.F[3][i]+","+bigData.data2.F[4][i]+","+bigData.data2.F[5][i]+","+bigData.data2.var1[i]+","+bigData.data2.var2[i]+","+bigData.data2.var3[i]+","+bigData.data2.var4[i]+","+bigData.data2.var5[i]+","+bigData.data2.var6[i]+","+bigData.data2.displacement[i]+","+bigData.data2.ele_mach1[i]+","+bigData.data2.ele_mach2[i]+","+bigData.data2.ele_mach3[i]+","+bigData.data2.mach1_speed[i]+","+bigData.data2.mach2_speed[i]+","+bigData.data2.mach3_speed[i]+","+bigData.data2.gyro1[i]+","+bigData.data2.gyro2[i]+","+bigData.data2.gyro3[i]+")");
                    }
                }
                else if(bigData.AorB==true)
                {
                    qDebug()<<bigData.AorB;
                    for(int i=0;i<100;i++)
                    {
                        sql->query->exec("insert into test_data values("+bigData.test_id+","+bigData.data1.current_time[i]+","+bigData.data1.F[0][i]+","+bigData.data1.F[1][i]+","+bigData.data1.F[2][i]+","+bigData.data1.F[3][i]+","+bigData.data1.F[4][i]+","+bigData.data1.F[5][i]+","+bigData.data1.var1[i]+","+bigData.data1.var2[i]+","+bigData.data1.var3[i]+","+bigData.data1.var4[i]+","+bigData.data1.var5[i]+","+bigData.data1.var6[i]+","+bigData.data1.displacement[i]+","+bigData.data1.ele_mach1[i]+","+bigData.data1.ele_mach2[i]+","+bigData.data1.ele_mach3[i]+","+bigData.data1.mach1_speed[i]+","+bigData.data1.mach2_speed[i]+","+bigData.data1.mach3_speed[i]+","+bigData.data1.gyro1[i]+","+bigData.data1.gyro2[i]+","+bigData.data1.gyro3[i]+")");
                    }
                }
            }
            else if(bigData.test_or_train==1)  //存储的是训练数据
            {
                if(bigData.AorB==false)
                {
                    qDebug()<<bigData.AorB;
                    for(int i=0;i<100;i++)
                    {
                        sql->query->exec("insert into train_dataa values("+bigData.train_id+","+bigData.data2.current_time[i]+","+bigData.data2.F[0][i]+","+bigData.data2.F[1][i]+","+bigData.data2.F[2][i]+","+bigData.data2.F[3][i]+","+bigData.data2.F[4][i]+","+bigData.data2.F[5][i]+","+bigData.data2.var1[i]+","+bigData.data2.var2[i]+","+bigData.data2.var3[i]+","+bigData.data2.var4[i]+","+bigData.data2.var5[i]+","+bigData.data2.var6[i]+","+bigData.data2.displacement[i]+","+bigData.data2.ele_mach1[i]+","+bigData.data2.ele_mach2[i]+","+bigData.data2.ele_mach3[i]+","+bigData.data2.mach1_speed[i]+","+bigData.data2.mach2_speed[i]+","+bigData.data2.mach3_speed[i]+","+bigData.data2.gyro1[i]+","+bigData.data2.gyro2[i]+","+bigData.data2.gyro3[i]+")");
                    }
                }
                else if(bigData.AorB==true)
                {
                    qDebug()<<bigData.AorB;
                    for(int i=0;i<100;i++)
                    {
                        sql->query->exec("insert into train_data values("+bigData.train_id+","+bigData.data1.current_time[i]+","+bigData.data1.F[0][i]+","+bigData.data1.F[1][i]+","+bigData.data1.F[2][i]+","+bigData.data1.F[3][i]+","+bigData.data1.F[4][i]+","+bigData.data1.F[5][i]+","+bigData.data1.var1[i]+","+bigData.data1.var2[i]+","+bigData.data1.var3[i]+","+bigData.data1.var4[i]+","+bigData.data1.var5[i]+","+bigData.data1.var6[i]+","+bigData.data1.displacement[i]+","+bigData.data1.ele_mach1[i]+","+bigData.data1.ele_mach2[i]+","+bigData.data1.ele_mach3[i]+","+bigData.data1.mach1_speed[i]+","+bigData.data1.mach2_speed[i]+","+bigData.data1.mach3_speed[i]+","+bigData.data1.gyro1[i]+","+bigData.data1.gyro2[i]+","+bigData.data1.gyro3[i]+")");
                    }
                }
            }
        }
        catch(std::exception e)
        {
            qDebug()<<e.what();
        }

        bigData.mut.unlock();
    }

}

