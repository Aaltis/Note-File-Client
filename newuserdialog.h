#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>
#include "userrequests.h"
#include <qmessagebox.h>
#include "settingshandler.h"
namespace Ui {
class NewUserDialog;
}

class NewUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewUserDialog(QWidget *parent = 0);
    ~NewUserDialog();

private slots:
    void on_btnCreateUser_clicked();
public slots:
    void querySuccess(QString result);
    void queryFailure(QString result);
signals:
    void userCreated();
private:
    Ui::NewUserDialog *ui;
};

#endif // NEWUSERDIALOG_H
