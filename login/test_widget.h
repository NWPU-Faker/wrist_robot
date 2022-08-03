#ifndef TEST_WIDGET_H
#define TEST_WIDGET_H
//#include"icon_help.h"
#include"new_button.h"


class test_widget : public QWidget
{
    Q_OBJECT

public:
    explicit test_widget(QWidget *parent = 0);
    ~test_widget();
private slots:
    void initForm();
    void buttonClick3();
private:
    QList<New_Button*> btn2;

};

#endif // TEST_WIDGET_H
