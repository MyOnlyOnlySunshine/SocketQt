

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Socket-Tool
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS



SOURCES += main.cpp\
        mainwindow.cpp \
    myudp.cpp \
    mytcpserver.cpp \
    mytcpclient.cpp

HEADERS  += mainwindow.h \
    myudp.h \
    mytcpserver.h \
    mytcpclient.h

FORMS    += mainwindow.ui
