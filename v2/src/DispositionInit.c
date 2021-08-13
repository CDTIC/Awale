
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


void dispositionInit(SDL_Renderer *renderer, SDL_Texture *texture, Case *T, SDL_Surface *pion)

{
    SDL_Texture *tmpPion=NULL;

    SDL_Rect pos= {0,0,20,20}, dist= {0,0,0,0};

    int i=0, j=0;

    pion = IMG_Load("caillouF.PNG");

    tmpPion = SDL_CreateTextureFromSurface(renderer, pion);
    if(tmpPion == NULL)
    {
        fprintf(stderr,"Erreur IMG_Load %s:",SDL_GetError());
    }
    SDL_SetRenderTarget(renderer, texture);
    for(i=11; i>=0; i--)
    {

        pos.y = T[i].y+25;
        for(j=0; j<4; j++)
        {
            switch(j)
            {
            case 0:
                pos.x=T[i].x+25;
                break;
            case 1:
                pos.x+=30;
                break;
            case 2:
                pos.x=T[i].x+25;
                pos.y=pos.y+30;
                break;
            case 3:
                pos.x+=30;
                break;
            }
            SDL_RenderCopy(renderer, tmpPion, NULL, &pos);
        }

    }

}
