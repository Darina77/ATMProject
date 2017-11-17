 QT       += core gui
 greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
 TARGET = PushButtonExample TEMPLATE = app
 SOURCES += main.cpp \ mainwindow.cpp
 HEADERS += mainwindow.h
DISTFILES +=

FORMS += \
    mainwindow.ui \
    getmoney.ui \
    login.ui \
    pin.ui \
    menu.ui \
    choose.ui \
    sendmoneyAmount.ui \
    sendmoneyAccount.ui \
    other.ui \
    paymentAmount.ui \
    paymentAccount.ui \
    balance.ui \
    putmoney.ui

SUBDIRS += \
    ATM.pro

RESOURCES += \
    images.qrc
