#-------------------------------------------------
#
# Project created by QtCreator 2014-05-13T00:57:10
#
#-------------------------------------------------

CONFIG += qt debug 
CONFIG += touch 

QT       += core gui \
	network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = usbwidget
TEMPLATE = app


SOURCES += main.cpp\
    gengxin.cpp \
    wenjian.cpp \
    baobiao.cpp \
    mainwindow.cpp \
    shangchuan.cpp \
    global.cpp \
    devwdg.cpp \
    devprocess.cpp \
    help.cpp \
    dataupdate.cpp \
    fileupload.cpp \
    usb_state.cpp \
    upstate.cpp 

SOURCES += db/sqlDB.cpp\
            db/devDB.cpp\
            db/pkgDB.cpp\
            db/apkDB.cpp\
            db/mblDB.cpp\
            db/usbStatDB.cpp\
            db/mblStatDB.cpp\
            db/logDB.cpp

SOURCES += json/json.cpp


HEADERS  += gengxin.h \
    ClickedLabel.h \
    wenjian.h \
    baobiao.h \
    mainwindow.h \
    shangchuan.h \
    global.h \
    devwdg.h \
    devprocess.h \
    help.h \
    dataupdate.h \
    fileupload.h \
    usb_enum.h \
    tongxin.h \
    upstate.h 

HEADERS  += db/sqlDB.h\
            db/pkgDB.h\
            db/apkDB.h\
            db/mblDB.h\
            db/usbStatDB.h\
            db/mblStatDB.h\
            db/logDB.h\
            db/devDB.h

HEADERS  += json/json.h

touch {
    SOURCES += touch/calibration.cpp
    HEADERS  += touch/calibration.h
}

FORMS    += widget.ui \
    gengxin.ui \
    wenjian.ui \
    baobiao.ui \
    fuwuqi.ui \
    shangchuan.ui \
    devwdg.ui \
    help.ui \
    upstate.ui 

RESOURCES += \
    usbwidget.qrc

LIBS += -lsqlite3 \
#            ./usb/pc/libusb_enum.a
            ./usb/arm/libusb_enum.a

#LIBS += -lqjson


