#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

 typedef struct Joueur Joueur;
struct Joueur
{
    int id;
    int score;
};

void afficheInfo(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player)
{
    SDL_Surface *texte1=NULL, *texte2=NULL;
    SDL_Texture *texteTmp=NULL;
    TTF_Font *police = NULL;
    SDL_Color noir={0,0,0}, vert={24,248,64};
    SDL_Rect pos={420,10,0,0};

    police = TTF_OpenFont("NunitoExtraBold.ttf", 20);

    if(player.id==1)
    {
        texte1 = TTF_RenderText_Blended(police, "Joueur 1 :", vert);
        texte2 = TTF_RenderText_Blended(police, "Joueur 2 :", noir);
    }
    else
    {
        texte2 = TTF_RenderText_Blended(police, "Joueur 2 :", vert);
        texte1 = TTF_RenderText_Blended(police, "Joueur 1 :", noir);
    }

    texteTmp=SDL_CreateTextureFromSurface(renderer, texte1);

    SDL_QueryTexture(texteTmp, NULL, NULL, &pos.w, &pos.h);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_RenderPresent(renderer);

    pos.y = 470;

    texteTmp=SDL_CreateTextureFromSurface(renderer, texte2);

    SDL_QueryTexture(texteTmp, NULL, NULL, &pos.w, &pos.h);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_RenderPresent(renderer);


    SDL_FreeSurface(texte1);
    SDL_FreeSurface(texte2);
    SDL_DestroyTexture(texteTmp);
    TTF_CloseFont(police);
}
