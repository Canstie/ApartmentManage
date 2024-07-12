#include "mainwindow.h"
#include "login.h"
#include "userui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;
    userui user1;
    MainWindow mainwindow;

    QObject::connect(&login, &Login::loginSuccess, [&](bool isAdmin) {
        if (isAdmin) {
            mainwindow.show();
        } else {
            user1.show();
        }
        login.close();
    });

    login.show();
    return a.exec();
}
