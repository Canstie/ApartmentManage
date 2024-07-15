#ifndef VISIT_H
#define VISIT_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QCompleter>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>
#include <QDateEdit>
#include <QSpinBox>
#include <QDebug>

namespace Ui {
class visit;
}

// 定义一个类来存储房屋信息
class House {
public:
    House(int price, const QString &location, const QString &type, const QString &name)
        : price(price), location(location), type(type), name(name) {}

    int getPrice() const { return price; }
    QString getLocation() const { return location; }
    QString getType() const { return type; }
    QString getName() const { return name; }

private:
    int price;
    QString location;
    QString type;
    QString name;
};

QList<House> readHouseData(const QString &fileName);

class visit : public QMainWindow
{
    Q_OBJECT

public:
    explicit visit(QWidget *parent = nullptr);
    ~visit();

private slots:
    void filterHouses(const QString &text);
    void rentHouse();

private:
    Ui::visit *ui;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QCompleter *completer;
    QPushButton *rentButton;
    QDateEdit *startDateEdit;
    QSpinBox *durationSpinBox;
    QList<House> houseList;
};

#endif // VISIT_H
