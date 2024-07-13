#ifndef MYINFOR_H
#define MYINFOR_H

#include <QWidget>

namespace Ui {
class myinfor;
}

class myinfor : public QWidget
{
    Q_OBJECT

public:
    explicit myinfor(QWidget *parent = nullptr);
    ~myinfor();

private:
    Ui::myinfor *ui;
};

#endif // MYINFOR_H
