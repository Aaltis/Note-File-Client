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
    Note selectedNote;
    void refreshNoteList(QList<Note>);
    NoteRequests* noteRequests;
private slots:
    void on_btnResreshList_clicked();

    void on_listWidgetNotes_activated(const QModelIndex &index);

    void on_btnSaveChanges_clicked();

    void on_btnNewNote_clicked();

    void on_btnSendFile_clicked();

    void on_actionFirst_Time_Settings_triggered();

    void on_tableWidgetNotes_cellClicked(int row, int column);
void on_cell_clicked( int row, int column );
private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
