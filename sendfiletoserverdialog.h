#ifndef SENDFILETOSERVERDIALOG_H
#define SENDFILETOSERVERDIALOG_H

#include <QDialog>

namespace Ui {
class SendFileToServerDialog;
}

class SendFileToServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendFileToServerDialog(QWidget *parent = 0);
    ~SendFileToServerDialog();

private slots:
    void on_btnChooseFile_clicked();

    void on_btnSendFile_clicked();

private:
    Ui::SendFileToServerDialog *ui;
};

#endif // SENDFILETOSERVERDIALOG_H
