#include "mainwindow.h"
#include "login.h"
#include "userui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;

    QObject::connect(&login, &Login::loginSuccess, [&](const QString &account, bool isAdmin) {
        if (isAdmin) {
            MainWindow *mainwindow = new MainWindow;
            mainwindow->show();
        } else {
            userui *user1 = new userui;
            user1->show();
        }
        login.close();
    });

    login.show();
    return a.exec();
}
