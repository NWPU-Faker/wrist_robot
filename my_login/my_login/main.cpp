#include "widget.h"

#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    /*
    QByteArray zero_array;
    for (int i = 0; i < 81; i++)
    {
        zero_array[i] = 0;
    }
    qDebug() << zero_array ;
    qDebug() << zero_array[80] +  17 ;
    */

    return a.exec();
}
