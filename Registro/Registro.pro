QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agregar.cpp \
    buscar.cpp \
    eliminar.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    query.cpp

HEADERS += \
    agregar.h \
    buscar.h \
    eliminar.h \
    login.h \
    mainwindow.h \
    query.h

FORMS += \
    agregar.ui \
    buscar.ui \
    eliminar.ui \
    login.ui \
    mainwindow.ui \
    query.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iconos.qrc
