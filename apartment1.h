#ifndef APARTMENT1_H
#define APARTMENT1_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class apartment1;
}

class apartment1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit apartment1(QWidget *parent = nullptr);
    ~apartment1();
    void display_apartment_info();
    void contextMenuEvent(QContextMenuEvent *);

private slots:
    void on_apar_read_triggered();
    void on_apar_save_triggered();
    void on_apar_del_triggered();
    void on_apar_add_triggered();
    void on_apar_chg_triggered();

private:
    Ui::apartment1 *ui;
    QAction *Act_Apar_Del;
    QAction *Act_Apar_Chg;
    QAction *Act_Apar_Add;

};

#endif // APARTMENT1_H
