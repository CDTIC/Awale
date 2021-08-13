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
    int i=0, x=0, y=300, ligne=1, colonne=0;


    for(i=0; i<6; i++)
    {
        x+=120;
        colonne++;

        T[i].ligne = ligne ;
        T[i].colonne = colonne;
        T[i].x = x;
        T[i].y = y;
    }
    for(i=6; i<12; i++)
    {
        T[i].ligne = 2;
        T[i].colonne = colonne;
        T[i].x = x;
        T[i].y = y-200;

        x-=120;
        colonne--;
    }

}

