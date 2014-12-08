#include "newnotedialog.h"
#include "ui_newnotedialog.h"
#include "newnoterequest.h"
#include "settingshandler.h"
NewNoteDialog::NewNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewNoteDialog)
{
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog()
{
    delete ui;
}

void NewNoteDialog::on_btnSave_clicked()
{
    SettingsHandler settingsHandler;


    NewNoteRequest newNoteRequest(settingsHandler.getUserID(),ui->lineEditTitle->text(),ui->textEditTextBody->toPlainText());
    QString response=newNoteRequest.SendRequest();
    if(response=="success")
    {
      this->destroy();
    }
}
