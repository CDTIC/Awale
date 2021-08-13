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


int possible(int *Tab, Joueur player, SDL_Renderer *renderer, SDL_Texture *texture, int id);

int Fin(int *Tab, Joueur player, int id, SDL_Renderer *renderer, SDL_Texture *texture)
{
    int i=0, j=0, k=1, l=1, S=0, S1=0, S2=0, stop=0;
    int T[12], N[6];

    for(i=0; i<12; i++)
    {
        S+=Tab[i];
        if(i<6)
            S1+=Tab[i];
        else
            S2+=Tab[i];
    }

    if(S<=4)
        stop=1;
    else
        stop=possible(Tab, player, renderer, texture, id);

    return stop;
}
