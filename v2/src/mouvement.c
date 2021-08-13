#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>

 typedef struct Case Case;
    struct Case
    {
    int ligne;
    int colonne;
    int x;
    int y;
    };
int setRand(int min, int max);
void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);
void afficheInfo(SDL_Renderer *renderer, SDL_Texture *texture);


int mouvement(SDL_Renderer *renderer, SDL_Texture *texture, Case *T, int id, int *Tab,int *Etat, SDL_Surface *pion)
{
    SDL_Texture *tmpPion=NULL;
    SDL_Rect pos= {T[id].x-20,T[id].y+40,20,20},dist= {0,0,0,0};
    Mix_Chunk *moveEffect = Mix_LoadWAV("depPion.WAV");
    int i=0, k=id, p=0;

    tmpPion = SDL_CreateTextureFromSurface(renderer, pion);
    if(tmpPion == NULL)
    {
        fprintf(stderr,"Erreur SDL_LoadBMP : %s",SDL_GetError());
    }

    SDL_QueryTexture(texture, NULL, NULL, &dist.w, &dist.h);

    for(i=0;i<12;i++) //reinitialisation du Tableau d'état//
        {
            Etat[i]=0;
        }
    p=Tab[id];
    if(p!=0)
    {
        Tab[id]=0;
        afficheNbr(renderer, texture, Tab, T, id);
    }
    for(i=0; i<p; i++)
    {
            if(k==11)
            {
                k=0;
            }
            else
            {
                k++;
            }

        pos.x = setRand(T[k].x+15,T[k].x+70);
        pos.y = setRand(T[k].y+15, T[k].y+70);

        {
            Tab[k]++;
            Etat[k]++;
            Mix_PlayChannel(-1, moveEffect, 0);
            SDL_SetRenderTarget(renderer, texture);
            SDL_RenderCopy(renderer, tmpPion, NULL, &pos);
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, tmpPion, NULL, &pos);
            SDL_RenderPresent(renderer);
            afficheNbr(renderer, texture, Tab, T, k);
            SDL_Delay(400);
        }
    }

    SDL_DestroyTexture(tmpPion);
    Mix_FreeChunk(moveEffect);
    return k;
}
