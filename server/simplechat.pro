QT       += core websockets
QT       -= gui

TARGET = chatserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    atmserver.cpp \
    myparser.cpp \
    dbaccessor.cpp \
    integer.cpp

HEADERS += \
    atmserver.h \
    myparser.h \
    userdata.h \
    dbaccessor.h \
    integer.h

EXAMPLE_FILES += chatclient.html

target.path = $$[QT_INSTALL_EXAMPLES]/websockets/simplechat
INSTALLS += target
