#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



    typedef struct Joueur Joueur;
    struct Joueur
    {
        int id;
        int score;
    };

int possible(int *Tab, Joueur *player, SDL_Renderer *renderer, SDL_Texture *texture, int *CaseDispo)
{
    int i=0, S=0, S1=0, S2=0, j=0, k=0, l=0, stop=3;

    SDL_Surface *surface=NULL;
    SDL_Texture *notification=NULL;
    SDL_Rect pos={0,0,0,0};

    for(i=0; i<12; i++)
    {
        S+=Tab[i];
        if(i<6)
            S1+=Tab[i];
        else
            S2+=Tab[i];
        if(Tab[i]==0)
            CaseDispo[i]=0;
        else
            CaseDispo[i]=1;
    }
    if (S<=5)
    {
        stop=2;
        goto Quit;
    }

    if(S1==0)
    {
        j=6;
        for(i=6; i<12; i++)
        {
            if(Tab[i]<j){
                CaseDispo[i]=0;
            }
            else
            {
                k++;
            }
            j--;
        }
    }

    if(S2==0)
    {
        j=1;
        for(i=0; i<6; i++)
        {
            if(Tab[i]<j){
                CaseDispo[i]=0;
            }
            else
            {
                l++;
            }
            j++;
        }
    }

    if(player->id==2 && S1==0)
    {
        if(k==0)
        {
            stop=1;
        }
        else
        {
            stop=0;
        }
        goto Quit;
    }
    if(player->id==1 && S2==0)
    {
        if(l==0)
        {
            stop=1;
        }
        else
        {
            stop=0;
        }
        goto Quit;
    }


    Quit:


    return stop;
}
