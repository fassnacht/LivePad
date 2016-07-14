TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    models/meteradapter.cpp \
    services/udpreceiver.cpp \
    bases/BaseItem.cpp \
    bases/ListModelBase.cpp \
    models/channleitem.cpp \
    models/channleadapter.cpp \
    services/udpsender.cpp \
    models/ChannleFilter.cpp \
    models/ChannleFilterProxy.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    models/meteradapter.h \
    services/udpreceiver.h \
    bases/BaseItem.h \
    bases/ListModelBase.h \
    models/channleitem.h \
    models/channleadapter.h \
    services/udpsender.h \
    models/ChannleFilter.h \
    models/ChannleFilterProxy.h
