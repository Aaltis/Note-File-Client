#include "newuserdialog.h"
#include "ui_newuserdialog.h"
#include "userrequests.h"
NewUserDialog::NewUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUserDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonCreateUser, SIGNAL(clicked()), this, SLOT(on_btnCreateUser_clicked()));
}

NewUserDialog::~NewUserDialog()
{
    delete ui;
}

void NewUserDialog::on_btnCreateUser_clicked()
{
    UserRequests userRequest;
    userRequest.createUser(ui->lineEditUsername->text(),ui->lineEditPassword1->text(),ui->lineEditPassword2->text());
}


