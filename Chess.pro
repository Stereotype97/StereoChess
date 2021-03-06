#-------------------------------------------------
#
# Project created by QtCreator 2018-05-03T23:45:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
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
    game.cpp \
    cell.cpp \
    udpclient.cpp \
    chessfigure.cpp \
    chessfigurepawn.cpp \
    chessfigureboat.cpp \
    chessfigureknight.cpp \
    chessfigureofficer.cpp \
    chessfigurequeen.cpp \
    chessfigureking.cpp \
    chesscontroller.cpp \
    view.cpp

HEADERS += \
    game.h \
    cell.h \
    udpclient.h \
    chessfigure.h \
    chessfigurepawn.h \
    chessfigureboat.h \
    chessfigureknight.h \
    chessfigureofficer.h \
    chessfigurequeen.h \
    chessfigureking.h \
    chesscontroller.h \
    view.h

FORMS += \
    view.ui
