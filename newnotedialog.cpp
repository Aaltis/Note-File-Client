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
    QObject::connect(&noteRequest, SIGNAL(querySuccess(QString)), this, SLOT(querySuccess(QString)));
    QObject::connect(&noteRequest, SIGNAL(queryFailure(QString)), this, SLOT(queryFailure(QString)));

    QString response=noteRequest.createNote(ui->lineEditTitle->text(),ui->textEditTextBody->toPlainText());

      this->destroy();

     //send signal for mainwindow to refresh lists
      emit noteCreated();
}

void NewNoteDialog::querySuccess(QString result){
    qDebug() << result;
    QMessageBox messageBox;
    messageBox.information(0,"Success",result);
    messageBox.setFixedSize(500,200);

    this->destroy();
    emit noteCreated();

}

void NewNoteDialog::queryFailure(QString result){
    qDebug() << result;
    QMessageBox messageBox;
    messageBox.critical(0,"Error",result);
    messageBox.setFixedSize(500,200);
}
