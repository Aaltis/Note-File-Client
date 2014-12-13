#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "note.h"
#include "logindialog.h"
#include "firstsettingdialog.h"
#include "settingsdialog.h"
#include "newnotedialog.h"
#include "sendfiletoserverdialog.h"
#include "noterequests.h"
#include "settingshandler.h"
#include "qstringlistmodel.h"
#include "filerequests.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showLoginDialog();
    QList<Note> notes;
    QList<File> files;
    void refreshNoteList(QList<Note>);
private:
    QString selected;
    QString selectedFile;
    NoteRequests* noteRequests;
    FileRequests* fileRequests;
public slots:
   void refreshLists();

private slots:
    void on_btnResreshList_clicked();
    void on_btnSaveChanges_clicked();
    void on_btnNewNote_clicked();
    void on_btnSendFile_clicked();
    void on_actionFirst_Time_Settings_triggered();
    void on_note_cell_clicked( int row, int column );
    void on_file_cell_clicked( int row, int column );
    void on_textEditNote_textChanged();
    void on_btnDeleteNote_clicked();
    void on_btnLoadFile_clicked();
    void on_actionChange_Settings_triggered();

    void on_btnDeleteDile_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
