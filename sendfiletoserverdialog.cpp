#include "sendfiletoserverdialog.h"
#include "ui_sendfiletoserverdialog.h"
#include "filesendrequest.h"
#include <QString>
#include <QFileDialog>
#include "settingshandler.h"
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

    FileSendRequest fileSendRequest(settingsHandler.getServerUrl(),ui->labelFileName->text(),settingsHandler.getUserID());
    fileSendRequest.startSend();

}
