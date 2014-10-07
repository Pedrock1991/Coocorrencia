#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T13:21:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Coocorrencia
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    vetor.cpp \
    coocorrencia.cpp \
    operacoes.cpp

unix:!macx: LIBS += -L$$PWD/../../../../../usr/local/cuda/lib64/ -lOpenCL

INCLUDEPATH += $$PWD/../../../../../usr/local/cuda/include
DEPENDPATH += $$PWD/../../../../../usr/local/cuda/include

unix:!macx: LIBS += -lOpenCL

unix:!macx: LIBS += -L$$PWD/../Nvidia/OpenCL/common/lib/ -loclUtil_x86_64

INCLUDEPATH += $$PWD/../Nvidia/OpenCL/common/inc
DEPENDPATH += $$PWD/../Nvidia/OpenCL/common/inc

unix:!macx: PRE_TARGETDEPS += $$PWD/../Nvidia/OpenCL/common/lib/liboclUtil_x86_64.a

unix:!macx: LIBS += -L$$PWD/../Nvidia/shared/lib/ -lshrutil_x86_64

INCLUDEPATH += $$PWD/../Nvidia/shared/inc
DEPENDPATH += $$PWD/../Nvidia/shared/inc

unix:!macx: PRE_TARGETDEPS += $$PWD/../Nvidia/shared/lib/libshrutil_x86_64.a

HEADERS += \
    vetor.h \
    coocorrencia.h \
    operacoes.h

RESOURCES += \
    ocorrencia.qrc
