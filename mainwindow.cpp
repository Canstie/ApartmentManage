#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apartment1.h"
#include "information.h"
#include "leasemanagement.h"
#include "visit.h"



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

void MainWindow::recievedata1(const QString &data){
    adad = data;
}


void MainWindow::on_pushButton_5_clicked()
{
    openInformation();
}


void MainWindow::openInformation() {
    information *info = new information(adad, true);
    info->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    LeaseManagement *a = new LeaseManagement;
    a->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    visit *a =new visit;
    a->show();
}


