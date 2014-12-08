#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firstsettingdialog.h"
#include "settingsdialog.h"
#include "newnotedialog.h"
#include "sendfiletoserverdialog.h"
#include "getnotesrequest.h"
#include "settingshandler.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionFirst_Time_Settings_triggered()
{
    firstsettingdialog fdialog;
    fdialog.setModal(true);
    fdialog.exec();
}

void MainWindow::on_actionChange_Settings_triggered()
{
    SettingsDialog settingDialog;
    settingDialog.setModal(true);
    settingDialog.exec();
}

void MainWindow::on_btnSendFile_clicked()
{
    SendFileToServerDialog sendFileDialog;
    sendFileDialog.setModal(true);
    sendFileDialog.exec();

}

void MainWindow::on_btnNewNote_clicked()
{
    NewNoteDialog newNoteDialog;
    newNoteDialog.setModal(true);
    newNoteDialog.exec();
}

void MainWindow::on_btnResreshList_clicked()
{
    SettingsHandler settingsHandler;
    GetnotesRequest getNotesRequest(settingsHandler.getUserID());
    QList<Note> notes= getNotesRequest.sendRequest();
}
