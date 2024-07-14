#include "information.h"
#include "ui_information.h"

information::information(const QString &account, bool isHost, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::information),
    originalAccount(account),
    isHost(isHost)
{
    ui->setupUi(this);
    filepath = isHost ? "hostAccount.txt" : "userAccount.txt";
    loadAccountInfo();
}

information::~information()
{
    delete ui;
}

void information::loadAccountInfo() {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开账户文件");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(",");
        if (fields[0] == originalAccount) {
            ui->lineEdit_4->setText(fields[0]); // 账号
            ui->lineEdit_3->setText(fields[1]); // 密码
            break;
        }
    }
    file.close();
}

void information::saveAccountInfo(const QString &newAccount, const QString &newPassword) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开账户文件");
        return;
    }
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(",");
        if (fields.size() == 2 && fields[0] == originalAccount) {
            lines.append(newAccount + "," + newPassword);
        } else {
            lines.append(line);
        }
    }
    file.resize(0);
    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();
    originalAccount = newAccount; // 更新原始账号
    QMessageBox::information(this, "成功", "账户信息已修改");
}

void information::deleteAccountInfo() {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开账户文件");
        return;
    }
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(",");
        if (fields.size() == 2 && fields[0] != originalAccount) {
            lines.append(line);
        }
    }
    file.resize(0);
    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();
    QMessageBox::information(this, "成功", "账户已注销");
    close(); // 关闭窗口
}

void information::on_pushButton_4_clicked() {
    QString newAccount = ui->lineEdit_4->text();
    QString newPassword = ui->lineEdit_3->text();
    saveAccountInfo(newAccount, newPassword);
}

void information::on_pushButton_3_clicked() {
    int ret = QMessageBox::warning(this, "确认", "确定要注销此账户吗？", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        deleteAccountInfo();
    }
}
