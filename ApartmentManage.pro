QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apartment.cpp \
    apartment1.cpp \
    codeconvert.cpp \
    information.cpp \
    leasemanagement.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    userui.cpp

HEADERS += \
    apartment.h \
    apartment1.h \
    information.h \
    leasemanagement.h \
    login.h \
    mainwindow.h \
    userui.h

FORMS += \
    apartment1.ui \
    information.ui \
    leasemanagement.ui \
    login.ui \
    mainwindow.ui \
    userui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
