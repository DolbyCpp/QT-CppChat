#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T17:16:21
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    registro.cpp

HEADERS  += mainwindow.h \
    form.h \
    registro.h


FORMS    += mainwindow.ui \
    form.ui \
    registro.ui

OTHER_FILES += \
    imagens/Contatos.png

RESOURCES += \
    Resource.qrc
