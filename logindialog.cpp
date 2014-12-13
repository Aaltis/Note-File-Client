#include "logindialog.h"
#include "ui_logindialog.h"
/*
 * Dialog for login
 */
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //initialize textfield to not show password.
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    //if user has logged in before we give him logindata ready.
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
    connect(&newuser, SIGNAL(userCreated()), this, SLOT(userCreated()));
    newuser.setModal(true);
    newuser.exec();
}

void LoginDialog::on_btnLogin_clicked()
{
    SettingsHandler settingsHandler;
    UserRequests userRequest(settingsHandler.getServerUrl());
    QString result=userRequest.login(ui->lineEditUsername->text(),ui->lineEditPassword->text());
    if(result!="")
    {
        SettingsHandler settingHandler;
        settingHandler.saveLoginData(ui->lineEditUsername->text(),ui->lineEditPassword->text(),result);
        this->destroy();
    }
    else{

    }

}
void LoginDialog::userCreated(){
    this->destroy();
}

