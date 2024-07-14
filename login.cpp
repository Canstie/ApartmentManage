#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Login), mw(new MainWindow), us(new userui)
{
    ui->setupUi(this);
    connect(this,&Login::senddata1,mw,&MainWindow::recievedata1);
    connect(this,&Login::senddata2,us,&userui::recievedata2);

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
        if(ui->rbtn2->isChecked()==true){
            emit senddata1(account);
            mw->show();
            //this->show();
        }
        else{
            emit senddata2(account);
            us->show();
            //this->show();
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
