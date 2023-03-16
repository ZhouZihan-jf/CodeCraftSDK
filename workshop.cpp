#include <iostream>
using namespace std;
#include "workshop.h"
workshop w[50];
int create_workshop(int k,char *line)
{
    int count = 1;
    const char *d = " ";
    const char *e = "\n";
    float tem;
    char *p,*q;
    q = strtok(line,e);
    p = strtok(q,d);
    while(p&&q)
    {
        printf("%s\n",p);
        stringstream get(p);
        get >> tem;
        if(count == 1)
            w[k].set_workid(tem);
        if(count == 2)
            w[k].set_locationx(tem);
        if(count == 3)
            w[k].set_locationy(tem);
        if(count == 4)
            w[k].set_left_time(tem);
        if(count == 5)
            w[k].set_material_state(tem);
        if(count == 6)
            w[k].set_product_state(tem);
        p = strtok(NULL,d);
        count++;
    }
   return 1;
}