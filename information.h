#ifndef INFORMATION_H
#define INFORMATION_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class information;
}

class information : public QMainWindow
{
    Q_OBJECT

public:
    explicit information(const QString &account, bool isHost, QWidget *parent = nullptr);
    ~information();

private:
    Ui::information *ui;
    QString originalAccount;
    bool isHost;
    QString filepath;
    void loadAccountInfo();
    void saveAccountInfo(const QString &newAccount, const QString &newPassword);
    void deleteAccountInfo();

private slots:
    void on_pushButton_4_clicked(); // 修改按钮
    void on_pushButton_3_clicked(); // 注销按钮
};

#endif // INFORMATION_H
