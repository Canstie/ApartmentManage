#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "userui.h"
#include "mainwindow.h"

namespace Ui {
class Login;
}



class User {
public:
    User(QString name, QString password, bool isHost)
        : _name(name), _password(password), _isHost(isHost) {}
    QString getName() { return _name; }
    QString getPassword() { return _password; }
    bool getIsHost() { return _isHost; }

private:
    QString _name;
    QString _password;
    bool _isHost;
};

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void loginSuccess(const QString &account, bool isAdmin);
    void senddata1(const QString &data);
    void senddata2(const QString &data);

private slots:
    void on_signupbtn_clicked();
    void on_loginbtn_clicked();

private:
    Ui::Login *ui;
    MainWindow *mw;
    userui *us;
    bool checkCredentials(const QString &account, const QString &password);
};

#endif // LOGIN_H
