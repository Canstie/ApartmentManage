#include "myinfor.h"
#include "ui_myinfor.h"
#include <QFile>

myinfor::myinfor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myinfor)
{
    ui->setupUi(this);
    this->setWindowTitle("我的租赁");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setColumnCount(6); // 设置列数
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "位置" << "价格" << "租赁状态" << "起始日期" << "租赁总时长" << "结束日期");
    QFile file("2.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList fields = line.split("\t");
            if (fields.size() == 6) {
                ui->tableWidget->insertRow(row);
                for (int col = 0; col < fields.size(); ++col) {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(fields.at(col)));
                }
                ++row;
            }
        }
        file.close();
    }
}

myinfor::~myinfor()
{
    delete ui;
}
