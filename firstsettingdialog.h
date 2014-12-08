#ifndef FIRSTSETTINGDIALOG_H
#define FIRSTSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class firstsettingdialog;
}

class firstsettingdialog : public QDialog
{
    Q_OBJECT

public:
    explicit firstsettingdialog(QWidget *parent = 0);
    ~firstsettingdialog();

private slots:
    void on_btnLocal_clicked();

private:
    Ui::firstsettingdialog *ui;
};

#endif // FIRSTSETTINGDIALOG_H
