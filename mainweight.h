#ifndef MAINWEIGHT_H
#define MAINWEIGHT_H

#include <QWidget>
#include "plcconnect.h"
namespace Ui {
class MainWeight;
}

class MainWeight : public QWidget
{
    Q_OBJECT

public:
    explicit MainWeight(QWidget *parent = 0);
    ~MainWeight();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWeight *ui;
    PLCConnect *plcConnect;
};

#endif // MAINWEIGHT_H
