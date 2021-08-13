#include <stdio.h>

void tabInit(int *Tab, int *Etat)
{
    int i=0;
    for(i=0; i<12; i++)
        {
            Tab[i]=4;
            Etat[i]=0;
        }
}
