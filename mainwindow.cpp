#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apartment1.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    apartment1 *a = new apartment1;
    a->show();
}

