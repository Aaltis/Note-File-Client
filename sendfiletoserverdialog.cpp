#include "sendfiletoserverdialog.h"
#include "ui_sendfiletoserverdialog.h"

SendFileToServerDialog::SendFileToServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendFileToServerDialog)
{
    ui->setupUi(this);
}

SendFileToServerDialog::~SendFileToServerDialog()
{
    delete ui;
}

void SendFileToServerDialog::on_btnChooseFile_clicked()
{
    QString sFilename=QFileDialog::getOpenFileName(this,tr("Open File"),"/home","All Files(*.*);;Text File (*.txt)");
    ui->labelFileName->setText(sFilename);
}

void SendFileToServerDialog::on_btnSendFile_clicked()
{
    SettingsHandler settingsHandler;
    FileRequests fileRequest(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    QObject::connect(&fileRequest, SIGNAL(fileSend(QString)), this, SLOT(fileSend(QString)));
    fileRequest.startSend(ui->labelFileName->text());

}
void SendFileToServerDialog::fileSend(QString message)
{
    QMessageBox messageBox;
    messageBox.information(0,"Success",message);
    messageBox.setFixedSize(500,200);
    this->destroy();
    emit fileSend();

}
