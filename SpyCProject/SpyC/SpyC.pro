#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T09:04:28
# Project created by QtCreator 2017-04-10T21:51:24
#
#-------------------------------------------------

QT += core gui qml quick quickwidgets positioning texttospeech xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += $$PWD/../DroneManager
INCLUDEPATH += $$PWD/../SpyCLib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpyC
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../bin/ -lspyclibd
    TARGET = SpyCd
} else {
    LIBS += -L$$PWD/../bin/ -lspyclib
    TARGET = SpyC
}

unix {
    DESTDIR = ../bin
    MOC_DIR = ../moc
    OBJECTS_DIR = ../obj
}

win32 {
    DESTDIR = ..\\bin
    MOC_DIR = ..\\moc
    OBJECTS_DIR = ..\\obj
}

unix {
    QMAKE_CLEAN *= $$DESTDIR/*$$TARGET*
    QMAKE_CLEAN *= $$MOC_DIR/*moc_*
    QMAKE_CLEAN *= $$OBJECTS_DIR/*.o*
}

win32 {
    QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
    QMAKE_CLEAN *= $$MOC_DIR\\*moc_*
    QMAKE_CLEAN *= $$OBJECTS_DIR\\*.o*
}

RESOURCES += \
    resources.qrc

#lupdate_only {
#    SOURCES = *.qml *.cpp *.h
#}

TRANSLATIONS = i18n/french.ts \
               i18n/english.ts \
               i18n/arabic.ts

DISTFILES +=

HEADERS += \
    alert.h \
    alertmodel.h \
    comstation.h \
    dronemodel.h \
    exclusionareamodel.h \
    gallerymodel.h \
    iservice.h \
    mastercontroller.h \
    pluginloader.h \
    settingcontroller.h \
    spyc.h \
    translator.h \
    waypointmodel.h \
    drone.h

SOURCES += \
    alert.cpp \
    alertmodel.cpp \
    comstation.cpp \
    dronemodel.cpp \
    exclusionareamodel.cpp \
    gallerymodel.cpp \
    main.cpp \
    mastercontroller.cpp \
    pluginloader.cpp \
    settingcontroller.cpp \
    spyc.cpp \
    translator.cpp \
    waypointmodel.cpp \
    drone.cpp




