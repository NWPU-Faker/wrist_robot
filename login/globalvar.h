#ifndef GLOBALVAR_H
#define GLOBALVAR_H


#include <QMutex>
#include <QWaitCondition>
#include<QString>

//此全局变量用于存储下位机传输来的采集数据，一个Data变量对象可以存储100包数据
struct Data{
    QString current_time[100];

    QString F[6][100];  //六维力数据

    //握力传感器与扭矩传感器、位移传感器
    QString var1[100];
    QString var2[100];
    QString var3[100];
    QString var4[100];
    QString var5[100];
    QString var6[100];
    QString displacement[100];


    //三个电机的位置角度值
    QString ele_mach1[100];
    QString ele_mach2[100];
    QString ele_mach3[100];


    //三个电机的速度值
    QString mach1_speed[100];
    QString mach2_speed[100];
    QString mach3_speed[100];



    //陀螺仪度数
    QString gyro1[100];
    QString gyro2[100];
    QString gyro3[100];

    //emg信号数据添加位置

};
//为线程的同步所设的结构体全局变量，包含互斥量，条件变量，全局变量Data和一些判断用的bool值
struct myData{
   QMutex mut ;   //互斥量
   QWaitCondition ok_insert;   //条件变量
   QString test_id;  //测试编号
   QString train_id;  //训练编号
   QString category;   //运动类别
   Data data1;   //全局变量Data
   Data data2;    //全局变量Data
   bool AorB;//两个线程轮流使用
   bool test_or_train;  //判断是测试或训练
};

//声明全局变量
extern myData bigData;




#endif // GLOBALVAR_H

//线程条件变量
