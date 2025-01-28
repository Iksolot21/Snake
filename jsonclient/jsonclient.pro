QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += wigets
CONFIG += c++17
QT += core network
QT += sql
QT += multimedia
QT += multimediawidgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    application.cpp \
    authorization2.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    playerinfo.cpp \
    splashscreen.cpp \
    titre.cpp

HEADERS += \
    admin.h \
    application.h \
    authorization2.h \
    crypter.h \
    crypter.h \
    mainwindow.h \
    menu.h \
    playerinfo.h \
    splashscreen.h \
    titre.h


FORMS += \
    admin.ui \
    authorization2.ui \
    mainwindow.ui \
    menu.ui \
    playerinfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

SUBDIRS += \

DISTFILES += \

