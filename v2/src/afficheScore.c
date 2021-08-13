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
    SDL_Rect pos={530,10,0,0};
    char chaine[3];

    police = TTF_OpenFont("NunitoExtraBold.ttf", 20);

    vide=IMG_Load("blanckBlanc.PNG");
    videText=SDL_CreateTextureFromSurface(renderer, vide);

    itoa(player.score,chaine,10);
    texte = TTF_RenderText_Blended(police, chaine, noir);

    texteTmp=SDL_CreateTextureFromSurface(renderer, texte);

    SDL_SetRenderTarget(renderer, NULL);

    if(player.id==1)
    {
        pos.y=470;
    }

    SDL_QueryTexture(videText, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, videText, NULL, &pos);
    SDL_RenderPresent(renderer);

    SDL_QueryTexture(texteTmp, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, texteTmp, NULL, &pos);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(texte);
    SDL_FreeSurface(vide);



}
