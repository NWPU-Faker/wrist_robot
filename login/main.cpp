#include "widget.h"
#include"dialog.h"
#include <QApplication>


#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>

//项目的主函数，即启动函数，此函数首先创建一个Application应用（即项目，包括后续的登陆界面和用户界面都是属于项目的），然后创建登陆界面的对象
int main(int argc, char *argv[])
{

    //创建应用
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);


    //创建登陆界面对象
    Widget *w=new Widget();
    //将登陆界面设置为显示
    w->show();





    return a.exec();
}
