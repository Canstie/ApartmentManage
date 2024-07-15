#include "visit.h"
#include "ui_visit.h"
#include <QHeaderView>

visit::visit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::visit)
{
    ui->setupUi(this);
    // 创建主窗口布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 创建QLineEdit
    lineEdit = new QLineEdit(centralWidget);
    lineEdit->setPlaceholderText("搜索...");

    // 创建QTableWidget用于显示搜索结果
    tableWidget = new QTableWidget(centralWidget);
    tableWidget->setColumnCount(4); // 设置列数
    tableWidget->setHorizontalHeaderLabels(QStringList() << "价格" << "位置" << "户型" << "公寓"); // 设置列头
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从txt文件读取房屋列表作为数据源
    houseList = readHouseData("1.txt");
    qDebug() << houseList.size();

    // 显示所有房屋信息到QTableWidget
    tableWidget->setRowCount(houseList.size());
    for (int row = 0; row < houseList.size(); ++row) {
        const House &house = houseList.at(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(house.getPrice())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(house.getLocation()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(house.getType()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(house.getName()));
    }

    // 创建QCompleter
    QStringList locations;
    for (const House &house : houseList) {
        locations << house.getLocation();
    }
    completer = new QCompleter(locations, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);

    // 将QCompleter设置给QLineEdit
    lineEdit->setCompleter(completer);

    // 连接QLineEdit的textChanged信号到槽函数，实现搜索逻辑
    connect(lineEdit, &QLineEdit::textChanged, this, &visit::filterHouses);

    // 创建QDateEdit用于选择租赁起始日期
    startDateEdit = new QDateEdit(QDate::currentDate(), centralWidget);
    startDateEdit->setCalendarPopup(true);

    // 创建QSpinBox用于选择租赁总时长
    durationSpinBox = new QSpinBox(centralWidget);
    durationSpinBox->setRange(1, 60);
    durationSpinBox->setSuffix(" 月");

    // 创建QPushButton用于租赁房屋
    rentButton = new QPushButton("租赁", centralWidget);

    // 连接QPushButton的clicked信号到槽函数，实现租赁功能
    connect(rentButton, &QPushButton::clicked, this, &visit::rentHouse);

    // 添加控件到布局
    layout->addWidget(lineEdit);
    layout->addWidget(startDateEdit);
    layout->addWidget(durationSpinBox);
    layout->addWidget(tableWidget);
    layout->addWidget(rentButton);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void visit::filterHouses(const QString &text) {
    // 过滤数据源中的项目
    QList<House> filteredList;
    for (const House &house : houseList) {
        if (QString::number(house.getPrice()).contains(text) ||
            house.getLocation().contains(text, Qt::CaseInsensitive) ||
            house.getType().contains(text, Qt::CaseInsensitive) ||
            house.getName().contains(text, Qt::CaseInsensitive)) {
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
    tableWidget->clearContents();
    tableWidget->setRowCount(filteredList.size());

    // 添加匹配的结果到QTableWidget
    for (int row = 0; row < filteredList.size(); ++row) {
        const House &house = filteredList.at(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(house.getPrice())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(house.getLocation()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(house.getType()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(house.getName()));
    }
}

void visit::rentHouse() {
    // 获取当前选中的行
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        int selectedRow = selectedItems.first()->row();
        QString price = tableWidget->item(selectedRow, 0)->text();
        QString location = tableWidget->item(selectedRow, 1)->text();
        QString type = tableWidget->item(selectedRow, 2)->text();
        QString name = tableWidget->item(selectedRow, 3)->text();
        QDate startDate = startDateEdit->date();
        int duration = durationSpinBox->value();
        QDate endDate = startDate.addMonths(duration);

        QString filename = "2.txt";
        QFile file(filename);
        if(file.open(QIODevice::Append|QIODevice::Text)){
            QTextStream stream(&file);
            stream << location << "\t" << price << "\t" << 1 << "\t" << startDate.toString("yyyy-MM-dd") << "\t" << duration << "\t" << endDate.toString("yyyy-MM-dd") << "\n";
            file.close();
        }

        // 显示租赁信息
        QMessageBox::information(this, "租赁", QString("您已成功租房:\n\n价格: %1\n位置: %2\n户型: %3\n公寓：%4\n起始日期: %5\n租赁总时长: %6 月\n结束日期: %7").arg(price).arg(location).arg(type).arg(name).arg(startDate.toString("yyyy-MM-dd")).arg(duration).arg(endDate.toString("yyyy-MM-dd")));
    } else {
        QMessageBox::warning(this, "租赁", "请选择一个户型.");
    }
}

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
    }
    return houseList;
}

visit::~visit()
{
    delete ui;
}
