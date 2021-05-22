#-------------------------------------------------
#
# Project created by QtCreator 2018-01-05T09:18:55
#
#-------------------------------------------------

QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtQGLWidget
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
        mainwindow.cpp \
    glview.cpp \
    material.cpp \
    triangle.cpp \
    vertex.cpp

HEADERS += \
    glview.h \
        mainwindow.h \
    material.h \
    triangle.h \
    vertex.h

FORMS += \
        mainwindow.ui

win32: LIBS += -L$$PWD/../../../../Qt/Tools/mingw730_64/x86_64-w64-mingw32/lib/ -lopengl32

INCLUDEPATH += $$PWD/../../../../Qt/Tools/mingw730_64/x86_64-w64-mingw32/include
DEPENDPATH += $$PWD/../../../../Qt/Tools/mingw730_64/x86_64-w64-mingw32/include

DISTFILES += \
    fshader.fsh \
    vshader.vsh
