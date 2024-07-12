#include "information.h"
#include "ui_information.h"
#include <QMessageBox>

information::information(const QString &filePath,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::information),filepath(filePath)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    loadInformation(filePath);
}

information::~information()
{
    delete ui;
}

void information::loadInformation(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() == 2) {
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fields[0]));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(fields[1]));
            row++;
        }
    }
    file.close();
}


void information::on_pushButton_2_clicked()
{
    handleSaveChanges();
}

void information::handleSaveChanges() {
    QString filePath = getfilepath();
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "保存失败", "打开失败");
        return;
    }

    QTextStream out(&file);

    int rowCount = ui->tableWidget->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *accountItem = ui->tableWidget->item(row, 0);
        QTableWidgetItem *passwordItem = ui->tableWidget->item(row, 1);

        if (accountItem && passwordItem) {
            QString account = accountItem->text();
            QString password = passwordItem->text();
            out << account << " " << password << "\n";
        }
    }
    file.close();
    QMessageBox::information(this, "保存成功", "账户密码已经被保存");
}
