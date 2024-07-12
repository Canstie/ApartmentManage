#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class Login;
}

class User{
public:
    User(QString name,QString passward,bool isHost)
        :_name(name),_passward(passward),_isHost(isHost)
    {}
    QString getname(){return _name;}
    QString getpassword(){return _passward;}
    bool getishost(){return _isHost;}

private:
    QString _name;
    QString _passward;
    bool _isHost;
};

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
signals:
    void loginSuccess(bool isAdmin);

private slots:
    void on_signupbtn_clicked();
    void on_loginbtn_clicked();


private:
    Ui::Login *ui;
    bool checkCredentials(const QString &account, const QString &password);
};

#endif // LOGIN_H
