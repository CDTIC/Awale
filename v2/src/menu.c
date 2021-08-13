#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



typedef struct Button Button;
struct Button
{
    SDL_Rect rect;
};



int menu(SDL_Renderer *renderer, SDL_Texture *texture1)
{
    SDL_Texture *texture=NULL, *tmp=NULL, *button=NULL;
    SDL_Surface *surface=NULL, *texte = NULL, *buttonContinuer=NULL, *buttonRecommencer=NULL, *buttonQuitter=NULL;
    Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");

    Button TabButton[3];

    TTF_Font *police = NULL;

    SDL_Rect  src={360,50,150,70};
    SDL_Color marron={255,255,255};

    int i=0, value=0;



    //surface = IMG_Load("plateauF.PNG");
    surface = IMG_Load("backMenu1.PNG");
    buttonContinuer = IMG_Load("btnPauseContinuer.PNG");
    buttonRecommencer = IMG_Load("btnPauseRecommencer.PNG");
    buttonQuitter = IMG_Load("btnPauseQuitter.PNG");

    //initialisation de TTF
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(tmp == NULL)
    {
        fprintf(stderr,"Erreur SDL_LoadBMP : %s",SDL_GetError());
        goto Quit;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 300, 400);

    if(NULL == texture)
    {
        fprintf(stderr,"Erreur SDL_CreateTexture : %s",SDL_GetError());
        goto Quit;
    }

    SDL_SetRenderTarget(renderer, texture);

    SDL_RenderCopy(renderer, tmp, NULL, NULL);
    SDL_RenderPresent(renderer);

    button = SDL_CreateTextureFromSurface(renderer, buttonContinuer);//button 0
    src.x=78;
    src.y=121;
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    TabButton[0].rect=src;
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);

    button = SDL_CreateTextureFromSurface(renderer, buttonRecommencer);//button 1
    src.x=78;
    src.y=205;
    TabButton[1].rect=src;
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    TabButton[1].rect=src;
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);

    button = SDL_CreateTextureFromSurface(renderer, buttonQuitter);//button 2
    src.x=78;
    src.y=289;
    TabButton[2].rect=src;
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    TabButton[2].rect=src;
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);

    for(i=0; i<3; i++)
    {
        TabButton[i].rect.x+=320;
        TabButton[i].rect.y+=91;
    }


    police = TTF_OpenFont("NunitoExtraBold.ttf", 30);

    texte = TTF_RenderText_Blended(police, "Pause", marron);
    src.x=106;
    src.y=27;
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);

    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);


    src.x=320;
    src.y=91;
    SDL_SetRenderTarget(renderer, NULL);
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, texture, NULL, &src);
    SDL_RenderPresent(renderer);
    //Mix_PlayMusic(bSound, -1);
    //Mix_PlayChannel(-1, moveEffect, -1);

    SDL_bool program_launch = SDL_TRUE;

    while(program_launch)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    program_launch = SDL_FALSE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.clicks==1)
                    {
                        for(i=0; i<3; i++)
                        {
                            if((event.button.x>=TabButton[i].rect.x && event.button.x<=TabButton[i].rect.x+TabButton[i].rect.w) && (event.button.y>=TabButton[i].rect.y && event.button.y<=TabButton[i].rect.y+TabButton[i].rect.h))
                            {
                                Mix_PlayChannel(-1, clickEffect, 0);
                                switch(i)
                                {
                                    case 0:
                                        SDL_SetRenderTarget(renderer, NULL);
                                        SDL_RenderCopy(renderer, texture1, NULL, NULL);
                                        SDL_RenderPresent(renderer);
                                        value=2;
                                        program_launch = SDL_FALSE;
                                        break;
                                    case 1:
                                        value=1;
                                        program_launch = SDL_FALSE;
                                        break;
                                    case 2:
                                        value=0;
                                        program_launch = SDL_FALSE;
                                        break;
                                }
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }

    Quit:
    //Mix_FreeMusic(bSound);

    TTF_CloseFont(police);
    TTF_Quit();
    return value;
}

