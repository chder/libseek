#-------------------------------------------------
#
# Project created by QtCreator 2015-04-11T01:50:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt
TEMPLATE = app

CONFIG   += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    seek.cpp

HEADERS  += mainwindow.h \
    seek_pimpl_h.hpp \
    seek_pimpl_impl.hpp \
    seek.hpp

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libusb-1.0
