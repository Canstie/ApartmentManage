#include "ModifyLeaseDialog.h"

ModifyLeaseDialog::ModifyLeaseDialog(QWidget *parent) :
    QDialog(parent),
    locationEdit(new QLineEdit(this)),
    priceEdit(new QLineEdit(this)),
    statusEdit(new QLineEdit(this)),
    startDateEdit(new QDateEdit(this)),
    durationEdit(new QLineEdit(this)),
    endDateEdit(new QDateEdit(this)),
    okButton(new QPushButton("确定", this)),
    cancelButton(new QPushButton("取消", this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(locationEdit);
    layout->addWidget(priceEdit);
    layout->addWidget(statusEdit);
    layout->addWidget(startDateEdit);
    layout->addWidget(durationEdit);
    layout->addWidget(endDateEdit);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &ModifyLeaseDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &ModifyLeaseDialog::reject);

    setLayout(layout);
}

void ModifyLeaseDialog::setLeaseData(const QStringList &data)
{
    if (data.size() != 6) return;
    locationEdit->setText(data.at(0));
    priceEdit->setText(data.at(1));
    statusEdit->setText(data.at(2));
    startDateEdit->setDate(QDate::fromString(data.at(3), "yyyy-MM-dd"));
    durationEdit->setText(data.at(4));
    endDateEdit->setDate(QDate::fromString(data.at(5), "yyyy-MM-dd"));
}

QStringList ModifyLeaseDialog::getLeaseData() const
{
    return QStringList() << locationEdit->text()
                         << priceEdit->text()
                         << statusEdit->text()
                         << startDateEdit->date().toString("yyyy-MM-dd")
                         << durationEdit->text()
                         << endDateEdit->date().toString("yyyy-MM-dd");
}
