#ifndef USERUI_H
#define USERUI_H

#include <QWidget>

namespace Ui {
class userui;
}

class userui : public QWidget
{
    Q_OBJECT

public:
    explicit userui(QWidget *parent = nullptr);
    ~userui();
public slots:
    void recievedata2(const QString &data);
private slots:
    void openInformation();
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userui *ui;
    QString ddd;
};

#endif // USERUI_H
