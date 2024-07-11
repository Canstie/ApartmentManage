#include "userui.h"
#include "ui_userui.h"

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
