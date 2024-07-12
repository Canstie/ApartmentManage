#ifndef LEASEMANAGEMENT_H
#define LEASEMANAGEMENT_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QDate>

class LeaseRecord {
public:
    LeaseRecord(const QString &location = "", int price = 0, int rooms = 0,
                const QDate &startDate = QDate::currentDate(), int duration = 0);

    QString getLocation() const;
    void setLocation(const QString &location);

    int getPrice() const;
    void setPrice(int price);

    int getRooms() const;
    void setRooms(int rooms);

    QDate getStartDate() const;
    void setStartDate(const QDate &startDate);

    QDate getEndDate() const;

    int getDuration() const;
    void setDuration(int duration);
    void updateEndDate(); // 更新租赁结束日期

private:
    QString location;
    int price;
    int rooms;
    QDate startDate;
    QDate endDate;
    int duration;
};

namespace Ui {
class LeaseManagement;
}

class LeaseManagement : public QWidget
{
    Q_OBJECT

public:
    explicit LeaseManagement(QWidget *parent = nullptr);
    ~LeaseManagement();

private slots:
    void on_add_clicked();
    void on_modify_clicked();
    void on_delete_2_clicked();
    void on_save_clicked(); // 保存租赁记录到txt文件
    void on_load_clicked(); // 加载租赁记录
    void on_delete_condition_clicked();
    void on_filter_clicked();

private:
    Ui::LeaseManagement *ui;
    QVector<LeaseRecord> leaseRecords; // 存储租赁记录
    void refreshTable(); // 刷新表格显示的函数
    void refreshTable(const QVector<LeaseRecord> &records); // 刷新表格显示的函数
    void loadSampleData(); // 加载示例数据
    void saveToFile(const QString &fileName); // 保存数据到文件
    void loadFromFile(const QString &fileName); // 从文件加载数据
    void deleteRecord(const QString &condition); // 根据条件删除记录
    void filterRecords(const QString &condition); // 根据条件筛选记录
};

#endif // LEASEMANAGEMENT_H
