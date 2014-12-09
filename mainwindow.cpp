#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->btnSaveChanges->setDisabled(true);
    SettingsHandler settingsHandler;
    noteRequests=new NoteRequests(settingsHandler.getServerUrl());
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

    notes= noteRequests->getNotes(settingsHandler.getUserID());

    ui->tableWidgetNotes->clear();
    ui->tableWidgetNotes->setRowCount(notes.size());
    ui->tableWidgetNotes->setColumnCount(2);
    ui->tableWidgetNotes->hideColumn( 1 );
    ui->tableWidgetNotes->setShowGrid( false );
    QStringList list;
    list<<"Title";
    ui->tableWidgetNotes->setHorizontalHeaderLabels(list);
    ui->tableWidgetNotes->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidgetNotes->verticalHeader()->hide();
    for(int i=0;i<notes.size();i++)
    {
        QString stitle=notes[i].getTitle();
        QString sid=QString::number(notes[i].getId());
        QTableWidgetItem* title = new QTableWidgetItem( stitle);
        QTableWidgetItem* id = new QTableWidgetItem( sid);
        ui->tableWidgetNotes->setItem(i,0,title);
        ui->tableWidgetNotes->setItem(i,1,id);
    }
    connect(ui->tableWidgetNotes, SIGNAL(cellClicked(int,int)), this, SLOT(on_cell_clicked(int,int)) );
}

void MainWindow::on_cell_clicked( int row, int column )
{
    QString id = ui->tableWidgetNotes->item( row, 1 )->text();
    qDebug() << "id" <<id;
    ui->textEditNote->setPlainText(noteRequests->getNote(id));

}



void MainWindow::on_btnSaveChanges_clicked()
{
    SettingsHandler settingsHandler;
    ui->listWidgetNotes->clear();


    noteRequests->updateNote(selectedNote);
    notes.clear();
    notes= noteRequests->getNotes(settingsHandler.getUserID());
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

void MainWindow::on_actionFirst_Time_Settings_triggered()
{
    firstsettingdialog fsettingdialog;
    fsettingdialog.setModal(true);
    fsettingdialog.exec();
}

void MainWindow::on_tableWidgetNotes_cellClicked(int row, int column)
{
    //QString id = ui->listWidgetNotes->item(row,1)->text();
    //QString text=noteRequests->getNote(id);
    //ui->textEditNote->setPlainText(text);
}

void MainWindow::on_textEditNote_textChanged()
{
    ui->btnSaveChanges->setDisabled(false);
}
