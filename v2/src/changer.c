#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

typedef struct Plateau Plateau;
struct Plateau
{
    int id;
    SDL_Surface *SPImg;
    SDL_Surface *SP;
    SDL_Surface *caseP1;
    SDL_Surface *caseP2;
};

typedef struct Caillou Caillou;
struct Caillou
{
    int id;
    SDL_Surface *SCImg;
    SDL_Surface *SC;
};




void changer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *texture1, int j, int k, Plateau *P, Caillou *C, int i)
{
    SDL_Rect src={100,122,0,0}, pos={110,261,0,0};
    SDL_Texture *tmp1=NULL, *tmp2=NULL;

    tmp1 = SDL_CreateTextureFromSurface(renderer, P[j].SPImg);
    tmp2 = SDL_CreateTextureFromSurface(renderer, C[k].SCImg);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    if(i==1){
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture1, NULL, &src);
        SDL_QueryTexture(tmp2, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer, tmp2, NULL, &pos);

        SDL_QueryTexture(tmp1, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(renderer, tmp1, NULL, &src);
        SDL_RenderPresent(renderer);
    }
    else{
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture1, NULL, NULL);
        SDL_QueryTexture(tmp1, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(renderer, tmp1, NULL, &src);

        SDL_QueryTexture(tmp2, NULL, NULL, &pos.w, &pos.h);
        SDL_RenderCopy(renderer, tmp2, NULL, &pos);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(tmp1);
    SDL_DestroyTexture(tmp2);
}

