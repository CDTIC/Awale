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


int actuCase(int *Tab, Case *T, int j)
{
    int i=j, p=0;


    p=Tab[i];
    if(p!=0)
        Tab[i]=0;
    while(p!=0)
    {

            if(i>=0 && i<=5)
            {
            if(i==0)
                i=6;
            else
                i--;
            }
            else if(i>=6 && i<=11)
            {
            if(i==11)
                i=5;
            else
                i++;
            }
            if (i!=j)
            {
                Tab[i]++;
                p--;
            }



    }
    for(j=0; j<12; j++)
        printf("Case Ligne: %d\tColonne: %d\tValeur: %d\n",T[j].ligne,T[j].colonne,Tab[j]);
    return i;


}
