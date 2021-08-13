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


void Terminer(SDL_Renderer *renderer, SDL_Texture *texture, Joueur *player, int *Tab)
{
    SDL_Texture *fond=NULL, *tmp=NULL;
    SDL_Surface *surface=NULL, *texte=NULL;
    SDL_Rect src={0,0,0,0};
    TTF_Font *police = NULL;
    SDL_Color Blanc={255,255,255}, Vert={82,249,33};
    char chaine[3], txt[10];
    int i=0;

    for(i=0; i<12; i++)
    {
        if(i<6)
            player[0].score+=Tab[i];
        else
            player[1].score+=Tab[i];
    }

    surface=IMG_Load("fondGagner.PNG");
    fond=SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetRenderTarget(renderer, NULL);

    SDL_QueryTexture(fond, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, fond, NULL, &src);
    SDL_RenderPresent(renderer);

    police = TTF_OpenFont("NunitoExtraBold.ttf", 30);

    if(player[0].score > player[1].score)
        texte = TTF_RenderText_Blended(police, "Joueur 1", Vert);
    else
        if(player[0].score < player[1].score)
            texte = TTF_RenderText_Blended(police, "Joueur 2", Vert);
        else
            texte = TTF_RenderText_Blended(police, "Match Nul!", Vert);
    src.x=395;
    src.y=169;
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);
    src.x=529;
    src.y=284;
    itoa(player[0].score,chaine,10);
    texte = TTF_RenderText_Blended(police, chaine, Blanc);
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);

    src.x=529;
    src.y=344;
    itoa(player[1].score,chaine,10);
    texte = TTF_RenderText_Blended(police, chaine, Blanc);
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);


}
