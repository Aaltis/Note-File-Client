#ifndef SDFG_H
#define SDFG_H

#include <QMainWindow>

namespace Ui {
class sdfg;
}

class sdfg : public QMainWindow
{
    Q_OBJECT

public:
    explicit sdfg(QWidget *parent = 0);
    ~sdfg();

private:
    Ui::sdfg *ui;
};

#endif // SDFG_H
