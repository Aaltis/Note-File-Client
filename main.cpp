#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
#include "settingshandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*w.showLoginDialog();
    LoginDialog ldialog;
    ldialog.exec();*/
    return a.exec();
}
