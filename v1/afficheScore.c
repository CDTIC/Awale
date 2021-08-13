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


void afficheScore(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player)
{
    SDL_Surface *texte=NULL, *vide=NULL;
    SDL_Texture *texteTmp=NULL, *videText=NULL;
    TTF_Font *police = NULL;
    SDL_Color noir={0,0,0};
    SDL_Rect pos={520,10,0,0};
    char chaine[3];

    police = TTF_OpenFont("NunitoExtraBold.ttf", 20);

    vide=IMG_Load("blanckBlanc.PNG");
    videText=SDL_CreateTextureFromSurface(renderer, vide);
    SDL_FreeSurface(vide);

    itoa(player.score,chaine,10);
    texte = TTF_RenderText_Blended(police, chaine, noir);

    texteTmp=SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

    if(player.id==2)
    {
        pos.y=470;
    }

    SDL_QueryTexture(videText, NULL, NULL, &pos.w, &pos.h);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, videText, NULL, &pos);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, videText, NULL, &pos);
    SDL_RenderPresent(renderer);

    pos.x=530;
    SDL_QueryTexture(texteTmp, NULL, NULL, &pos.w, &pos.h);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_RenderPresent(renderer);


    SDL_DestroyTexture(texteTmp);
    SDL_DestroyTexture(videText);
    TTF_CloseFont(police);

}
