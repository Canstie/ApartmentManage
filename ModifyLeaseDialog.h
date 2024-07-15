#ifndef MODIFYLEASEDIALOG_H
#define MODIFYLEASEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ModifyLeaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyLeaseDialog(QWidget *parent = nullptr);
    void setLeaseData(const QStringList &data);
    QStringList getLeaseData() const;

private:
    QLineEdit *locationEdit;
    QLineEdit *priceEdit;
    QLineEdit *statusEdit;
    QDateEdit *startDateEdit;
    QLineEdit *durationEdit;
    QDateEdit *endDateEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // MODIFYLEASEDIALOG_H
