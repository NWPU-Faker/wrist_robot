/********************************************************************************
** Form generated from reading UI file 'frmimageswitch.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMIMAGESWITCH_H
#define UI_FRMIMAGESWITCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "imageswitch.h"

QT_BEGIN_NAMESPACE

class Ui_frmImageSwitch
{
public:
    QGridLayout *gridLayout;
    ImageSwitch *imageSwitch3;
    ImageSwitch *imageSwitch1;
    ImageSwitch *imageSwitch2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *frmImageSwitch)
    {
        if (frmImageSwitch->objectName().isEmpty())
            frmImageSwitch->setObjectName(QStringLiteral("frmImageSwitch"));
        frmImageSwitch->resize(500, 300);
        gridLayout = new QGridLayout(frmImageSwitch);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        imageSwitch3 = new ImageSwitch(frmImageSwitch);
        imageSwitch3->setObjectName(QStringLiteral("imageSwitch3"));

        gridLayout->addWidget(imageSwitch3, 0, 2, 1, 1);

        imageSwitch1 = new ImageSwitch(frmImageSwitch);
        imageSwitch1->setObjectName(QStringLiteral("imageSwitch1"));

        gridLayout->addWidget(imageSwitch1, 0, 0, 1, 1);

        imageSwitch2 = new ImageSwitch(frmImageSwitch);
        imageSwitch2->setObjectName(QStringLiteral("imageSwitch2"));

        gridLayout->addWidget(imageSwitch2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);


        retranslateUi(frmImageSwitch);

        QMetaObject::connectSlotsByName(frmImageSwitch);
    } // setupUi

    void retranslateUi(QWidget *frmImageSwitch)
    {
        frmImageSwitch->setWindowTitle(QApplication::translate("frmImageSwitch", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmImageSwitch: public Ui_frmImageSwitch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMIMAGESWITCH_H
