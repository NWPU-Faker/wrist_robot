/********************************************************************************
** Form generated from reading UI file 'frmlunarcalendarwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMLUNARCALENDARWIDGET_H
#define UI_FRMLUNARCALENDARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <lunarcalendarwidget.h>

QT_BEGIN_NAMESPACE

class Ui_frmLunarCalendarWidget
{
public:
    QVBoxLayout *verticalLayout;
    LunarCalendarWidget *widget;

    void setupUi(QWidget *frmLunarCalendarWidget)
    {
        if (frmLunarCalendarWidget->objectName().isEmpty())
            frmLunarCalendarWidget->setObjectName(QStringLiteral("frmLunarCalendarWidget"));
        frmLunarCalendarWidget->resize(760, 627);
        frmLunarCalendarWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(frmLunarCalendarWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new LunarCalendarWidget(frmLunarCalendarWidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);


        retranslateUi(frmLunarCalendarWidget);

        QMetaObject::connectSlotsByName(frmLunarCalendarWidget);
    } // setupUi

    void retranslateUi(QWidget *frmLunarCalendarWidget)
    {
        frmLunarCalendarWidget->setWindowTitle(QApplication::translate("frmLunarCalendarWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmLunarCalendarWidget: public Ui_frmLunarCalendarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMLUNARCALENDARWIDGET_H
