#include "login.h"
#include "mainwindow.h"
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

void Login::on_UserChoseAction_triggered()
{
    if(ui->UserChoseAction->isChecked()==true)
    {
        ui->UserChoseAction->setText("房主登录");
        ui->UserChoseAction->setToolTip("房主登录");
        ui->UserChoseAction->setStatusTip("房主登录");
    }else{
        ui->UserChoseAction->setText("用户登录");
        ui->UserChoseAction->setToolTip("用户登录");
        ui->UserChoseAction->setStatusTip("用户登录");
    }
}


void Login::on_signupbtn_clicked()
{
    QString user1 = ui->userEdit->text();
    QString pw = ui->pwEdit->text();
    bool ishost = ui->UserChoseAction->isChecked();
    User newuser(user1,pw,ishost);
    QString filename = ishost ? "hostAccount.txt":"userAccount.txt";
    QFile file(filename);
    if(file.open(QIODevice::Append|QIODevice::Text)){
        QTextStream stream(&file);
        stream << newuser.getname() << " " << newuser.getpassword()<< "\n";
        file.close();
        QMessageBox::information(this,"注册成功","注册成功");
    }else{
        QMessageBox::warning(this,"警告","注册失败");
    }
}


void Login::on_loginbtn_clicked()
{
    QString user1 = ui->userEdit->text();
    QString pw = ui->pwEdit->text();
    QString filename = ui->UserChoseAction->isChecked() ? "hostAccount.txt" : "userAccount.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&file);
        bool found = false;
        while(!in.atEnd()){
            QString line = in.readLine().trimmed();
            QStringList fields = line.split(" ");
            if(fields[0] == user1 && fields[1] == pw){
                found = true;
                MainWindow *a = new MainWindow;
                a->show();
                this->close();
                break;
            }
        }
        file.close();
        if(!found){
            QMessageBox::warning(this,"登陆失败","用户名或密码错误");
        }
    }else{
        QMessageBox::critical(this,"错误","无法打开账户文件");
    }
}

