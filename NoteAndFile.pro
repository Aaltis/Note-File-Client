#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T18:40:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoteAndFile
TEMPLATE = app


QT += network

SOURCES += main.cpp\
        mainwindow.cpp \
    firstsettingdialog.cpp \
    logindialog.cpp \
    loginrequest.cpp \
    newuserrequest.cpp \
    settingshandler.cpp \
    settingsdialog.cpp \
    filesendrequest.cpp \
    sendfiletoserverdialog.cpp \
    newnotedialog.cpp \
    newnoterequest.cpp \
    note.cpp \
    getnotesrequest.cpp \
    newuserdialog.cpp \
    filerequests.cpp

HEADERS  += mainwindow.h \
    firstsettingdialog.h \
    logindialog.h \
    loginrequest.h \
    newuserrequest.h \
    settingshandler.h \
    settingsdialog.h \
    filesendrequest.h \
    sendfiletoserverdialog.h \
    newnotedialog.h \
    newnoterequest.h \
    note.h \
    getnotesrequest.h \
    newuserdialog.h \
    filerequests.h

FORMS    += mainwindow.ui \
    firstsettingdialog.ui \
    logindialog.ui \
    settingsdialog.ui \
    sendfiletoserverdialog.ui \
    newnotedialog.ui \
    newuserdialog.ui

OTHER_FILES +=
