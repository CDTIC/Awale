#include <stdio.h>
#include <stdlib.h>

 typedef struct Case Case;
    struct Case
    {
    int ligne;
    int colonne;
    int x;
    int y;
    };



void defCase(Case *T)
{
    int i=0, x=120, y=100, ligne=1, colonne=1;


    for(i=0; i<12; i++)
    {
        T[i].ligne = ligne;
        T[i].colonne = colonne;
        T[i].x = x;
        T[i].y = y;

        x+=120;
        colonne++;
        if(i==5)
        {
            ligne = 2;
            colonne = 1;
            x=120;
            y=300;
        }
    }
}
