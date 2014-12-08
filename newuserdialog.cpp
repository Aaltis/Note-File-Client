#include "newuserdialog.h"
#include "ui_newuserdialog.h"
#include <newuserrequest.h>
#include <loginrequest.h>

NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}



void NewUserDialog::on_pushButtonCreateUser_clicked()
{
    NewUserRequest nUser(ui->lineEditUsername->text(),ui->lineEditPassword1->text(),ui->lineEditPassword2->text());
    nUser.sendRequest();
}
