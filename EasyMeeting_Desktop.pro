#-------------------------------------------------
#
# Project created by QtCreator 2019-03-03T21:09:24
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyMeeting_Desktop
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    arcfaceidutil.cpp \
    globals.cpp \
    loginwindow.cpp \
    networkutil.cpp \
    stringutil.cpp \
    fileutil.cpp \
    leasewindow.cpp

HEADERS += \
        mainwindow.h \
    include/amcomdef.h \
    include/arcsoft_idcardveri.h \
    include/asvloffscreen.h \
    include/merror.h \
    arcfaceidutil.h \
    globals.h \
    loginwindow.h \
    networkutil.h \
    stringutil.h \
    fileutil.h \
    settings.h \
    connectutil.h \
    user.h \
    leasewindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

# 虹软人脸识别
#INCLUDEPATH += include \
unix|win32: LIBS += -L$$PWD/lib/ -llibarcsoft_idcardveri

# OpenCV
win32 {
INCLUDEPATH += D:\Libraries\OpenCV\include\
INCLUDEPATH += D:\Libraries\OpenCV\include\opencv
INCLUDEPATH += D:\Libraries\OpenCV\include\opencv2
LIBS += D:\Libraries\OpenCV\bin\libopencv_*.dll
}
