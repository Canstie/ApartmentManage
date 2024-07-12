#include "leasemanagement.h"
#include "ui_leasemanagement.h"
#include <QFileDialog>
#include <QTextStream>

LeaseRecord::LeaseRecord(const QString &location, int price, int rooms, const QDate &startDate, int duration)
    : location(location), price(price), rooms(rooms), startDate(startDate), duration(duration) {
    updateEndDate();
}

QString LeaseRecord::getLocation() const {
    return location;
}

void LeaseRecord::setLocation(const QString &location) {
    this->location = location;
}

int LeaseRecord::getPrice() const {
    return price;
}

void LeaseRecord::setPrice(int price) {
    this->price = price;
}

int LeaseRecord::getRooms() const {
    return rooms;
}

void LeaseRecord::setRooms(int rooms) {
    this->rooms = rooms;
}

QDate LeaseRecord::getStartDate() const {
    return startDate;
}

void LeaseRecord::setStartDate(const QDate &startDate) {
    this->startDate = startDate;
    updateEndDate();
}

QDate LeaseRecord::getEndDate() const {
    return endDate;
}

int LeaseRecord::getDuration() const {
    return duration;
}

void LeaseRecord::setDuration(int duration) {
    this->duration = duration;
    updateEndDate();
}

void LeaseRecord::updateEndDate() {
    endDate = startDate.addMonths(duration);
}

LeaseManagement::LeaseManagement(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LeaseManagement)
{
    ui->setupUi(this);

    loadSampleData();
    refreshTable();

}

LeaseManagement::~LeaseManagement()
{
    delete ui;
}

void LeaseManagement::refreshTable()
{
    refreshTable(leaseRecords);
}

void LeaseManagement::refreshTable(const QVector<LeaseRecord> &records)
{
    ui->tableWidget->setRowCount(records.size());
    ui->tableWidget->setColumnCount(6);

    QStringList headers = {"位置", "价格", "房间数", "租赁起始日期", "租赁总时长/月", "租赁结束日期"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < records.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(records[i].getLocation()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(records[i].getPrice())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(records[i].getRooms())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(records[i].getStartDate().toString("yyyy-MM-dd")));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(records[i].getDuration())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(records[i].getEndDate().toString("yyyy-MM-dd")));
    }
}

void LeaseManagement::loadSampleData()
{
    leaseRecords.append(LeaseRecord("北京市", 5000, 3, QDate(2023, 1, 1), 12));
    leaseRecords.append(LeaseRecord("上海市", 6000, 2, QDate(2023, 2, 1), 24));
    leaseRecords.append(LeaseRecord("广州市", 4500, 1, QDate(2023, 3, 1), 6));
    leaseRecords.append(LeaseRecord("深圳市", 7000, 4, QDate(2023, 4, 1), 36));
}

void LeaseManagement::on_add_clicked()
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);

    LeaseRecord newRecord;
    leaseRecords.append(newRecord);

    refreshTable();
}

void LeaseManagement::on_modify_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        leaseRecords[currentRow].setLocation(ui->tableWidget->item(currentRow, 0)->text());
        leaseRecords[currentRow].setPrice(ui->tableWidget->item(currentRow, 1)->text().toInt());
        leaseRecords[currentRow].setRooms(ui->tableWidget->item(currentRow, 2)->text().toInt());
        leaseRecords[currentRow].setStartDate(QDate::fromString(ui->tableWidget->item(currentRow, 3)->text(), "yyyy-MM-dd"));
        leaseRecords[currentRow].setDuration(ui->tableWidget->item(currentRow, 4)->text().toInt());

        leaseRecords[currentRow].updateEndDate();

        refreshTable();
    }
}

void LeaseManagement::on_delete_2_clicked()
{
    int currentRow = ui->tableWidget->currentRow();
    if (currentRow >= 0) {
        ui->tableWidget->removeRow(currentRow);
        leaseRecords.remove(currentRow);
        refreshTable();
    }
}

void LeaseManagement::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存租赁记录", QDir::homePath(), "Text Files (*.txt)");
    if (fileName.isEmpty())
        return;

    saveToFile(fileName);
}

void LeaseManagement::on_load_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "加载租赁记录", QDir::homePath(), "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        loadFromFile(fileName);
    }
}

void LeaseManagement::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 处理文件打开失败的情况，例如弹出错误消息框
        return;
    }

    QTextStream out(&file);
    out << "位置\t价格\t房间数\t租赁起始日期\t租赁总时长/月\t租赁结束日期\n";
    for (const auto &record : leaseRecords) {
        out << record.getLocation() << '\t'
            << record.getPrice() << '\t'
            << record.getRooms() << '\t'
            << record.getStartDate().toString("yyyy-MM-dd") << '\t'
            << record.getDuration() << '\t'
            << record.getEndDate().toString("yyyy-MM-dd") << '\n';
    }
    file.close();
}

void LeaseManagement::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 处理文件打开失败的情况，例如弹出错误消息框
        return;
    }

    leaseRecords.clear();
    QTextStream in(&file);
    QString header = in.readLine(); // 读取表头
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split('\t');
        if (fields.size() == 6) {
            QString location = fields[0];
            int price = fields[1].toInt();
            int rooms = fields[2].toInt();
            QDate startDate = QDate::fromString(fields[3], "yyyy-MM-dd");
            int duration = fields[4].toInt();
            LeaseRecord record(location, price, rooms, startDate, duration);
            leaseRecords.append(record);
        }
    }
    file.close();
    refreshTable();
}

void LeaseManagement::deleteRecord(const QString &condition)
{
    // 遍历 leaseRecords 找到符合条件的记录并删除
    auto it = std::remove_if(leaseRecords.begin(), leaseRecords.end(), [&condition](const LeaseRecord &record) {
        return record.getLocation().contains(condition, Qt::CaseInsensitive);
    });

    // 删除符合条件的记录
    if (it != leaseRecords.end()) {
        leaseRecords.erase(it, leaseRecords.end());
        // 刷新表格显示
        refreshTable();
    }
}

void LeaseManagement::filterRecords(const QString &condition)
{
    QVector<LeaseRecord> filteredRecords;
    for (const auto &record : leaseRecords) {
        if (record.getLocation() == condition) {
            filteredRecords.append(record);
        }
    }
    refreshTable(filteredRecords);
}

void LeaseManagement::on_delete_condition_clicked()
{
    QString condition = ui->condition->text();
    if (!condition.isEmpty()) {
        deleteRecord(condition);
    }
}

void LeaseManagement::on_filter_clicked()
{
    QString condition = ui->condition->text();
    if (!condition.isEmpty()) {
        filterRecords(condition);
    }
}
