#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


 typedef struct Case Case;
    struct Case
    {
    int ligne;
    int colonne;
    int x;
    int y;
    };
    typedef struct Joueur Joueur;
    struct Joueur
    {
        int id;
        int score;
    };

void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);
void viderCase(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case T);

void recuperer(int ind, int *Tab, Joueur *player,SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case *T)
{

    int j=0;
    player->score=0;

    if((player->id == 1 && ind>=6) || (player->id == 2 && ind<=5))
    {

        if(ind<=5)
            for(j=ind; j<=5 && (Tab[j]==2 || Tab[j]==3); j++)
            {
                player->score+=Tab[j];
                Tab[j]=0;
                viderCase(renderer, texture, tmpTrou, T[j]);
                afficheNbr(renderer, texture, Tab, T, j);
                SDL_Delay(400);
            }
        else
            for(j=ind; j>=6 && (Tab[j]==2 || Tab[j]==3); j--)
            {
                player->score+=Tab[j];
                Tab[j]=0;
                viderCase(renderer, texture, tmpTrou, T[j]);
                afficheNbr(renderer, texture, Tab, T, j);
                SDL_Delay(400);
            }

    }

}
