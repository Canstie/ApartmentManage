#ifndef VISIT2_H
#define VISIT2_H
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
#include <QWidget>

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

QList<House> readHouseData1(const QString &fileName);


namespace Ui {
class visit2;
}

class visit2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit visit2(QWidget *parent = nullptr);
    ~visit2();

private slots:
    void filterHouses(const QString &text);
    void rentHouse();

private:
    Ui::visit2 *ui;
    QLineEdit *lineEdit;
    QTableWidget *tableWidget;
    QCompleter *completer;
    QPushButton *rentButton;
    QDateEdit *startDateEdit;
    QSpinBox *durationSpinBox;
    QList<House> houseList;
};

#endif // VISIT2_H
