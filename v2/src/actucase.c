#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

 typedef struct Case Case;
    struct Case
    {
    int ligne;
    int colonne;
    int x;
    int y;
    };


int actuCase(int *Tab, int *Etat, Case *T, int j)
{
    int i=0, p=0;

    for(i=0;i<12;i++) //reinitialisation du Tableau d'état//
        {
            Etat[i]=0;
        }


    i=j;

    p=Tab[i];
    if(p!=0)
        Tab[i]=0;
    while(p!=0)
    {

            if(i==11)
            {
                i=0;
            }
            else
            {
                i++;
            }
            if (i!=j)
            {
                Tab[i]++;
                Etat[i]++;
                p--;
            }

    }

    for(j=0; j<12; j++)
        printf("Case Ligne: %d\tColonne: %d\tValeur: %d\n",T[j].ligne,T[j].colonne,Tab[j]);

    return i;


}
