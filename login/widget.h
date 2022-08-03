#ifndef WIDGET_H
#define WIDGET_H

#include"dialog.h"
//#include"new_button.h"
//#include"icon_help.h"
namespace Ui {
class Widget;
}

//构建登陆界面
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    //事件过滤器：处理鼠标按下弹出小键盘
        bool eventFilter(QObject *obj, QEvent *event);
   // void mouseMoveEvent(QMouseEvent *e);//鼠标移动
   // void mousePressEvent(QMouseEvent *e);//鼠标按下移动

private slots://触发函数
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();
    //时间显示
    void timerUpdate(void);
    //登陆成功，关闭此界面，打开主系统界面
    void close_log(void);

    //数字输入
    void num_insert();
    //结束后关闭数据库连接
    void close_sql();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_11_clicked();

private:
    Ui::Widget *ui;    //登陆界面的UI
    //QPoint p;

    Dialog* dd;  //主界面作为登陆界面的成员存在，完成登陆后，登陆界面隐藏，主界面显示
    QTimer *timer;   //界面右下角时钟计时
    QTimer *timer1;   //登陆成功后界面切换计时
    QList<QPushButton*> num;   //输入虚拟键盘的按钮
    int user;   //此变量用于用户名和密码输入之间的判断
    int oksql;  //判断数据库连接是否成功




};

#endif // WIDGET_H
