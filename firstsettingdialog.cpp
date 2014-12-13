#include "firstsettingdialog.h"
#include "ui_firstsettingdialog.h"
#include "settingshandler.h"
#include "logindialog.h"
#include <QDebug>
/*
 * Initialdialog for first time user.
 */
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

/*
 *save server url to setting and open logindialog.
 */
void firstsettingdialog::on_btnLocal_clicked()
{
    SettingsHandler settingsHandler;
    settingsHandler.saveServerUrlLocal();
    this->destroy();
    LoginDialog loginDialog;
    loginDialog.exec();
}
