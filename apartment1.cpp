#include "apartment1.h"
#include "ui_apartment1.h"
#include <QByteArray>
#include <QCursor>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QTabWidget>

apartment1::apartment1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::apartment1)
{
    ui->setupUi(this);
    // 预先读取文件
    Apartment.read("1.txt");

    // 窗口大小设置
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // 右键菜单设置
    Act_Apar_Del = new QAction(tr("删除公寓信息"), this);
    Act_Apar_Chg = new QAction(tr("修改公寓信息"), this);
    Act_Apar_Add = new QAction(tr("添加公寓信息"), this);

    connect(Act_Apar_Del, SIGNAL(triggered()), this, SLOT(on_apar_del_triggered()));
    connect(Act_Apar_Chg, SIGNAL(triggered()), this, SLOT(on_apar_chg_triggered()));
    connect(Act_Apar_Add, SIGNAL(triggered()), this, SLOT(on_apar_add_triggered()));

    // Update table headers
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers << "租金" << "位置" << "户型" << "公寓";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    display_apartment_info();
}

apartment1::~apartment1()
{
    delete ui;
}

void apartment1::contextMenuEvent(QContextMenuEvent *event)
{
    QCursor cur = this->cursor();
    QMenu *menu = new QMenu;
    if (ui->tabWidget->currentIndex() == 0)
    {
        menu->addAction(Act_Apar_Del);
        menu->addAction(Act_Apar_Chg);
        menu->addAction(Act_Apar_Add);
    }
    menu->exec(cur.pos());
    delete menu;
}

void apartment1::display_apartment_info()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->clearContents();
    for(int loop = 0; loop < ui->tableWidget->rowCount();)
        ui->tableWidget->removeRow(loop);
    AparInfo *p = Apartment.head;
    while(p != NULL)
    {
        int rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        ui->tableWidget->setItem(rows, 0, new QTableWidgetItem(p->price));
        ui->tableWidget->setItem(rows, 1, new QTableWidgetItem(p->location));
        ui->tableWidget->setItem(rows, 2, new QTableWidgetItem(p->type));
        ui->tableWidget->setItem(rows, 3, new QTableWidgetItem(p->name));
        p = p->next;
    }
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item) {
                item->setTextAlignment(Qt::AlignCenter); // 设置文本居中对齐
            }
        }
    }
}

void apartment1::on_apar_read_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "打开文件", ".", ("文本文件(*.txt)"));
    if (fileNames.size() == 0) return;
    for (int i = 0; i < fileNames.size(); ++i)
    {
        QByteArray bytearray = fileNames[i].toUtf8();
        const char *temp = bytearray.data();
        if (temp == NULL) continue;
        Apartment.read(temp);
    }
    char buffer[20];
    itoa(Apartment.count, buffer, 10);
    char output[100];
    strcat(output, "导入完成，当前一共有");
    strcat(output, buffer);
    strcat(output, "个数据");
    QMessageBox::information(NULL, "导入完成", output, QMessageBox::Ok, QMessageBox::Ok);
    display_apartment_info();
}

void apartment1::on_apar_del_triggered()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString text;
    if (!items.count() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(NULL, tr("删除公寓数据"), tr("请输入公寓信息"));
    }
    else
    {
        QTableWidgetItem *item = (ui->tabWidget->currentIndex() == 0) ? items.at(3) : items.at(0);
        text = item->text();
    }
    if (text.isEmpty())
        return;
    QByteArray bytearray = text.toUtf8();
    const char *temp = bytearray.constData();
    AparInfo *p = new AparInfo;
    strcpy(p->name, temp);
    if (Apartment.del(p, 0))
    {
        QMessageBox::information(NULL, "删除结果", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    }
    else
        QMessageBox::information(NULL, "删除结果", "删除失败-不存在此公寓", QMessageBox::Ok, QMessageBox::Ok);
    delete p;
    display_apartment_info();
}

void apartment1::on_apar_add_triggered()
{
    QString price = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入租金"));
    if (price.isEmpty()) return;
    QString location = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入地区"));
    if (location.isEmpty()) return;
    QString type = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入户型"));
    if (type.isEmpty()) return;
    QString name = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入公寓名称"));
    if (name.isEmpty()) return;

    AparInfo *p = new AparInfo;
    p->next = NULL;
    strcpy(p->price, price.toUtf8().data());
    strcpy(p->location, location.toUtf8().data());
    strcpy(p->type, type.toUtf8().data());
    strcpy(p->name, name.toUtf8().data());

    if (Apartment.add(p))
        QMessageBox::information(NULL, "添加结果", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "添加结果", "添加失败-公寓重复", QMessageBox::Ok, QMessageBox::Ok);

    display_apartment_info();
    QString fileName = "1.txt";
    if (fileName.length() == 0) return;
    QByteArray bytearray = fileName.toUtf8();
    const char *temp = bytearray.constData();
    Apartment.save(temp);
    display_apartment_info();
}

void apartment1::on_apar_chg_triggered()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString name;
    if (!items.count()) {
        name = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入公寓名称"));
    } else {
        QTableWidgetItem *item = items.at(3);
        name = item->text();
    }
    if (name.isEmpty()) return;

    QString price = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入新租金"));
    if (price.isEmpty()) return;
    QString location = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入新地区"));
    if (location.isEmpty()) return;
    QString type = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入新户型"));
    if (type.isEmpty()) return;

    AparInfo *p = new AparInfo;
    p->next = NULL;
    strcpy(p->name, name.toUtf8().data());
    strcpy(p->price, price.toUtf8().data());
    strcpy(p->location, location.toUtf8().data());
    strcpy(p->type, type.toUtf8().data());

    if (Apartment.chg(p, 0))
        QMessageBox::information(NULL, "修改结果", "修改成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "修改结果", "修改失败-公寓不存在", QMessageBox::Ok, QMessageBox::Ok);

    delete p;
    display_apartment_info();
    QString fileName = "1.txt";
    if (fileName.length() == 0) return;
    QByteArray bytearray = fileName.toUtf8();
    const char *temp = bytearray.constData();
    Apartment.save(temp);
    display_apartment_info();
}
