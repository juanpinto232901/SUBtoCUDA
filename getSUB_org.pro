#-------------------------------------------------
#
# Project created by QtCreator 2019-05-15T11:13:05
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../w64/getSUB
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
LIBS += -lopengl32

#DEFINES *= USE_CUDA
DEFINES *= USE_CPU
# USE_CUDA_TREADS
# USE_CUDA_NOTH
# USE_CPU

INCLUDEPATH *= sdl/include \
                cwipc_util/include  \
                cwipc_codec

LIBS *= -Lsdl/lib/x64   \
        -lSDL \
        -Lcwipc_codec/lib/Debug  \
        -lcwipc_codec  \
        -lcloud_codec_v2 \
        -lpcl_jpeg_io

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    safeMain.cpp \
    TimerHQ.cpp \
    CapturSUBThread.cpp \
    GLVertexBuffers.cpp

HEADERS += \
        mainwindow.h \
    safeMain.h \
    signals_unity_bridge.h \
    TimerHQ.h \
    CapturSUBThread.h \
    qvector4duchar.h \
    GLVertexBuffers.h

FORMS += \
        mainwindow.ui
