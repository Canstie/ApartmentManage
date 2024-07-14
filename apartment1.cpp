#include "apartment1.h"
#include "ui_apartment1.h"
#include "apartment.h"

apartment Apartment;

extern QByteArray AnsiToUtf8(QByteArray &ansi);

apartment1::apartment1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::apartment1)
{
    ui->setupUi(this);
    //预先读取文件
    Apartment.read("apar.txt");

    //窗口大小设置
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    //右键菜单设置
    Act_Apar_Del = new QAction(tr("删除公寓信息"), this);
    Act_Apar_Chg = new QAction(tr("修改公寓信息"), this);
    Act_Apar_Add = new QAction(tr("添加公寓信息"), this);

    connect(Act_Apar_Del, SIGNAL(triggered()), this, SLOT(on_apar_del_triggered()));
    connect(Act_Apar_Chg, SIGNAL(triggered()), this, SLOT(on_apar_chg_triggered()));
    connect(Act_Apar_Add, SIGNAL(triggered()), this, SLOT(on_apar_add_triggered()));
}

apartment1::~apartment1()
{
    delete ui;
}

void apartment1::contextMenuEvent(QContextMenuEvent *)
{
    //qDebug()<<ui->tabWidget->currentIndex();
    QCursor cur=this->cursor();
    QMenu *menu = new QMenu;
    if(ui->tabWidget->currentIndex() == 0)
    {
        menu->addAction(Act_Apar_Del);
        menu->addAction(Act_Apar_Chg);
        menu->addAction(Act_Apar_Add);
    }
    menu->exec(cur.pos());
    delete menu;
}

//============DisplayToTableWeight
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
        ui->tableWidget->setItem(rows, 0, new QTableWidgetItem(p->name));
        ui->tableWidget->setItem(rows, 1, new QTableWidgetItem(p->id));
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

//============Infos
void apartment1::on_apar_read_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "打开文件", ".", ("文本文件(*.txt)"));
    if(fileNames.size() == 0) return;
    for(int i = 0; i < fileNames.size(); ++i)
    {
        QByteArray bytearray = fileNames[i].toLocal8Bit();
        char *temp = bytearray.data();
        if(temp == NULL) continue;
        Apartment.read(temp);
    }
    char buffer[20];
    itoa(Apartment.count, buffer,10);
    char output[100];
    strcat(output, "导入完成，当前一共有");
    strcat(output, buffer);
    strcat(output, "个数据");
    QMessageBox::information(NULL, "导入完成", output, QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_save_triggered()
{
    QString fileName = "1.txt";
    if(fileName.length() == 0) return;
    QByteArray bytearray = fileName.toLocal8Bit();
    char *temp = bytearray.data();
    Apartment.save(temp);
    QMessageBox::information(NULL, "保存完成", "保存完成", QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_del_triggered()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    char temp[20] = {'\0'};
    QString text;
    if(!items.count() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(NULL, tr("删除公寓数据"), tr("请输入公寓信息"));
    }
    else
    {
        QTableWidgetItem *item=(ui->tabWidget->currentIndex() == 0)?items.at(1):items.at(0);
        text = item->text();
    }
    if(text.isEmpty())
        return;
    QByteArray bytearray = text.toLocal8Bit();
    bytearray = AnsiToUtf8(bytearray);
    strcpy(temp, bytearray.data());
    AparInfo *p = new AparInfo;
    p->next = NULL;
    strcpy(p->id, temp);
    if(Apartment.del(p, 1))
    {
        QMessageBox::information(NULL, "删除结果", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    }
    else
        QMessageBox::information(NULL, "删除结果", "删除失败-不存在此公寓", QMessageBox::Ok, QMessageBox::Ok);
    delete p;
    apartment1::display_apartment_info();
}

void apartment1::on_apar_add_triggered()
{
    QString text = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入公寓信息"));
    if(text.isEmpty())
        return;
    QByteArray bytearray = text.toLocal8Bit();
    bytearray = AnsiToUtf8(bytearray);
    char *aparid = bytearray.data();

    QString text2 = QInputDialog::getText(NULL, tr("添加公寓数据"), tr("请输入租金，地区，户型信息"));
    if(text2.isEmpty())
        return;
    QByteArray bytearray2 = text2.toLocal8Bit();
    bytearray2 = AnsiToUtf8(bytearray2);
    char *aparname = bytearray2.data();

    AparInfo *p = new AparInfo;
    p->next = NULL;
    strcpy(p->id, aparid);
    strcpy(p->name, aparname);

    if(Apartment.add(p))
        QMessageBox::information(NULL, "添加结果", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "添加结果", "添加失败-公寓重复", QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_chg_triggered()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    char aparid[20] = {'\0'};
    QString text;
    if(!items.count() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入公寓信息"));
    }
    else
    {
        QTableWidgetItem *item=(ui->tabWidget->currentIndex() == 0)?items.at(1):items.at(0);
        text = item->text();
    }
    if(text.isEmpty())
        return;
    QByteArray bytearray = text.toLocal8Bit();
    bytearray = AnsiToUtf8(bytearray);
    strcpy(aparid, bytearray.data());

    QString text2 = QInputDialog::getText(NULL, tr("修改公寓数据"), tr("请输入新信息（租金 地区 户型）"));
    if(text2.isEmpty())
        return;
    QByteArray bytearray2 = text2.toLocal8Bit();
    bytearray2 = AnsiToUtf8(bytearray2);
    char *aparnewname = bytearray2.data();
    AparInfo *p = new AparInfo;
    p->next = NULL;
    strcpy(p->id, aparid);
    strcpy(p->name, aparnewname);
    if(Apartment.chg(p, 0))
        QMessageBox::information(NULL, "修改结果", "修改成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "修改结果", "修改失败-公寓不存在", QMessageBox::Ok, QMessageBox::Ok);
    delete p;
    apartment1::display_apartment_info();
}
