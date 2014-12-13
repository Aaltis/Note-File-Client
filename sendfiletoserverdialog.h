#ifndef SENDFILETOSERVERDIALOG_H
#define SENDFILETOSERVERDIALOG_H

#include <QDialog>
#include "filerequests.h"
#include <QString>
#include <QFileDialog>
#include "settingshandler.h"
#include "qnetworkreply.h"
#include "qmessagebox.h"
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
public slots:
    void fileSend(QString message);
signals:
    void fileSend();
private:
    Ui::SendFileToServerDialog *ui;
};

#endif // SENDFILETOSERVERDIALOG_H
