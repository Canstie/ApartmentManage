#include "apartment1.h"
#include "ui_apartment1.h"
#include "apartment.h"
#include <QContextMenuEvent>

apartment Apartment;

extern QByteArray AnsiToUtf8(QByteArray &ansi);

apartment1::apartment1(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::apartment1)
{
    ui->setupUi(this);

    // Read file in advance
    Apartment.read("apar.txt");

    // Set window size
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // Set right-click menu
    Act_Apar_Del = new QAction(tr("删除公寓信息"), this);
    Act_Apar_Chg = new QAction(tr("修改公寓信息"), this);
    Act_Apar_Add = new QAction(tr("添加公寓信息"), this);

    connect(Act_Apar_Del, &QAction::triggered, this, &apartment1::on_apar_del_triggered);
    connect(Act_Apar_Chg, &QAction::triggered, this, &apartment1::on_apar_chg_triggered);
    connect(Act_Apar_Add, &QAction::triggered, this, &apartment1::on_apar_add_triggered);
}

apartment1::~apartment1()
{
    delete ui;
}

void apartment1::contextMenuEvent(QContextMenuEvent *)
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
    while (ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(0);
    }

    AparInfo *p = Apartment.head;
    while (p != nullptr)
    {
        int rows = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rows);
        ui->tableWidget->setItem(rows, 0, new QTableWidgetItem(p->name));
        ui->tableWidget->setItem(rows, 1, new QTableWidgetItem(p->id));
        p = p->next;
    }

    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
        {
            QTableWidgetItem *item = ui->tableWidget->item(row, col);
            if (item)
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void apartment1::on_apar_read_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("打开文件"), ".", tr("文本文件(*.txt)"));
    if (fileNames.isEmpty()) return;

    for (const QString &fileName : fileNames)
    {
        QByteArray byteArray = fileName.toLocal8Bit();
        char *temp = byteArray.data();
        if (temp == nullptr) continue;
        Apartment.read(temp);
    }

    char buffer[20];
    itoa(Apartment.count, buffer, 10);
    char output[100] = "导入完成，当前一共有";
    strcat(output, buffer);
    strcat(output, "个数据");

    QMessageBox::information(this, tr("导入完成"), tr(output), QMessageBox::Ok, QMessageBox::Ok);
    display_apartment_info();
}

void apartment1::on_apar_save_triggered()
{
    QString fileName = "1.txt";
    if (fileName.isEmpty()) return;

    QByteArray byteArray = fileName.toLocal8Bit();
    char *temp = byteArray.data();
    Apartment.save(temp);

    QMessageBox::information(this, tr("保存完成"), tr("保存完成"), QMessageBox::Ok, QMessageBox::Ok);
    display_apartment_info();
}

void apartment1::on_apar_del_triggered()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString text;

    if (items.isEmpty() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(this, tr("删除公寓数据"), tr("请输入公寓信息"));
    }
    else
    {
        QTableWidgetItem *item = (ui->tabWidget->currentIndex() == 0) ? items.at(1) : items.at(0);
        text = item->text();
    }

    if (text.isEmpty()) return;

    QByteArray byteArray = text.toLocal8Bit();
    byteArray = AnsiToUtf8(byteArray);
    char temp[20];
    strcpy(temp, byteArray.data());

    AparInfo *p = new AparInfo;
    p->next = nullptr;
    strcpy(p->id, temp);

    if (Apartment.del(p, 1))
    {
        QMessageBox::information(this, tr("删除结果"), tr("删除成功"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("删除结果"), tr("删除失败-不存在此公寓"), QMessageBox::Ok, QMessageBox::Ok);
    }
    delete p;
    display_apartment_info();
}

void apartment1::on_apar_add_triggered()
{
    QString idText = QInputDialog::getText(this, tr("添加公寓数据"), tr("请输入公寓信息"));
    if (idText.isEmpty()) return;

    QByteArray idByteArray = idText.toLocal8Bit();
    idByteArray = AnsiToUtf8(idByteArray);
    char *aparid = idByteArray.data();

    QString infoText = QInputDialog::getText(this, tr("添加公寓数据"), tr("请输入租金，地区，户型信息"));
    if (infoText.isEmpty()) return;

    QByteArray infoByteArray = infoText.toLocal8Bit();
    infoByteArray = AnsiToUtf8(infoByteArray);
    char *aparname = infoByteArray.data();

    AparInfo *p = new AparInfo;
    p->next = nullptr;
    strcpy(p->id, aparid);
    strcpy(p->name, aparname);

    if (Apartment.add(p))
    {
        QMessageBox::information(this, tr("添加结果"), tr("添加成功"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("添加结果"), tr("添加失败-公寓重复"), QMessageBox::Ok, QMessageBox::Ok);
    }
    display_apartment_info();
}

void apartment1::on_apar_chg_triggered()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QString text;

    if (items.isEmpty() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(this, tr("修改公寓数据"), tr("请输入公寓信息"));
    }
    else
    {
        QTableWidgetItem *item = (ui->tabWidget->currentIndex() == 0) ? items.at(1) : items.at(0);
        text = item->text();
    }

    if (text.isEmpty()) return;

    QByteArray byteArray = text.toLocal8Bit();
    byteArray = AnsiToUtf8(byteArray);
    char aparid[20];
    strcpy(aparid, byteArray.data());

    QString infoText = QInputDialog::getText(this, tr("修改公寓数据"), tr("请输入新信息（租金 地区 户型）"));
    if (infoText.isEmpty()) return;

    QByteArray infoByteArray = infoText.toLocal8Bit();
    infoByteArray = AnsiToUtf8(infoByteArray);
    char *aparnewname = infoByteArray.data();

    AparInfo *p = new AparInfo;
    p->next = nullptr;
    strcpy(p->id, aparid);
    strcpy(p->name, aparnewname);

    if (Apartment.chg(p, 0))
    {
        QMessageBox::information(this, tr("修改结果"), tr("修改成功"), QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, tr("修改结果"), tr("修改失败-公寓不存在"), QMessageBox::Ok, QMessageBox::Ok);
    }
    delete p;
    display_apartment_info();
}
