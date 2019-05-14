QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=console c++14

INCLUDEPATH+="../../"
INCLUDEPATH+="googletest"
INCLUDEPATH+="googletest/include"
INCLUDEPATH+="googlemock"
INCLUDEPATH+="googlemock/include"

SOURCES += \
        ../../game.cpp \
        ../../gamewidget.cpp \
        googlemock/src/gmock-all.cc \
        googletest/src/gtest-all.cc \
        main.cpp

HEADERS += \
    ../../game.h \
    ../../gamewidget.h
