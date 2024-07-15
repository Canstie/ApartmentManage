#include "apartment.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

apartment::apartment() {
    count = 0;
    head = nullptr;
}

apartment::~apartment() {
    while (head != nullptr) {
        AparInfo* temp = head;
        head = head->next;
        delete temp;
    }
}

void apartment::read(const char *filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");
        if (fields.size() == 4) {
            AparInfo *newInfo = new AparInfo;
            strcpy(newInfo->price, fields[0].toUtf8().data());
            strcpy(newInfo->location, fields[1].toUtf8().data());
            strcpy(newInfo->type, fields[2].toUtf8().data());
            strcpy(newInfo->name, fields[3].toUtf8().data());
            newInfo->next = head;
            head = newInfo;
            count++;
        }
    }
    file.close();
}

void apartment::save(const char *filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    AparInfo *current = head;
    while (current != NULL) {
        out << current->price << " "
            << current->location << " "
            << current->type << " "
            << current->name << "\n";
        current = current->next;
    }
    file.close();
}

bool apartment::add(AparInfo *info) {
    if (serh(info, 0) != nullptr)
        return false;
    count += 1;
    info->next = head;
    head = info;
    return true;
}

bool apartment::del(AparInfo *info, bool type) {
    AparInfo *point;
    AparInfo *p = head;
    if ((point = serh(info, type)) == nullptr)
        return false;
    count -= 1;
    if (p == point) {
        head = head->next;
        delete point;
        return true;
    }
    while (p->next != nullptr) {
        if (p->next == point)
            break;
        else
            p = p->next;
    }
    p->next = p->next->next;
    delete point;
    return true;
}

bool apartment::chg(AparInfo *info, bool type) {
    AparInfo *point;
    if ((point = serh(info, 0)) == nullptr)
        return false;
    strcpy(point->price, info->price);
    strcpy(point->location, info->location);
    strcpy(point->type, info->type);
    return true;
}

AparInfo *apartment::serh(AparInfo *info, int type) {
    AparInfo *p = head;
    while (p != nullptr) {
        if (type == 0 && strcmp(info->name, p->name) == 0)
            return p;
        p = p->next;
    }
    return nullptr;
}
