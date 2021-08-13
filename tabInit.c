#include <stdio.h>

void tabInit(int *Tab, int *CaseDispo, int *TabTmp)
{
    int i=0;
    for(i=0; i<12; i++)
    {
        Tab[i]=4;
        CaseDispo[i]=1;
        TabTmp[i]=0;
    }
}
