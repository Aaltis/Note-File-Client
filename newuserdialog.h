#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>

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
    void on_pushButton_clicked();

    void on_pushButtonCreateUser_clicked();

private:
    Ui::NewUserDialog *ui;
};

#endif // NEWUSERDIALOG_H
