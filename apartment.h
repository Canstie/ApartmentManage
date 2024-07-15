#ifndef APARTMENT_H
#define APARTMENT_H

struct AparInfo {
    char price[20];
    char location[50];
    char type[20];
    char name[100];
    AparInfo* next;
};

class apartment {
public:
    apartment();
    ~apartment();
    void read(const char *filename);
    void save(const char *filename);
    bool add(AparInfo *info);
    bool del(AparInfo *info, bool type);
    bool chg(AparInfo *info, bool type);
    AparInfo *serh(AparInfo *info, int type);
    AparInfo *head;
    int count;
};

#endif // APARTMENT_H
