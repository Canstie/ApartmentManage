#ifndef INFORMATION_H
#define INFORMATION_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

namespace Ui {
class information;
}

class information : public QMainWindow
{
    Q_OBJECT

public:
    explicit information(const QString &filePath,QWidget *parent = nullptr);
    QString getfilepath(){return filepath;}
    ~information();

private slots:
    void on_pushButton_2_clicked();
private slots:
    void handleSaveChanges(); // Slot to handle saving changes

private:
    Ui::information *ui;
    QString filepath;
    void loadInformation(const QString &filePath);
};

#endif // INFORMATION_H
