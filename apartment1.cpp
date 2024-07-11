#include "apartment1.h"
#include "ui_apartment1.h"
#include <cstring>
#include <cstdio>
#include <QByteArray>
#include <QCursor>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QIODevice>
#include <QMenu>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTextCodec>
#include <QTextStream>
#include <QTabWidget>
#include "apartment.h"

apartment Apartment;

extern QByteArray AnsiToUtf8(QByteArray &ansi);

apartment1::apartment1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::apartment1)
{
    ui->setupUi(this);
    //Ԥ�ȶ�ȡ�ļ�
    Apartment.read("apar.txt");

    //���ڴ�С����
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    //�Ҽ��˵�����
    Act_Apar_Del = new QAction(tr("ɾ����Ԣ��Ϣ"), this);
    Act_Apar_Chg = new QAction(tr("�޸Ĺ�Ԣ��Ϣ"), this);
    Act_Apar_Add = new QAction(tr("��ӹ�Ԣ��Ϣ"), this);

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
}

//============Infos
void apartment1::on_apar_read_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "���ļ�", ".", ("�ı��ļ�(*.txt)"));
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
    strcat(output, "������ɣ���ǰһ����");
    strcat(output, buffer);
    strcat(output, "������");
    QMessageBox::information(NULL, "�������", output, QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_save_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "���Ϊ...", ".", ("�ı��ļ�(*.txt)"));
    if(fileName.length() == 0) return;
    QByteArray bytearray = fileName.toLocal8Bit();
    char *temp = bytearray.data();
    Apartment.save(temp);
    QMessageBox::information(NULL, "�������", "�������", QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_del_triggered()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    char temp[20] = {'\0'};
    QString text;
    if(!items.count() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(NULL, tr("ɾ����Ԣ����"), tr("�����빫Ԣ��Ϣ"));
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
        QMessageBox::information(NULL, "ɾ�����", "ɾ���ɹ�", QMessageBox::Ok, QMessageBox::Ok);
    }
    else
        QMessageBox::information(NULL, "ɾ�����", "ɾ��ʧ��-�����ڴ˹�Ԣ", QMessageBox::Ok, QMessageBox::Ok);
    delete p;
    apartment1::display_apartment_info();
}

void apartment1::on_apar_add_triggered()
{
    QString text = QInputDialog::getText(NULL, tr("��ӹ�Ԣ����"), tr("�����빫Ԣ��Ϣ"));
    if(text.isEmpty())
        return;
    QByteArray bytearray = text.toLocal8Bit();
    bytearray = AnsiToUtf8(bytearray);
    char *aparid = bytearray.data();

    QString text2 = QInputDialog::getText(NULL, tr("��ӹ�Ԣ����"), tr("�����������Ϣ"));
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
        QMessageBox::information(NULL, "��ӽ��", "��ӳɹ�", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "��ӽ��", "���ʧ��-��Ԣ�ظ�", QMessageBox::Ok, QMessageBox::Ok);
    apartment1::display_apartment_info();
}

void apartment1::on_apar_chg_triggered()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    char aparid[20] = {'\0'};
    QString text;
    if(!items.count() || ui->tabWidget->currentIndex() == 1)
    {
        text = QInputDialog::getText(NULL, tr("�޸Ĺ�Ԣ����"), tr("�����빫Ԣ��Ϣ"));
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

    QString text2 = QInputDialog::getText(NULL, tr("�޸Ĺ�Ԣ����"), tr("�������������Ϣ"));
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
        QMessageBox::information(NULL, "�޸Ľ��", "�޸ĳɹ�", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "�޸Ľ��", "�޸�ʧ��-��Ԣ������", QMessageBox::Ok, QMessageBox::Ok);
    delete p;
    apartment1::display_apartment_info();
}

