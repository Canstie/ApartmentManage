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
private slots:
    void openInformation();
    void on_pushButton_3_clicked();

private:
    Ui::userui *ui;
};

#endif // USERUI_H
