#ifndef APARTMENT_H
#define APARTMENT_H

#define Apar_INFO_SIZE 20
struct AparInfo{
    char name[Apar_INFO_SIZE];
    char id[Apar_INFO_SIZE];
    AparInfo *next;
};

class apartment{
public:
    apartment();
    ~apartment();
    int count;
    AparInfo *head;
    bool read(const char *);
    bool save(const char *);
    AparInfo *serh(AparInfo *, int);
    bool add(AparInfo *);
    bool del(AparInfo *, bool);
    bool chg(AparInfo *, bool);
};

#endif // APARTMENT_H
