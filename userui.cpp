#include "userui.h"
#include "ui_userui.h"
#include "information.h"
#include "visit.h"

userui::userui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userui)
{
    ui->setupUi(this);
}

userui::~userui()
{
    delete ui;
}

void userui::on_pushButton_3_clicked()
{
    openInformation();
}

void userui::openInformation() {
    information *info = new information("userAccount.txt", this);
    info->show();
}

void userui::on_pushButton_clicked()
{
    visit *a =new visit;
    a->show();
}

