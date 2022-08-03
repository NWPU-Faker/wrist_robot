/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFrame *frame;
    QLineEdit *username;
    QLineEdit *password;
    QLabel *label;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QWidget *widget;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *widget_2;
    QPushButton *pushButton_01;
    QPushButton *pushButton_02;
    QPushButton *pushButton_03;
    QPushButton *pushButton_00;
    QPushButton *pushButton_04;
    QPushButton *pushButton_07;
    QPushButton *pushButton_05;
    QPushButton *pushButton_06;
    QPushButton *pushButton_11;
    QPushButton *pushButton_08;
    QPushButton *pushButton_09;
    QPushButton *pushButton_14;
    QWidget *widget_3;
    QLabel *label_8;
    QLabel *sqlok;
    QWidget *widget_4;
    QLabel *label_9;
    QLabel *sqlok_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1280, 800);
        QFont font;
        Widget->setFont(font);
        Widget->setStyleSheet(QString::fromUtf8("\n"
"#Widget{\n"
"\n"
"background:rgb(255, 255, 255);\n"
"font-size:15px;\n"
"font-style:MingLiU-ExtB;\n"
"\n"
"}\n"
"QFrame{\n"
"border:sold 10px rgba(0,0,0);\n"
"	border-image: url(:/new/prefix1/2.231.jpg);\n"
"}\n"
"QLabel{\n"
"border-image:rgba(85,170,25);\n"
"color:white;\n"
"font-style:MingLiU-ExtB;\n"
"font-size:14px;\n"
"}\n"
"QPushButton{\n"
"background:#ced1d8;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-color: rgb(255, 85, 0);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"\n"
""));
        frame = new QFrame(Widget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1280, 800));
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        username = new QLineEdit(frame);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(960, 330, 271, 61));
        username->setStyleSheet(QString::fromUtf8("\n"
"color:#8d98a1;\n"
"background-color:rgba(255, 255, 255, 35%);\n"
"font-size:20px;\n"
"border-style:outset;\n"
"border-radius:14px;\n"
"font-style:MingLiU-ExtB;\n"
"\n"
"color: rgb(255, 255, 255);\n"
"font: 16pt \"\351\273\221\344\275\223\";"));
        password = new QLineEdit(frame);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(960, 410, 271, 61));
        password->setStyleSheet(QString::fromUtf8("\n"
"color:#8d98a1;\n"
"background-color:rgba(255, 255, 255, 35%);\n"
"font-size:20px;\n"
"border-style:outset;\n"
"border-radius:14px;\n"
"font-style:MingLiU-ExtB;\n"
"\n"
"color: rgb(255, 255, 255);\n"
"font: 16pt \"\351\273\221\344\275\223\";"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 181, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"\351\273\221\344\275\223\";\n"
""));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(955, 510, 251, 61));
        pushButton->setStyleSheet(QString::fromUtf8("font: 27pt \"\351\273\221\344\275\223\";\n"
"color: rgb(0, 170, 255);"));
        toolButton = new QToolButton(frame);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(1130, 20, 50, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe Myungjo Std M"));
        font2.setPointSize(11);
        toolButton->setFont(font2);
        toolButton->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"background:#ced1d8;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}"));
        toolButton_2 = new QToolButton(frame);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(1200, 20, 50, 50));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Adobe Myungjo Std M"));
        font3.setPointSize(12);
        toolButton_2->setFont(font3);
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton{\n"
"\n"
"	background-color: rgb(255, 5, 9,80%);\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}"));
        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(430, 240, 431, 311));
        widget->setStyleSheet(QString::fromUtf8("#widget{background-color: rgb(176, 184, 183,65%);\n"
"border-radius:20px;\n"
"}\n"
"QPushButton{\n"
"\n"
"font: 22pt \"\351\273\221\344\275\223\";\n"
"background-color: rgb(119, 150, 179);\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-color: rgb(170, 219, 226);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"\n"
"}"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 20, 141, 91));
        label_2->setStyleSheet(QString::fromUtf8("font: 26pt \"\351\273\221\344\275\223\";"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 110, 261, 71));
        label_4->setStyleSheet(QString::fromUtf8("font: 22pt \"\351\273\221\344\275\223\";"));
        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 210, 141, 71));
        pushButton_2->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1000, 750, 241, 41));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Times New Roman"));
        font4.setPointSize(18);
        font4.setBold(false);
        font4.setItalic(false);
        label_3->setFont(font4);
        label_3->setStyleSheet(QString::fromUtf8("\n"
"font: 18pt \"Times New Roman\";"));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(910, 340, 61, 51));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(910, 410, 61, 61));
        widget_2 = new QWidget(frame);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(430, 430, 421, 326));
        widget_2->setStyleSheet(QString::fromUtf8("#widget_2{background-color: rgb(176, 184, 183,65%);\n"
"\n"
"border-radius:20px;\n"
"}\n"
"QPushButton{\n"
"\n"
"font: 40pt \"\351\273\221\344\275\223\";\n"
"\n"
"background-color: rgb(54, 54, 54,50%);\n"
"\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"background-color: rgb(170, 219, 226);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"\n"
"}"));
        pushButton_01 = new QPushButton(widget_2);
        pushButton_01->setObjectName(QString::fromUtf8("pushButton_01"));
        pushButton_01->setGeometry(QRect(15, 20, 90, 90));
        pushButton_01->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_02 = new QPushButton(widget_2);
        pushButton_02->setObjectName(QString::fromUtf8("pushButton_02"));
        pushButton_02->setGeometry(QRect(115, 20, 90, 90));
        pushButton_02->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_03 = new QPushButton(widget_2);
        pushButton_03->setObjectName(QString::fromUtf8("pushButton_03"));
        pushButton_03->setGeometry(QRect(215, 20, 90, 90));
        pushButton_03->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_00 = new QPushButton(widget_2);
        pushButton_00->setObjectName(QString::fromUtf8("pushButton_00"));
        pushButton_00->setGeometry(QRect(315, 20, 90, 90));
        pushButton_00->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_04 = new QPushButton(widget_2);
        pushButton_04->setObjectName(QString::fromUtf8("pushButton_04"));
        pushButton_04->setGeometry(QRect(15, 120, 90, 90));
        pushButton_04->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_07 = new QPushButton(widget_2);
        pushButton_07->setObjectName(QString::fromUtf8("pushButton_07"));
        pushButton_07->setGeometry(QRect(15, 220, 90, 90));
        pushButton_07->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_05 = new QPushButton(widget_2);
        pushButton_05->setObjectName(QString::fromUtf8("pushButton_05"));
        pushButton_05->setGeometry(QRect(115, 120, 90, 90));
        pushButton_05->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_06 = new QPushButton(widget_2);
        pushButton_06->setObjectName(QString::fromUtf8("pushButton_06"));
        pushButton_06->setGeometry(QRect(215, 120, 90, 90));
        pushButton_06->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_11 = new QPushButton(widget_2);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(315, 120, 90, 90));
        pushButton_11->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_08 = new QPushButton(widget_2);
        pushButton_08->setObjectName(QString::fromUtf8("pushButton_08"));
        pushButton_08->setGeometry(QRect(115, 220, 90, 90));
        pushButton_08->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_09 = new QPushButton(widget_2);
        pushButton_09->setObjectName(QString::fromUtf8("pushButton_09"));
        pushButton_09->setGeometry(QRect(215, 220, 90, 90));
        pushButton_09->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"border-width: 1px;\n"
