#-------------------------------------------------
#
# Project created by QtCreator 2021-09-10T15:14:36
#
#-------------------------------------------------

QT       += core gui
QT+=sql
QT       += webenginewidgets
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    dialog.cpp \
    mysql.cpp \
    icon_help.cpp \
    new_button.cpp \
    serial_process.cpp \
    mythread.cpp \
    globalvar.cpp \
    lunarcalendarinfo.cpp \
    lunarcalendaritem.cpp \
    lunarcalendarwidget.cpp

HEADERS += \
        widget.h \
    dialog.h \
    mysql.h \
    icon_help.h \
    new_button.h \
    serial_process.h \
    mythread.h \
    globalvar.h \
    lunarcalendarinfo.h \
    lunarcalendaritem.h \
    lunarcalendarwidget.h

FORMS += \
        widget.ui \
    dialog.ui

RESOURCES += \
    background.qrc \
    QWidgetDemo-master/QWidgetDemo-master/lunarcalendarwidget/main.qrc

DISTFILES +=

SUBDIRS += \
    ../../QWidgetDemo-master/QWidgetDemo-master/lunarcalendarwidget/lunarcalendarwidget.pro
