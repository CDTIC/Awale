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

Info choix(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Plateau *P, Caillou *C);

Info acceuil(Plateau *P, Caillou *C, int value)// value=menuValue=valeur retournée par la fonction menu//
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer =NULL;
    SDL_Texture *texture=NULL, *tmp=NULL, *button=NULL;
    SDL_Surface *surface=NULL, *texte = NULL, *buttonJouer=NULL, *buttonQuit=NULL;
    Info informations;

    Button TabButton[2];

    TTF_Font *police = NULL;

    SDL_Rect  src={360,50,150,70};
    SDL_Color marron={215,225,15};

    int i=0;



    //surface = IMG_Load("plateauF.PNG");
    surface = IMG_Load("fond.jpg");
    buttonJouer = IMG_Load("buttonPlay.PNG");
    buttonQuit = IMG_Load("buttonQuit.PNG");

    //initialisation de TTF
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //initialisation de SDL
    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))//Si l'initialisation ne s'est pas bien passe
    {
        fprintf(stderr,"Erreur SDL_Init :%s",SDL_GetError());// Affichage de l'erreur
        goto Quit;
    }

    //Creation de la fenetre
    window = SDL_CreateWindow("Accueil",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,300,400,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateWindow :%s",SDL_GetError());
        goto Quit;
    }

    //creation du rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateRenderer :%s",SDL_GetError());
        goto Quit;
    }

    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
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

   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 0, 2048);

    Mix_Music *bSound = Mix_LoadMUS("Heart_of_Africa.mp3");
   /* Mix_Chunk *accSound = Mix_LoadWAV("580541__neopolitansixth__bad-cliche-hip-hop-loops.FLAC"); */
    Mix_PlayMusic(bSound, -1);
    Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");

    SDL_RenderCopy(renderer, tmp, NULL, NULL);
    SDL_RenderPresent(renderer);

    if(value==1)
        goto Suite;

    button = SDL_CreateTextureFromSurface(renderer, buttonJouer); //button 0 jouer
    SDL_FreeSurface(buttonJouer);
    src.x=75;
    src.y=180;
    TabButton[0].rect=src;
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);
    printf("Taille boutton accueil: width: %d, height: %d",src.w,src.h);

    button = SDL_CreateTextureFromSurface(renderer, buttonQuit); //button 1 quitter
    SDL_FreeSurface(buttonQuit);
    src.x=75;
    src.y=264;
    TabButton[1].rect=src;
    SDL_QueryTexture(button, NULL, NULL, &src.w, &src.h);
    SDL_RenderCopy(renderer, button, NULL, &src);
    SDL_RenderPresent(renderer);



    police = TTF_OpenFont("NunitoExtraBold.ttf", 40);

    src.h=0;
    src.w=0;
    texte = TTF_RenderText_Blended(police, "AWALE", marron);
    src.x=85;
    src.y=60;
    tmp = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    SDL_QueryTexture(tmp, NULL, NULL, &src.w, &src.h);

    SDL_RenderCopy(renderer, tmp, NULL, &src);
    SDL_RenderPresent(renderer);


   /* Mix_PlayChannel(-1, accSound, 0);*/

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
                        for(i=0; i<2; i++)
                        {
                            if((event.button.x>=TabButton[i].rect.x && event.button.x<=TabButton[i].rect.x+TabButton[i].rect.w) && (event.button.y>=TabButton[i].rect.y && event.button.y<=TabButton[i].rect.y+TabButton[i].rect.h))
                            {

                                Mix_PlayChannel(-1, clickEffect, 0);
                                if(i==0)
                                {
                                    Suite:
                                    informations =choix(window, renderer, texture, P, C);
                                    if(informations.id==1)
                                        goto Quit;
                                }
                                else
                                {
                                    goto Quit;
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

    Mix_FreeMusic(bSound);

    SDL_DestroyTexture(button);
    SDL_DestroyTexture(tmp);
    SDL_DestroyTexture(texture);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);

    TTF_CloseFont(police);
    Mix_CloseAudio();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    return informations;
}
