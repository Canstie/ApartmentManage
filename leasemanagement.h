#ifndef LEASEMANAGEMENT_H
#define LEASEMANAGEMENT_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class LeaseManagement;
}

class LeaseManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeaseManagement(QWidget *parent = nullptr);
    ~LeaseManagement();

private slots:
    void addLease();
    void deleteLease();
    void modifyLease();

private:
    Ui::LeaseManagement *ui;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *modifyButton;
    void loadLeases();
};

#endif // LEASEMANAGEMENT_H
