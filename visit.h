#ifndef VISIT_H
#define VISIT_H

#include <QMainWindow>
#include <QCompleter>
#include <QStringListModel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class visit;
}

    // 定义一个类来存储房屋信息
    class House {
public:
    House(int price, const QString &location, const QString &type,const QString &name)
        : price(price), location(location), type(type) ,name(name){}

    int getPrice() const { return price; }
    QString getLocation() const { return location; }
    QString getType() const { return type; }
    QString getname() const {return name;}

private:
    int price;
    QString location;
    QString type;
    QString name;
};

class visit : public QMainWindow
{
    Q_OBJECT

public:
    explicit visit(QWidget *parent = nullptr);
    ~visit();

private:
    Ui::visit *ui;
};

#endif // VISIT_H
