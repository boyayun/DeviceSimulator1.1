#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T10:11:43
#
#-------------------------------------------------
QT       += core gui
QT += xml\
     serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = DeviceSimulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    define.cpp \
    functionitemwidget.cpp \
    controlItem/controlcmd.cpp \
    controlItem/controlnumber.cpp \
    controlItem/controlenumberate.cpp \
    controlItem/controlalarm.cpp \
    controlItem/controldate.cpp \
    controlItem/controltime.cpp \
    controlpanel.cpp \
    controlItem/controldatetime.cpp \
    detectxml.cpp \
    UserUartLink.cpp \
    about.cpp \
    controlItem/selectpanel.cpp \
    controlItem/form.cpp \
    customControl/switchbutton.cpp

HEADERS  += mainwindow.h \
    define.h \
    functionitemwidget.h \
    controlItem/controlcmd.h \
    controlItem/controlnumber.h \
    controlItem/controlenumberate.h \
    controlItem/controlalarm.h \
    controlItem/controldate.h \
    controlItem/controltime.h \
    controlpanel.h \
    controlItem/controldatetime.h \
    detectxml.h \
    UserUartLink.h \
    about.h \
    controlItem/selectpanel.h \
    controlItem/form.h \
    customControl/switchbutton.h

FORMS    += mainwindow.ui \
    controlItem/controlnumber.ui \
    controlItem/controlenumberate.ui \
    controlItem/controlalarm.ui \
    controlItem/controldate.ui \
    controlItem/controltime.ui \
    about.ui \
    controlItem/selectpanel.ui \
    controlItem/controlcmd.ui \
    controlItem/form.ui

RESOURCES += \
    resource.qrc

#qwt设置
include(D:\Qt2\qtCtrl\qwt-6.1.3\qwtfunctions.pri)
DEFINES *= QWT_DLL
CONFIG += qwt
LIBS += -LD:\Qt2\5.8\mingw53_32\lib-lqwt
INCLUDEPATH += D:\Qt2\qtCtrl\qwt-6.1.3\src
DEPENDPATH += D:\Qt2\qtCtrl\qwt-6.1.3\src
qwtAddLibrary(D:\Qt2\5.8\mingw53_32\lib, qwt)
#end qwt
