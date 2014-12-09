#include "newnotedialog.h"
#include "ui_newnotedialog.h"
#include "settingshandler.h"
#include "noterequests.h"
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


    NoteRequests noteRequest(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    QString response=noteRequest.createNote(ui->lineEditTitle->text(),ui->textEditTextBody->toPlainText());
    if(response=="success")
    {
      this->destroy();
    }
}
