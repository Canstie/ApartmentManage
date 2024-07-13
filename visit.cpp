#include "visit.h"
#include "ui_visit.h"


QList<House> readHouseData(const QString &fileName) {
    QList<House> houseList;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList fields = line.split(" ");
            if (fields.size() == 4) {
                House house(fields.at(0).toInt(), fields.at(1), fields.at(2), fields.at(3));
                houseList.append(house);
            }
        }
        file.close();
    } else {
        qDebug() << "Failed to open file:" << fileName;
    }
    return houseList;
}

visit::visit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::visit)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4); // 设置列数
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "价格" << "位置" << "户型"<<"公寓"); // 设置列头
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // 从txt文件读取房屋列表作为数据源
    QList<House> houseList = readHouseData("1.txt");
    qDebug()<<houseList.size();
    // 显示所有房屋信息到QTableWidget
    ui->tableWidget->setRowCount(houseList.size());
    for (int row = 0; row < houseList.size(); ++row) {
        const House &house = houseList.at(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(house.getPrice())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(house.getLocation()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(house.getType()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(house.getname()));
    }

    // 创建QCompleter
    QStringList locations;
    for (const House &house : houseList) {
        locations << house.getLocation();
    }
    QCompleter *completer = new QCompleter(locations, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    // 将QCompleter设置给QLineEdit
    ui->lineEdit->setCompleter(completer);

    // 连接QLineEdit的textChanged信号到槽函数，实现搜索逻辑
    QObject::connect(ui->lineEdit, &QLineEdit::textChanged, [&houseList, completer, this](const QString &text) {
        // 过滤数据源中的项目
        QList<House> filteredList;
        for (const House &house : houseList) {
            if (QString::number(house.getPrice()).contains(text) ||
                house.getLocation().contains(text, Qt::CaseInsensitive) ||
                house.getType().contains(text, Qt::CaseInsensitive)||
                house.getname().contains(text,Qt::CaseInsensitive)) {
                filteredList.append(house);
            }
        }

        // 更新QCompleter的模型
        QStringList filteredLocations;
        for (const House &house : filteredList) {
            filteredLocations << house.getLocation();
        }
        completer->setModel(new QStringListModel(filteredLocations, completer));

        // 清空QTableWidget
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(filteredList.size());

        // 添加匹配的结果到QTableWidget
        for (int row = 0; row < filteredList.size(); ++row) {
            const House &house = filteredList.at(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(house.getPrice())));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(house.getLocation()));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(house.getType()));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(house.getname()));
        }
    });


    // 连接QPushButton的clicked信号到槽函数，实现租赁功能
    QObject::connect(ui->pushButton, &QPushButton::clicked, [this] {
        // 获取当前选中的行

        QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
        if (!selectedItems.isEmpty()) {
            int selectedRow = selectedItems.first()->row();
            QString price = ui->tableWidget->item(selectedRow, 0)->text();
            QString location = ui->tableWidget->item(selectedRow, 1)->text();
            QString type = ui->tableWidget->item(selectedRow, 2)->text();
            QString name = ui->tableWidget->item(selectedRow,3)->text();

            // 显示租赁信息
            QMessageBox::information(nullptr, "租赁", QString("您已成功租房:\n\n价格: %1\n位置: %2\n户型: %3\n公寓：%4").arg(price).arg(location).arg(type).arg(name));
            QString filename = "2.txt";
            QFile file(filename);
            if(file.open(QIODevice::Append|QIODevice::Text)){
                QTextStream stream(&file);
                stream << price << " " << location << " " << type << " " << name << "\n";
                file.close();
            }


        } else {
            QMessageBox::warning(nullptr, "租赁", "请选择一个户型.");
        }
    });
}

visit::~visit()
{
    delete ui;
}


