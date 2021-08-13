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

typedef struct Info Info;
struct Info
{
    int id;
    SDL_bool Fin;
    int idPlateau;
    int idCaillou;
};

typedef struct Button Button;
struct Button
{
    SDL_Rect rect;
};

int suivant(int i, int n, int p);
void changer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *texture1, int j, int k, Plateau *P, Caillou *C, int i);


Info choix(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Plateau *P, Caillou *C)
{
    SDL_Texture *fondText=NULL, *button=NULL, *T_btnNext=NULL, *T_btnBack=NULL, *tmp=NULL, *texture1=NULL;
    SDL_Surface *fond=NULL, *texte = NULL, *btnNext=NULL, *btnBack=NULL, *btnCommencer=NULL;
    SDL_Rect src={250,50,0,0};
    TTF_Font *police = NULL;
    SDL_Color marron={215,225,15}, blanc={255,255,255};
    int i=0, j=0, k=0;
    Button TabButton[5];
    Info informations;
    Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");

    //fond=IMG_Load("fond.PNG");

    fond = IMG_Load("fond.jpg");
    fondText=SDL_CreateTextureFromSurface(renderer, fond);
    SDL_FreeSurface(fond);

    police = TTF_OpenFont("NunitoExtraBold.ttf", 30);

    texte = TTF_RenderText_Blended(police, "Choix :", marron);

    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderCopy(renderer, fondText, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);

    src.x=106;
    src.y=26;
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);

    police = TTF_OpenFont("NunitoExtraBold.ttf", 20);

    texte = TTF_RenderText_Blended(police, "Plateau de jeu", blanc);
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

    src.x=86;
    src.y=72;
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);

    texte = TTF_RenderText_Blended(police, "Pion", blanc);
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);

    src.x=130;
    src.y=207;
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);

    //Boutton commencer
    src.x=80;
    src.y=346;
    btnCommencer = IMG_Load("bouttonCommencer.PNG");
    button = SDL_CreateTextureFromSurface(renderer, btnCommencer);
    SDL_FreeSurface(btnCommencer);
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_SetRenderTarget(renderer, texture);
    TabButton[4].rect=src;

    btnNext = IMG_Load("buttonNext.PNG");
    btnBack = IMG_Load("buttonBack.PNG");

    T_btnBack = SDL_CreateTextureFromSurface(renderer, btnBack);
    SDL_FreeSurface(btnBack);
    T_btnNext = SDL_CreateTextureFromSurface(renderer, btnNext);
    SDL_FreeSurface(btnNext);
    src.x=43;
    src.y=140;

    for(i=0; i<2; i++)
    {
        SDL_QueryTexture(T_btnBack, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(renderer, T_btnBack, NULL, &src);
        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, texture);
        TabButton[i].rect=src;
        src.y=278;
    }

    src.x=230;
    src.y=140;

    for(i=0; i<2; i++)
    {
        SDL_QueryTexture(T_btnNext, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(renderer, T_btnNext, NULL, &src);
        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_SetRenderTarget(renderer, texture);
        TabButton[i+2].rect=src;
        src.y=278;
    }

    src.x=100;
    src.y=122;
    SDL_SetRenderTarget(renderer, NULL);

    texture1=texture;
    tmp = SDL_CreateTextureFromSurface(renderer, P[j].SPImg);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_SetRenderTarget(renderer, texture1);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);

    src.x=107;
    src.y=261;
    tmp = SDL_CreateTextureFromSurface(renderer, C[k].SCImg);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);

    SDL_bool program_launch = SDL_TRUE;

    while(program_launch)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    informations.id=2;//On ne continue plus le jeu
                    SDL_Quit();
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    program_launch = SDL_FALSE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.clicks==1)
                    {

                        for(i=0; i<5; i++)
                        {
                            if((event.button.x>=TabButton[i].rect.x && event.button.x<=TabButton[i].rect.x+TabButton[i].rect.w) && (event.button.y>=TabButton[i].rect.y && event.button.y<=TabButton[i].rect.y+TabButton[i].rect.h))
                            {
                                Mix_PlayChannel(-1, clickEffect, 0);
                                switch(i)
                                {
                                    case 0:
                                        j=suivant(j,1,1);
                                        changer(renderer, texture, texture1, j, k, P, C, 1);
                                        break;
                                    case 1:
                                        k=suivant(k,1,1);
                                        changer(renderer, texture, texture1, j, k, P, C, 2);
                                        break;
                                    case 2:
                                        j=suivant(j,2,1);
                                        changer(renderer, texture, texture1, j, k, P, C, 1);
                                        break;
                                    case 3:
                                        k=suivant(k,2,1);
                                        changer(renderer, texture, texture1, j, k, P, C, 2);
                                        break;
                                    case 4:
                                        informations.id=1;
                                        program_launch = SDL_FALSE;
                                        break;
                                }
                            }
                        }
                    }
                    break;
            }
        }
    }

    informations.idCaillou=k;
    informations.idPlateau=j;

    SDL_DestroyTexture(fondText);
    SDL_DestroyTexture(button);
    SDL_DestroyTexture(T_btnBack);
    SDL_DestroyTexture(T_btnNext);
    SDL_DestroyTexture(tmp);
    SDL_DestroyTexture(texture1);

    return informations;

}
