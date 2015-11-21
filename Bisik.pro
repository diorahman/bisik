TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    account.cpp \
    call.cpp \
    app.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

CONFIG += link_pkgconfig
PKGCONFIG += libpjproject

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    account.h \
    call.h \
    app.h

