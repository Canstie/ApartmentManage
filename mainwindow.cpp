#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apartment1.h"
#include "information.h"
#include "leasemanagement.h"


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


void MainWindow::on_pushButton_5_clicked()
{
    openInformation();
}

void MainWindow::openInformation() {
    information *info = new information("hostAccount.txt", this);
    info->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    LeaseManagement *a = new LeaseManagement;
    a->show();
}

