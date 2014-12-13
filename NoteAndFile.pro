#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T18:40:48
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets


TARGET = NoteAndFile
TEMPLATE = app


QT += network

SOURCES += main.cpp\
    firstsettingdialog.cpp \
    logindialog.cpp \
    settingshandler.cpp \
    settingsdialog.cpp \
    sendfiletoserverdialog.cpp \
    newnotedialog.cpp \
    note.cpp \
    filerequests.cpp \
    noterequests.cpp \
    mainwindow.cpp \
    newuserdialog.cpp \
    userrequests.cpp \
    file.cpp

HEADERS  += \
    firstsettingdialog.h \
    logindialog.h \
    settingshandler.h \
    settingsdialog.h \
    sendfiletoserverdialog.h \
    newnotedialog.h \
    note.h \
    filerequests.h \
    noterequests.h \
    mainwindow.h \
    newuserdialog.h \
    userrequests.h \
    file.h

FORMS    += mainwindow.ui \
    firstsettingdialog.ui \
    logindialog.ui \
    settingsdialog.ui \
    sendfiletoserverdialog.ui \
    newnotedialog.ui \
    newuserdialog.ui

OTHER_FILES +=
