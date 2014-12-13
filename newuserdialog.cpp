#include "newuserdialog.h"
#include "ui_newuserdialog.h"
NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
    ui->lineEditPassword1->setEchoMode(QLineEdit::Password);
    ui->lineEditPassword2->setEchoMode(QLineEdit::Password);
    connect(ui->pushButtonCreateUser, SIGNAL(clicked()), this, SLOT(on_btnCreateUser_clicked()));
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}

void NewUserDialog::on_btnCreateUser_clicked()
{
    SettingsHandler settingsHandler;
    UserRequests userRequest(settingsHandler.getServerUrl());
    QObject::connect(&userRequest, SIGNAL(querySuccess(QString)), this, SLOT(querySuccess(QString)));
    QObject::connect(&userRequest, SIGNAL(queryFailure(QString)), this, SLOT(queryFailure(QString)));
    userRequest.createUser(ui->lineEditUsername->text(),ui->lineEditPassword1->text(),ui->lineEditPassword2->text());
}
void NewUserDialog::querySuccess(QString result){
    qDebug() << result;
    QMessageBox messageBox;
    messageBox.information(0,"Success","User Created Succesfully");
    messageBox.setFixedSize(500,200);
    SettingsHandler settingsHandler;

    settingsHandler.saveLoginData(ui->lineEditUsername->text(),ui->lineEditPassword1->text(),result);
    emit userCreated();
    this->destroy();
}

void NewUserDialog::queryFailure(QString result){
    qDebug() << result;
    QMessageBox messageBox;
    messageBox.critical(0,"Error",result);
    messageBox.setFixedSize(500,200);
}



