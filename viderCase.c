#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


 typedef struct Case Case;
    struct Case
    {
    int ligne;
    int colonne;
    int x;
    int y;
    };

void viderCase(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case T)
{
    Mix_Chunk *videEffect = Mix_LoadWAV("videSound.WAV");

    SDL_Rect pos= {T.x,T.y,100,100};

    Mix_PlayChannel(0, videEffect, 0);

    SDL_SetRenderTarget(renderer, texture);

    SDL_QueryTexture(tmpTrou, NULL, NULL, &pos.w, &pos.h);

    SDL_RenderCopy(renderer, tmpTrou, NULL, &pos);

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderCopy(renderer, tmpTrou, NULL, &pos);

    SDL_RenderPresent(renderer);

    SDL_Delay(200);




}
