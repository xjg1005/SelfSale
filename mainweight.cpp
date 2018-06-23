#include "mainweight.h"
#include "ui_mainweight.h"

MainWeight::MainWeight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWeight),
    plcConnect(NULL)
{
    ui->setupUi(this);
    plcConnect = new PLCConnect(this);
}

MainWeight::~MainWeight()
{
    delete ui;
}

void MainWeight::on_pushButton_clicked()
{
    plcConnect->sendDataToPLC(0x18);
}
