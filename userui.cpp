#include "userui.h"
#include "ui_userui.h"
#include "information.h"
#include "visit.h"
#include "myinfor.h"

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

void userui::recievedata2(const QString &data){
    ddd = data;
}

void userui::on_pushButton_3_clicked()
{
    openInformation();
}

void userui::openInformation() {
    information *info = new information(ddd, false);
    info->show();
}

void userui::on_pushButton_clicked()
{
    visit *a =new visit;
    a->show();
}


void userui::on_pushButton_2_clicked()
{
    myinfor *a = new myinfor;
    a->show();
}

