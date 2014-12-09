#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>

namespace Ui {
class newuserdialog;
}

class newuserdialog : public QDialog
{
    Q_OBJECT

public:
    explicit newuserdialog(QWidget *parent = 0);
    ~newuserdialog();

private:
    Ui::newuserdialog *ui;
};

#endif // NEWUSERDIALOG_H
