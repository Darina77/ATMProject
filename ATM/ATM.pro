#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T13:58:40
#
#-------------------------------------------------

QT       += core gui
QT       += core websockets

QT   += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ATM
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    AtmInput.cpp \
    login.cpp \
    pin.cpp \
    menu.cpp \
    getmoney.cpp \
    balance.cpp \
    putmoney.cpp \
    other.cpp \
    sendmoneyaccount.cpp \
    sendmoneyamount.cpp \
    fromjson.cpp


HEADERS += \
    AtmInput.h \
    login.h \
    login.h \
    pin.h \
    menu.h\
    shotuserinfo.h \
    getmoney.h \
    balance.h \
    putmoney.h \
    other.h \
    sendmoneyaccount.h \
    sendmoneyamount.h \
    fromjson.h


FORMS += \
    balance.ui \
    getmoney.ui \
    login.ui \
    menu.ui \
    other.ui \
    pin.ui \
    putmoney.ui \
    sendmoneyAccount.ui \
    sendmoneyAmount.ui

SUBDIRS += \
    ATM.pro

RESOURCES += \
    images.qrc
