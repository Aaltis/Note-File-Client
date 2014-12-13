#ifndef NEWNOTEDIALOG_H
#define NEWNOTEDIALOG_H

#include <QDialog>
#include <qmessagebox.h>
namespace Ui {
class NewNoteDialog;
}

class NewNoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewNoteDialog(QWidget *parent = 0);
    ~NewNoteDialog();

private slots:
    void on_btnSave_clicked();

private:
    Ui::NewNoteDialog *ui;
signals:
    void noteCreated();
public slots:
    void querySuccess(QString result);
    void queryFailure(QString result);
};

#endif // NEWNOTEDIALOG_H
