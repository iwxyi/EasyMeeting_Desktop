#-------------------------------------------------
#
# Project created by QtCreator 2019-03-03T21:09:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyMeeting_Desktop
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
    include/amcomdef.h \
    include/arcsoft_idcardveri.h \
    include/asvloffscreen.h \
    include/merror.h

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
INCLUDEPATH += D:\OpenCV\include\
INCLUDEPATH += D:\OpenCV\include\opencv
INCLUDEPATH += D:\OpenCV\include\opencv2
LIBS += D:\OpenCV\bin\libopencv_*.dll
}
