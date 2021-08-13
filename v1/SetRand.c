#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int setRand(int min, int max)
{
    int n=0;
    srand(time(NULL));
    n=(rand()%(max-min+1))+min;
    return n;
}
