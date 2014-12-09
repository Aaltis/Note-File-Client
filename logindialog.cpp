#include "logindialog.h"
#include "ui_logindialog.h"
#include "newuserdialog.h"
#include "userrequests.h"
#include "settingshandler.h"
#include "firstsettingdialog.h"
#include "newuserdialog.h"
//#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    SettingsHandler settingsHandler;
    settingsHandler.loadLoginData();
    ui->lineEditUsername->setText(settingsHandler.getLoginName());
    ui->lineEditPassword->setText(settingsHandler.getPassword());

}

LoginDialog::~LoginDialog()
{
    delete ui;
}
bool LoginDialog::checkIfLoginData(QString data[] ){

    if(data[0].length()>0)
    {
        return true;
    }
    else
        false;
}

void LoginDialog::on_btnUser_clicked()
{
    NewUserDialog newuser;
    newuser.setModal(true);
    newuser.exec();
}

void LoginDialog::on_btnLogin_clicked()
{
    UserRequests userRequest;
    int result=userRequest.login(ui->lineEditUsername->text(),ui->lineEditPassword->text());
    if(result!=0)
    {
        SettingsHandler settingHandler;
        settingHandler.saveLoginData(ui->lineEditUsername->text(),ui->lineEditPassword->text(),QString::number(result));
        this->destroy();
    }

}


