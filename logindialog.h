#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void getloginResult(QString data);
    bool checkIfLoginData(QString data[]);
private slots:
    void on_btnUser_clicked();

    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
