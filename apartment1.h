#ifndef APARTMENT1_H
#define APARTMENT1_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "apartment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class apartment1; }
QT_END_NAMESPACE

class apartment1 : public QMainWindow
{
    Q_OBJECT

public:
    apartment1(QWidget *parent = nullptr);
    ~apartment1();

private slots:
    void on_apar_add_triggered();
    void on_apar_del_triggered();
    void on_apar_chg_triggered();
    void on_apar_read_triggered();
    void contextMenuEvent(QContextMenuEvent *event);
    void display_apartment_info();

private:
    Ui::apartment1 *ui;
    QAction *Act_Apar_Del;
    QAction *Act_Apar_Chg;
    QAction *Act_Apar_Add;
    apartment Apartment;
};

#endif // APARTMENT1_H
