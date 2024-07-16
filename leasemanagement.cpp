#include "LeaseManagement.h"
#include "ui_LeaseManagement.h"
#include "ModifyLeaseDialog.h"
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

LeaseManagement::LeaseManagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeaseManagement)
{
    ui->setupUi(this);

    // 创建主窗口布局
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 创建QTableWidget用于显示租赁记录
    tableWidget = new QTableWidget(centralWidget);
    tableWidget->setColumnCount(6); // 设置列数
    tableWidget->setHorizontalHeaderLabels(QStringList() << "位置" << "价格" << "租赁状态" << "起始日期" << "租赁总时长" << "结束日期"); // 设置列头
    tableWidget->horizontalHeader()->setStretchLastSection(true); // 拉伸最后一列以填充剩余空间
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 自适应列宽
    tableWidget->setAlternatingRowColors(true); // 交替行颜色
    tableWidget->setStyleSheet("QTableWidget {"
                               "    gridline-color: #d0d0d0;"
                               "    font-size: 12px;"
                               "}"
                               "QTableWidget::item {"
                               "    padding: 5px;"
                               "}"
                               "QHeaderView::section {"
                               "    background-color: #f0f0f0;"
                               "    padding: 4px;"
                               "    border: 1px solid #d0d0d0;"
                               "    font-size: 12px;"
                               "}");

    // 加载租赁记录
    loadLeases();

    // 创建按钮用于删除和修改租赁记录
    deleteButton = new QPushButton("删除", centralWidget);
    modifyButton = new QPushButton("修改", centralWidget);

    // 按钮样式
    deleteButton->setStyleSheet("QPushButton {"
                                "    background-color: #e74c3c;"
                                "    color: white;"
                                "    border: none;"
                                "    padding: 10px;"
                                "    font-size: 14px;"
                                "    border-radius: 5px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #c0392b;"
                                "}");
    modifyButton->setStyleSheet("QPushButton {"
                                "    background-color: #3498db;"
                                "    color: white;"
                                "    border: none;"
                                "    padding: 10px;"
                                "    font-size: 14px;"
                                "    border-radius: 5px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #2980b9;"
                                "}");

    // 连接按钮的点击信号到槽函数
    connect(deleteButton, &QPushButton::clicked, this, &LeaseManagement::deleteLease);
    connect(modifyButton, &QPushButton::clicked, this, &LeaseManagement::modifyLease);

    // 添加控件到布局
    layout->addWidget(tableWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(modifyButton);
    layout->addLayout(buttonLayout);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void LeaseManagement::loadLeases() {
    // 读取文件中的租赁记录
    QFile file("2.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int row = 0;
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            QStringList fields = line.split("\t");
            if (fields.size() == 6) {
                tableWidget->insertRow(row);
                for (int col = 0; col < fields.size(); ++col) {
                    tableWidget->setItem(row, col, new QTableWidgetItem(fields.at(col)));
                }
                ++row;
            }
        }
        file.close();
    }
}

void LeaseManagement::deleteLease() {
    // 删除选中的租赁记录
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow);
        // 更新文件
        QFile file("2.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int row = 0; row < tableWidget->rowCount(); ++row) {
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    out << tableWidget->item(row, col)->text();
                    if (col < tableWidget->columnCount() - 1) {
                        out << "\t";
                    }
                }
                out << "\n";
            }
            file.close();
        }
    } else {
        QMessageBox::warning(this, "删除", "请选择要删除的租赁记录.");
    }
}

void LeaseManagement::modifyLease() {
    // 修改选中的租赁记录的逻辑（可实现对话框让用户修改租赁信息）
    int currentRow = tableWidget->currentRow();
    if (currentRow >= 0) {
        QStringList currentData;
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            currentData << tableWidget->item(currentRow, col)->text();
        }

        ModifyLeaseDialog dialog(this);
        dialog.setLeaseData(currentData);
        if (dialog.exec() == QDialog::Accepted) {
            QStringList newData = dialog.getLeaseData();
            for (int col = 0; col < newData.size(); ++col) {
                tableWidget->setItem(currentRow, col, new QTableWidgetItem(newData.at(col)));
            }

            // 更新文件
            QFile file("2.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                for (int row = 0; row < tableWidget->rowCount(); ++row) {
                    for (int col = 0; col < tableWidget->columnCount(); ++col) {
                        out << tableWidget->item(row, col)->text();
                        if (col < tableWidget->columnCount() - 1) {
                            out << "\t";
                        }
                    }
                    out << "\n";
                }
                file.close();
            }
        }
    } else {
        QMessageBox::warning(this, "修改", "请选择要修改的租赁记录.");
    }
}

LeaseManagement::~LeaseManagement()
{
    delete ui;
}