"border-style: solid;"));
        pushButton_14 = new QPushButton(widget_2);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(315, 220, 90, 90));
        pushButton_14->setStyleSheet(QString::fromUtf8("border-color: rgb(59, 94, 94);\n"
"font: 30pt \"\351\273\221\344\275\223\";\n"
"border-width: 1px;\n"
"border-style: solid;"));
        widget_3 = new QWidget(frame);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(490, 20, 380, 81));
        widget_3->setStyleSheet(QString::fromUtf8("#widget_3{background-color: rgb(176, 184, 183,65%);\n"
"border-radius:20px;\n"
"}\n"
""));
        label_8 = new QLabel(widget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 5, 260, 71));
        label_8->setStyleSheet(QString::fromUtf8("font: 22pt \"\351\273\221\344\275\223\";"));
        sqlok = new QLabel(widget_3);
        sqlok->setObjectName(QString::fromUtf8("sqlok"));
        sqlok->setGeometry(QRect(30, 20, 51, 51));
        widget_4 = new QWidget(frame);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(490, 20, 380, 81));
        widget_4->setStyleSheet(QString::fromUtf8("#widget_4{background-color: rgb(176, 184, 183,65%);\n"
"border-radius:20px;\n"
"}\n"
""));
        label_9 = new QLabel(widget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(100, 5, 260, 71));
        label_9->setStyleSheet(QString::fromUtf8("font: 22pt \"\351\273\221\344\275\223\";"));
        sqlok_2 = new QLabel(widget_4);
        sqlok_2->setObjectName(QString::fromUtf8("sqlok_2"));
        sqlok_2->setGeometry(QRect(30, 20, 51, 51));
        widget->raise();
        username->raise();
        password->raise();
        pushButton->raise();
        toolButton->raise();
        toolButton_2->raise();
        label_3->raise();
        label_5->raise();
        label_6->raise();
        widget_2->raise();
        widget_3->raise();
        widget_4->raise();
        label->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        username->setPlaceholderText(QCoreApplication::translate("Widget", " \347\224\250\346\210\267\345\220\215", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("Widget", " \345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\245\277\345\214\227\345\267\245\344\270\232\345\244\247\345\255\246", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        toolButton->setText(QCoreApplication::translate("Widget", "-", nullptr));
        toolButton_2->setText(QCoreApplication::translate("Widget", "X", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\346\217\220  \347\244\272", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215\346\210\226\345\257\206\347\240\201\351\224\231\350\257\257", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\347\241\256 \345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "Time loading...", nullptr));
        pushButton_01->setText(QCoreApplication::translate("Widget", "1", nullptr));
        pushButton_02->setText(QCoreApplication::translate("Widget", "2", nullptr));
        pushButton_03->setText(QCoreApplication::translate("Widget", "3", nullptr));
        pushButton_00->setText(QCoreApplication::translate("Widget", "0", nullptr));
        pushButton_04->setText(QCoreApplication::translate("Widget", "4", nullptr));
        pushButton_07->setText(QCoreApplication::translate("Widget", "7", nullptr));
        pushButton_05->setText(QCoreApplication::translate("Widget", "5", nullptr));
        pushButton_06->setText(QCoreApplication::translate("Widget", "6", nullptr));
        pushButton_11->setText(QCoreApplication::translate("Widget", "\342\206\220", nullptr));
        pushButton_08->setText(QCoreApplication::translate("Widget", "8", nullptr));
        pushButton_09->setText(QCoreApplication::translate("Widget", "9", nullptr));
        pushButton_14->setText(QCoreApplication::translate("Widget", "\347\241\256\345\256\232", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245\346\210\220\345\212\237", nullptr));
        sqlok->setText(QString());
        label_9->setText(QCoreApplication::translate("Widget", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245\345\244\261\350\264\245", nullptr));
        sqlok_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
