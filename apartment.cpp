#include "apartment.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
apartment::apartment()
{
    apartment::count = 0;
    apartment::head = NULL;
}

apartment::~apartment()
{

}

bool apartment::read(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
        return 0;
    char ch;
    int i = 0;
    bool mode = 0;
    AparInfo *p = new AparInfo;
    p->next = NULL;
    while((ch = fgetc(fp)) != EOF)
    {
        if(mode == 0 && ch != ' ' && ch != '\n')
            p->name[i++]=ch;
        else if(mode == 1 && ch != ' ' && ch != '\n')
            p->id[i++] = ch;
        else if(ch == '\n')
        {
            p->id[i] = '\0';
            i = 0;
            mode = 0;
            AparInfo *point;
            if((point = apartment::serh(p, 1)) != NULL)
            {
                strcpy(point->name, p->name);
            }
            else
            {
                if(apartment::head != NULL)
                    p->next = apartment::head;
                apartment::head = p;
                ++apartment::count;
            }
            p = new AparInfo;
            p->next = NULL;
        }
        else if(ch == ' ')
        {
            p->name[i] = '\0';
            i = 0;
            mode = 1;
        }
    }
    fclose(fp);
    return 1;
}

bool apartment::save(const char *filename)
{
    AparInfo *p = apartment::head;
    FILE *fp = fopen(filename, "w");
    while(p != NULL)
    {
        fprintf(fp, p->name);
        fprintf(fp, " ");
        fprintf(fp, p->id);
        fprintf(fp, "\n");
        p = p->next;
    }
    fclose(fp);
    return 1;
}

bool apartment::add(AparInfo *info)
{
    if(!(apartment::serh(info, 1) == NULL))
        return 0;
    apartment::count += 1;
    info->next = apartment::head;
    apartment::head = info;
    return 1;
}

bool apartment::del(AparInfo *info, bool type)
{
    AparInfo *point;
    AparInfo *p = apartment::head;
    if((point = apartment::serh(info, type)) == NULL)
        return 0;
    apartment::count -= 1;
    if(p == point)
    {
        apartment::head = apartment::head->next;
        return 1;
    }
    while(p->next != NULL)
        if(p->next == point)
            break;
        else
            p = p->next;
    p->next = p->next->next;
    return 1;
}

bool apartment::chg(AparInfo *info, bool type)
{
    AparInfo *point;
    if((point = apartment::serh(info, 1)) == NULL)
        return 0;
    if(type == 0)
        strcpy(point->name, info->name);
    else if(type == 1)
        strcpy(point->id, info->id);
    return 1;
}

AparInfo *apartment::serh(AparInfo *info, int type)
{
    AparInfo *p = apartment::head;
    while(p != NULL)
    {
        if(type == 0 && strcmp(info->name, p->name) == 0)
            return p;
        else if(type == 1 && strcmp(info->id, p->id) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}
