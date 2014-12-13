#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "newuserdialog.h"
#include "userrequests.h"
#include "settingshandler.h"
#include "firstsettingdialog.h"
#include "newuserdialog.h"

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
private slots:
    void userCreated();
};

#endif // LOGINDIALOG_H
