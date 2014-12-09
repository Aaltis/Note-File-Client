#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "firstsettingdialog.h"
#include "settingsdialog.h"
#include "newnotedialog.h"
#include "sendfiletoserverdialog.h"
#include "noterequests.h"
#include "settingshandler.h"
#include "qstringlistmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->btnSaveChanges->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnResreshList_clicked()
{
    notes.clear();
    ui->listWidgetNotes->clear();
       SettingsHandler settingsHandler;
       NoteRequests NotesRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
       notes= NotesRequests.getNotes();
       foreach(Note note,notes)
       {
          ui->listWidgetNotes->addItem(note.getTitle());
       }
}

void MainWindow::on_listWidgetNotes_activated(const QModelIndex &index)
{
    ui->btnSaveChanges->setDisabled(false);
    int i=index.row();
    selectedNote=notes[i];
    ui->textEditNote->setText(selectedNote.getBody());
}

void MainWindow::on_btnSaveChanges_clicked()
{
    SettingsHandler settingsHandler;
    ui->listWidgetNotes->clear();

       NoteRequests noteRequest(settingsHandler.getServerUrl());
       noteRequest.updateNote(selectedNote);
       notes.clear();
       NoteRequests NotesRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
       notes= NotesRequests.getNotes();
       foreach(Note note,notes)
       {

           ui->listWidgetNotes->addItem(note.getTitle());
       }
}

void MainWindow::on_btnNewNote_clicked()
{
    NewNoteDialog newNoteDialog;
    newNoteDialog.setModal(true);
    newNoteDialog.exec();
}

void MainWindow::on_btnSendFile_clicked()
{
    SendFileToServerDialog sendFileDialog;
        sendFileDialog.setModal(true);
        sendFileDialog.exec();
}
