#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settingshandler.h"
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    SettingsHandler settingsHandler;

    ui->lineEditLoginName->setText(settingsHandler.getLoginName());
    ui->lineEditPassword->setText(settingsHandler.getPassword());
    ui->lineEditServerUrl->setText(settingsHandler.getServerUrl());

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
