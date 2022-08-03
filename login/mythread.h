#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include "globalvar.h"
#include"mysql.h"

class MyThread:public QThread
{
    Q_OBJECT
public:
    MyThread(QObject* parent = nullptr);



protected:
    void run() override;
};

#endif // MYTHREAD_H
