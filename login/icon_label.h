#ifndef ICON_LABEL_H
#define ICON_LABEL_H
#include<QLabel>
class icon_label:public QLabel
{
public:
    explicit icon_label(QWidget *parent = 0);
    void paintevent(QPainter* p);

};

#endif // ICON_LABEL_H
