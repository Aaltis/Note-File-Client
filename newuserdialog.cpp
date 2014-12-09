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
