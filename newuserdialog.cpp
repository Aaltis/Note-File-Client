#include "newuserdialog.h"
#include "ui_newuserdialog.h"

newuserdialog::newuserdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newuserdialog)
{
    ui->setupUi(this);
}

newuserdialog::~newuserdialog()
{
    delete ui;
}

void newuserdialog::on_btnCreateUser_clicked()
{
    NewUserRequest nUser(ui->lineEditUsername->text(),ui->lineEditPassword1->text(),ui->lineEditPassword2->text());
    nUser.sendRequest();
}
