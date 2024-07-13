#include "myinfor.h"
#include "ui_myinfor.h"
#include <QFile>

myinfor::myinfor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myinfor)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFile file("2.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() == 4) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fields[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(fields[1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(fields[2]));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(fields[3]));
            row++;
        }
    }
}

myinfor::~myinfor()
{
    delete ui;
}
