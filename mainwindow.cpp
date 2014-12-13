#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //Model Tablets to look like list and hide column 2 which has id of objects.
    ui->tableWidgetNotes->setColumnCount(2);
    ui->tableWidgetNotes->hideColumn( 1 );
    ui->tableWidgetNotes->setShowGrid( false );
    ui->tableWidgetNotes->horizontalHeader()->setResizeContentsPrecision(true);

    //stretch header of list
    QHeaderView* header = ui->tableWidgetNotes->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    //add headertext
    QStringList list;
    list<<"Title";
    ui->tableWidgetNotes->setHorizontalHeaderLabels(list);
    //resize header to fit width
    ui->tableWidgetNotes->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidgetNotes->verticalHeader()->hide();

    //same as upperd
    QHeaderView* header2 = ui->tableWidgetFiles->horizontalHeader();
    header2->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetFiles->setColumnCount(2);
    ui->tableWidgetFiles->hideColumn( 1 );
    ui->tableWidgetFiles->setShowGrid( false );
    QStringList asdf;
    asdf<<"Name";
    ui->tableWidgetFiles->setHorizontalHeaderLabels(asdf);
    ui->tableWidgetFiles->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidgetFiles->verticalHeader()->hide();

    //both list have custom signals so we can get data of
    connect(ui->tableWidgetNotes, SIGNAL(cellClicked(int,int)), this, SLOT(on_note_cell_clicked(int,int)) );
    connect(ui->tableWidgetFiles, SIGNAL(cellClicked(int,int)), this, SLOT(on_file_cell_clicked(int,int)) );


    SettingsHandler settingsHandler;
    if(settingsHandler.getServerUrl()=="")
    {
        firstsettingdialog fsettingdialog;
        fsettingdialog.setModal(true);
        fsettingdialog.exec();
    }
    else{
        noteRequests=new NoteRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
        fileRequests=new FileRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnResreshList_clicked()
{
    ui->tableWidgetNotes->clear();

    notes.clear();
    SettingsHandler settingsHandler;
    notes= noteRequests->getNotes(settingsHandler.getUserID());
    files=fileRequests->getFilesList(settingsHandler.getUserID());

    ui->tableWidgetFiles->setRowCount(files.size());
    for(int i=0;i<files.size();i++)
    {
        QString sname=files[i].getName();
        QString sid=QString::number(files[i].getId());
        QTableWidgetItem* name = new QTableWidgetItem(sname);
        QTableWidgetItem* id = new QTableWidgetItem(sid);
        name->setFlags(name->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidgetFiles->setItem(i,0,name);
        ui->tableWidgetFiles->setItem(i,1,id);

    }

    ui->tableWidgetNotes->setRowCount(notes.size());
    for(int i=0;i<notes.size();i++)
    {
        QString stitle=notes[i].getTitle();
        QString sid=QString::number(notes[i].getId());
        QTableWidgetItem* title = new QTableWidgetItem( stitle);
        QTableWidgetItem* id = new QTableWidgetItem( sid);
        title->setFlags(title->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidgetNotes->setItem(i,0,title);
        ui->tableWidgetNotes->setItem(i,1,id);

    }

}

void MainWindow::on_note_cell_clicked( int row, int column )
{
    QString id = ui->tableWidgetNotes->item( row, 1 )->text();
    selected=id;
    qDebug() << "id" <<id;
    ui->textEditNote->setPlainText(noteRequests->getNote(id));

}
void MainWindow::on_file_cell_clicked( int row, int column )
{
    selectedFile = ui->tableWidgetFiles->item( row,0 )->text();
}




void MainWindow::on_btnSaveChanges_clicked()
{

    SettingsHandler settingsHandler;
    NoteRequests noter(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    QObject::connect(&noter, SIGNAL(querySuccess(QString message)), this, SLOT(refreshLists()));
    noteRequests->updateNote(selected,settingsHandler.getUserID(),ui->textEditNote->toPlainText());
    //refreshLists();

}

void MainWindow::on_btnNewNote_clicked()
{
    NewNoteDialog newNoteDialog;
    QObject::connect(&newNoteDialog, SIGNAL(noteCreated()), this, SLOT(refreshLists()));
    newNoteDialog.setModal(true);
    newNoteDialog.exec();
}

void MainWindow::on_btnSendFile_clicked()
{
    SendFileToServerDialog sendFileDialog;
    QObject::connect(&sendFileDialog, SIGNAL(fileSend()), this, SLOT(refreshLists()));
    sendFileDialog.setModal(true);
    sendFileDialog.exec();
}

void MainWindow::on_actionFirst_Time_Settings_triggered()
{
    firstsettingdialog fsettingdialog;
    fsettingdialog.setModal(true);
    fsettingdialog.exec();
}



void MainWindow::on_textEditNote_textChanged()
{
    ui->btnSaveChanges->setDisabled(false);
}
/*
 * Button gives NoteRequests call to delete selected note.
 */
void MainWindow::on_btnDeleteNote_clicked()
{
    SettingsHandler settingsHandler;
    QObject::connect(noteRequests, SIGNAL(noteDeleted()), this, SLOT(refreshLists()));
    noteRequests->deleteNote(selected,settingsHandler.getUserID());

}
/*
 * When note or file is created or deleted we need to refresh lists
 */
void MainWindow::refreshLists()
{
    ui->tableWidgetNotes->clear();
    notes.clear();
    SettingsHandler settingsHandler;
    notes= noteRequests->getNotes(settingsHandler.getUserID());
    files=fileRequests->getFilesList(settingsHandler.getUserID());

    ui->tableWidgetFiles->setRowCount(files.size());
    for(int i=0;i<files.size();i++)
    {
        QString sname=files[i].getName();
        QString sid=QString::number(files[i].getId());
        QTableWidgetItem* name = new QTableWidgetItem(sname);
        QTableWidgetItem* id = new QTableWidgetItem(sid);
        name->setFlags(name->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidgetFiles->setItem(i,0,name);
        ui->tableWidgetFiles->setItem(i,1,id);

    }

    ui->tableWidgetNotes->setRowCount(notes.size());
    for(int i=0;i<notes.size();i++)
    {
        QString stitle=notes[i].getTitle();
        QString sid=QString::number(notes[i].getId());
        QTableWidgetItem* title = new QTableWidgetItem( stitle);
        QTableWidgetItem* id = new QTableWidgetItem( sid);
        title->setFlags(title->flags() &= ~Qt::ItemIsEditable);
        ui->tableWidgetNotes->setItem(i,0,title);
        ui->tableWidgetNotes->setItem(i,1,id);

    }
}

void MainWindow::on_btnLoadFile_clicked()
{
    SettingsHandler settingsHandler;
    FileRequests fileRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    fileRequests.getFile(settingsHandler.getUserID(),selectedFile);
}

void MainWindow::on_actionChange_Settings_triggered()
{
    SettingsDialog settingsDialog;
    settingsDialog.setModal(true);
    settingsDialog.exec();
}

void MainWindow::on_btnDeleteDile_clicked()
{
    SettingsHandler settingsHandler;
    FileRequests fileRequests(settingsHandler.getServerUrl(),settingsHandler.getUserID());
    QObject::connect(&fileRequests, SIGNAL(fileDeleted(message)), this, SLOT(refreshLists()));
    fileRequests.deleteFile(selectedFile);
}
