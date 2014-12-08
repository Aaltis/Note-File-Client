#include "firstsettingdialog.h"
#include "ui_firstsettingdialog.h"
#include "settingshandler.h"
#include "logindialog.h"
#include <QDebug>
firstsettingdialog::firstsettingdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstsettingdialog)
{

    ui->setupUi(this);
}

firstsettingdialog::~firstsettingdialog()
{
    delete ui;
}

void firstsettingdialog::on_btnLocal_clicked()
{
    SettingsHandler settingsHandler;
    settingsHandler.saveServerUrlLocal();
    this->destroy();
    LoginDialog loginDialog;
    loginDialog.exec();

}
