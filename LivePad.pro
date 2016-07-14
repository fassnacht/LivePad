TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    meteradapter.cpp \
    udpreceiver.cpp \
    BaseItem.cpp \
    ListModelBase.cpp \
    channleitem.cpp \
    channleadapter.cpp \
    udpsender.cpp \
    ChannleFilter.cpp \
    ChannleFilterProxy.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    meteradapter.h \
    udpreceiver.h \
    BaseItem.h \
    ListModelBase.h \
    channleitem.h \
    channleadapter.h \
    udpsender.h \
    ChannleFilter.h \
    ChannleFilterProxy.h

DISTFILES += \
    Sends.qml

