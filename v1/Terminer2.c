#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>



Info acceuil(Plateau *P, Caillou *C, int value)// value=menuValue=valeur retournée par la fonction menu//
{
    SDL_Window *window2 = NULL;
    SDL_Renderer *renderer2 =NULL;
    SDL_Texture *fond2=NULL, *tmp2=NULL;
    SDL_Surface *surface2=NULL, *texte2=NULL;
    SDL_Rect src2={0,0,0,0};
    TTF_Font *police2 = NULL;
    SDL_Color Blanc={255,255,255}, Vert={82,249,33};
    char chaine[3], txt[10];
    int i=0;

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
    window2 = SDL_CreateWindow("Fin",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,500,SDL_WINDOW_SHOWN);
    if(window2 == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateWindow :%s",SDL_GetError());
        goto Quit;
    }

    //creation du rendu
    renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED);
    if(renderer2 == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateRenderer :%s",SDL_GetError());
        goto Quit;
    }

    surface2=IMG_Load("fondGagner.PNG");

    tmp2 = SDL_CreateTextureFromSurface(renderer2, surface2);
    SDL_FreeSurface(surface2);
    if(tmp2 == NULL)
    {
        fprintf(stderr,"Erreur SDL_LoadBMP : %s",SDL_GetError());
        goto Quit;
    }

    fond2 = SDL_CreateTexture(renderer2, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);

    if(NULL == fond2)
    {
        fprintf(stderr,"Erreur SDL_CreateTexture : %s",SDL_GetError());
        goto Quit;
    }



    for(i=0; i<12; i++)
    {
        if(i<6)
            player[0].score+=Tab[i];
        else
            player[1].score+=Tab[i];
    }




    SDL_SetRenderTarget(renderer2, NULL);

    SDL_QueryTexture(fond2, NULL, NULL, &src2.w, &src2.h);
    SDL_RenderCopy(renderer2, fond2, NULL, &src2);
    SDL_RenderPresent(renderer2);

    police2 = TTF_OpenFont("NunitoExtraBold.ttf", 30);

    if(player[0].score > player[1].score)
        texte2 = TTF_RenderText_Blended(police2, "Joueur 1", Vert);
    else
        if(player[0].score < player[1].score)
            texte2 = TTF_RenderText_Blended(police2, "Joueur 2", Vert);
        else
            texte2 = TTF_RenderText_Blended(police2, "Match Nul!", Vert);
    src2.x=395;
    src2.y=169;
    tmp2 = SDL_CreateTextureFromSurface(renderer2, texte2);
    SDL_QueryTexture(tmp, NULL, NULL, &src2.w, &src2.h);
    SDL_RenderCopy(renderer2, tmp, NULL, &src2);
    SDL_RenderPresent(renderer2);
    src2.x=529;
    src2.y=284;
    itoa(player[0].score,chaine,10);
    texte2 = TTF_RenderText_Blended(police2, chaine, Blanc);
    tmp2 = SDL_CreateTextureFromSurface(renderer2, texte2);
    SDL_QueryTexture(tmp2, NULL, NULL, &src2.w, &src2.h);
    SDL_RenderCopy(renderer2, tmp2, NULL, &src2);
    SDL_RenderPresent(renderer2);

    src2.x=529;
    src2.y=344;
    itoa(player[1].score,chaine,10);
    texte2 = TTF_RenderText_Blended(policeé, chaine, Blanc);
    tmp2 = SDL_CreateTextureFromSurface(renderer2, texte2);
    SDL_QueryTexture(tmp2, NULL, NULL, &src2.w, &src2.h);
    SDL_RenderCopy(renderer2, tmp2, NULL, &src2);
    SDL_RenderPresent(renderer2);


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




}

    SDL_Window *window2 = NULL;
    SDL_Renderer *renderer2 =NULL;
    SDL_Texture *texture2=NULL, *tmp2=NULL, *button2=NULL;
    SDL_Surface *surface2=NULL, *texte2 = NULL, *buttonJouer2=NULL, *buttonQuit2=NULL;
    Info informations;

    Button TabButton[2];

    TTF_Font *police2 = NULL;

    SDL_Rect  src2={360,50,150,70};
    SDL_Color marron={215,225,15};

    int i=0;



    //surface = IMG_Load("plateauF.PNG");
    surface2 = IMG_Load("fond.jpg");
    buttonJouer2 = IMG_Load("buttonPlay.PNG");
    buttonQuit2 = IMG_Load("buttonQuit.PNG");





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
