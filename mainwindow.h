#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "note.h"
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

private slots:
    void on_btnResreshList_clicked();

    void on_listWidgetNotes_activated(const QModelIndex &index);

    void on_btnSaveChanges_clicked();

    void on_btnNewNote_clicked();

    void on_btnSendFile_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
