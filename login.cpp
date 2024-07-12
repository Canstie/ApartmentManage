#include "login.h"
#include "mainwindow.h"
#include "userui.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_signupbtn_clicked()
{
    QString user1 = ui->userEdit->text();
    QString pw = ui->pwEdit->text();
    bool ishost = ui->rbtn2->isChecked();
    User newuser(user1,pw,ishost);
    QString filename = ishost ? "hostAccount.txt":"userAccount.txt";
    QFile file(filename);
    if(file.open(QIODevice::Append|QIODevice::Text)){
        QTextStream stream(&file);
        stream << newuser.getname() << " " << newuser.getpassword()<< "\n";
        file.close();
        QMessageBox::information(this,"注册成功","注册成功");
    }else{
        QMessageBox::warning(this,"警告","文件打不开");
    }
}


void Login::on_loginbtn_clicked()
{
    QString account = ui->userEdit->text();
    QString password = ui->pwEdit->text();
    if (checkCredentials(account, password)) {
        emit loginSuccess(ui->rbtn2->isChecked());  // 简单区分管理员和普通用户
    } else {
        QMessageBox::warning(this,"警告","账户或密码错误");
    }
}

bool Login::checkCredentials(const QString &account, const QString &password) {
    QFile file(ui->rbtn2->isChecked() ? "hostAccount.txt" : "userAccount.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList fields = line.split(" ");
        if (fields.size() == 2 && fields[0] == account && fields[1] == password) {
            return true;
        }
    }
    return false;
}

