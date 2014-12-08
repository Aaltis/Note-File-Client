#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
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

private:
    Ui::MainWindow *ui;
    LoginDialog *loginDialog;
    QList<Note> notes;
public slots:
    void showFirstTimeSettings();
private slots:
    void on_actionFirst_Time_Settings_triggered();
    void on_actionChange_Settings_triggered();
    void on_btnSendFile_clicked();
    void on_pushButton_2_clicked();
    void on_btnNewNote_clicked();
    void on_btnResreshList_clicked();
};

#endif // MAINWINDOW_H
