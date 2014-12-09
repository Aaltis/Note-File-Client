#include "sdfg.h"
#include "ui_sdfg.h"

sdfg::sdfg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sdfg)
{
    ui->setupUi(this);
}

sdfg::~sdfg()
{
    delete ui;
}
