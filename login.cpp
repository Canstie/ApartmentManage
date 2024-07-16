#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Login::Login(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Login), mw(new MainWindow), us(new userui)
{
    ui->setupUi(this);
    connect(this, &Login::senddata1, mw, &MainWindow::recievedata1);
    connect(this, &Login::senddata2, us, &userui::recievedata2);

    // 设置窗口图标
    //setWindowIcon(QIcon(":/icons/login_icon.png"));
}

Login::~Login()
{
    delete ui;
}

void Login::on_signupbtn_clicked()
{
    QString user1 = ui->userEdit->text();
    QString pw = ui->pwEdit->text();
    bool isHost = ui->rbtn2->isChecked();
    User newUser(user1, pw, isHost);
    QString filename = isHost ? "hostAccount.txt" : "userAccount.txt";
    QFile file(filename);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << newUser.getName() << "," << newUser.getPassword() << "\n";
        file.close();
        QMessageBox::information(this, "注册成功", "注册成功");
    } else {
        QMessageBox::warning(this, "警告", "文件打不开");
    }
}

void Login::on_loginbtn_clicked()
{
    QString account = ui->userEdit->text();
    QString password = ui->pwEdit->text();
    if (checkCredentials(account, password)) {
        if(ui->rbtn2->isChecked()) {
            emit senddata1(account);
            mw->show();
            this->close();
        } else {
            emit senddata2(account);
            us->show();
            this->close();
        }
    } else {
        QMessageBox::warning(this, "警告", "账户或密码错误");
    }
}

bool Login::checkCredentials(const QString &account, const QString &password)
{
    QFile file(ui->rbtn2->isChecked() ? "hostAccount.txt" : "userAccount.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(",");
        if (fields.size() == 2 && fields[0] == account && fields[1] == password) {
            return true;
        }
    }
    return false;
}
