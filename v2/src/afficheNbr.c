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


void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id)
{

    SDL_Surface *nbr=NULL, *backSur=NULL;
    SDL_Texture *tmp=NULL, *backText=NULL;
    TTF_Font *police = NULL;
    SDL_Color noir={0,0,0};
    SDL_Rect pos={0,0,0,0}, posBack={0,0,0,0};
    char chaine[3];

    police = TTF_OpenFont("NunitoExtraBold.ttf", 14);
    backSur=IMG_Load("back.PNG");
    backText=SDL_CreateTextureFromSurface(renderer, backSur);
    SDL_QueryTexture(backText, NULL, NULL, &posBack.w, &posBack.h);


    //for(i=0;i<12;i++)
    //{
    itoa(Tab[id],chaine,10);
    nbr = TTF_RenderText_Blended(police, chaine, noir);
    tmp=SDL_CreateTextureFromSurface(renderer, nbr);

    SDL_SetRenderTarget(renderer, NULL);

    posBack.x=T[id].x+37;
    posBack.y=T[id].y-25;
    if(T[id].ligne==1)
        posBack.y+=129;

    SDL_RenderCopy(renderer, backText, NULL, &posBack);
    SDL_RenderPresent(renderer);

    SDL_QueryTexture(tmp, NULL, NULL, &pos.w, &pos.h);
    pos.x=T[id].x+45;
    pos.y=T[id].y-24;
    if(T[id].ligne==1)
        pos.y+=129;
    SDL_RenderCopy(renderer, tmp, NULL, &pos);
    SDL_RenderPresent(renderer);
   // }

}

/*void affichePlateau(SDL_Renderer *renderer, int )
{

}*/
