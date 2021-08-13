#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>


typedef struct Case Case;
struct Case
{
    int ligne;
    int colonne;
    int x;
    int y;
};

typedef struct Joueur Joueur;
struct Joueur
{
    int id;
    int score;
};

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

void defCase(Case *T);
void InitPlateau(Plateau *P, int n);
void InitCaillou(Caillou *C, int n);
void viderCase(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case T);
void dispositionInit(SDL_Renderer *renderer, SDL_Texture *texture, Case *T, SDL_Surface *pion);

void tabInit(int *Tab, int *CaseDispo, int *TabTmp);

int setRand(int min, int max);
int mouvement(SDL_Renderer *renderer, SDL_Texture *texture,Case *T, int id, int *Tab, SDL_Surface *pion);
int testRecup (int ind, int *Tab, Joueur *player, int *TabTmp);
void recuperer(int ind, int *Tab, Joueur *player,SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case *T);
Info acceuil(Plateau *P, Caillou *C, int value);
void afficheInfo(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);
void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);
void afficheScore(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);

Info choix(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Plateau *P, Caillou *C);
int suivant(int i, int n, int p);
void changer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *texture1, int j, int k, Plateau *P, Caillou *C, int i);
int menu(SDL_Renderer *renderer, SDL_Texture *texture);
int possible(int *Tab, Joueur *player, SDL_Renderer *renderer, SDL_Texture *texture, int *CaseDispo);


void Terminer(SDL_Renderer *renderer, SDL_Texture *texture, Joueur *player, int *Tab);

int main(int argc, char *argv[])
{
    Info informations;
    int state=0, menuValue=2;
    Plateau P[2];
    Caillou C[2];
    Debut:
    InitPlateau(P, 2);
    InitCaillou(C, 2);

    informations=acceuil(P, C, menuValue);
    if(informations.id==1)
    {
        SDL_Window *window = NULL;
        SDL_Renderer *renderer =NULL;
        SDL_Texture *texture=NULL, *tmp=NULL, *tmpTrou=NULL, *BouttonMenu=NULL, *notification=NULL;
        SDL_Surface *surface=NULL, *pion=NULL, *trou=NULL, *BtnMenu=NULL, *notif=NULL;
        SDL_Rect dist={0,0,0,0}, src={0,0,0,0}, pos={0,0,0,0};

        TTF_Font *police = NULL;
        Mix_Chunk *videEffect = Mix_LoadWAV("videSound.WAV");
        Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");

        int state = EXIT_FAILURE;

        int i=0, ind=0, stop=0;

        // Declaration du tableau de cases//
        Case T[12];
        int CaseDispo[12];

        //Declaration du tableau contenant le nombre de cailloux par case//
        int Tab[12];
        int TabTmp[12];

        // Initialisation du tableau de case//
        tabInit(Tab, CaseDispo, TabTmp);

        // Definition des cases//
        defCase(T);

        police = TTF_OpenFont("NunitoExtraBold.ttf", 40);

        //Definition desjoueurs: tableau de 2 joueurs (0 et 1)+ un joueur switch//

        Joueur player[3];
        player[0].id=1;
        player[0].score=0;
        player[1].id=2;
        player[1].score=0;
        player[2].id=setRand(1,2);
        player[2].score=0;

        //chargement des images des différezntes structures //
        BtnMenu=IMG_Load("btnMenu.PNG");

        surface = P[informations.idPlateau].SP;
        //pion = IMG_Load("c1.PNG");
        pion = C[informations.idCaillou].SC;
        //trou = IMG_Load("casePfBoisClair.PNG");
        trou = P[informations.idPlateau].caseP1;

        TTF_Init();
        //initialisation de SDL_video (et vérification)//

        if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))//Si l'initialisation ne s'est pas bien passe
        {
            fprintf(stderr,"Erreur SDL_Init :%s",SDL_GetError());// Affichage de l'erreur
            goto Quit;
        }

        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

        Mix_Music *bgSound = Mix_LoadMUS("580507__erokia__ub-e-24-7-drums-piano-synths-100-bpm.FLAC");

        //Creation de la fenetre
        window = SDL_CreateWindow("Awale",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,940,551,SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            fprintf(stderr,"Erreur SDL_CreateWindow :%s",SDL_GetError());
            goto Quit;
        }

        //creation du rendu
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL)
        {
            fprintf(stderr,"Erreur SDL_CreateRenderer : %s",SDL_GetError());
            goto Quit;
        }

        tmp = SDL_CreateTextureFromSurface(renderer, surface);
        if(tmp == NULL)
        {
            fprintf(stderr,"Erreur SDL_LoadBMP : %s",SDL_GetError());
            goto Quit;
        }



        tmpTrou = SDL_CreateTextureFromSurface(renderer, trou);
        if(tmpTrou == NULL)
        {
            fprintf(stderr,"Erreur SDL_LoadBMP :%s",SDL_GetError());
            goto Quit;
        }

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);


        if(NULL == texture)
        {
            fprintf(stderr,"Erreur SDL_CreateTexture : %s",SDL_GetError());
            goto Quit;
        }

       // texte = TTF_RenderText_Blended(police, "Joueur 1", marron);


        SDL_SetRenderTarget(renderer, texture);

        SDL_RenderCopy(renderer, tmp, NULL, NULL);

        SDL_FreeSurface(surface); //libération de l'espace mémoire occupée par "surface"//

        printf("idCaillou : %d\n",informations.idCaillou);

        dispositionInit(renderer, texture, T, pion);

        SDL_SetRenderTarget(renderer, NULL);

        SDL_QueryTexture(texture, NULL, NULL, &dist.w, &dist.h);

        SDL_RenderCopy(renderer, texture, NULL, &dist);

        SDL_RenderPresent(renderer);


        //SDL_FreeSurface(pion);libération de l'espace mémoire occupée par "pion"//



        src.x=814;
        src.y=497;
        BouttonMenu = SDL_CreateTextureFromSurface(renderer, BtnMenu);
        SDL_FreeSurface(BtnMenu);

        SDL_SetRenderTarget(renderer, texture);
        SDL_QueryTexture(BouttonMenu, NULL, NULL, &src.w, &src.h);
        SDL_RenderCopy(renderer, BouttonMenu, NULL, &src);

        SDL_SetRenderTarget(renderer, NULL);
        SDL_QueryTexture(texture, NULL, NULL, &dist.w, &dist.h);
        SDL_RenderCopy(renderer, texture, NULL, &dist);

        SDL_RenderPresent(renderer);

        afficheInfo(renderer, texture, player[2]);

        for(i=0; i<12; i++)
            afficheNbr(renderer, texture, Tab, T, i);

        afficheScore(renderer, texture, player[0]);
        afficheScore(renderer, texture, player[1]);

        Mix_PlayMusic(bgSound, -1);

        SDL_bool program_launch = SDL_TRUE;

        while(program_launch)
        {
            SDL_Event event;

            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_QUIT:
                    menuValue=3;
                    program_launch = SDL_FALSE;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button==SDL_BUTTON_LEFT && event.button.clicks==1)
                    {

                        for(i=0; i<12; i++)
                        {
                            if((event.button.x>=T[i].x && event.button.x<=T[i].x+100) && (event.button.y>=T[i].y && event.button.y<=T[i].y+100))
                            {

                                if(T[i].ligne == player[2].id && Tab[i])
                                {
                                    if (CaseDispo[i])
                                    {

                                        if(informations.idPlateau == 1)
                                        {
                                            if(T[i].ligne==1)
                                                trou = P[1].caseP1;
                                            else
                                                trou = P[1].caseP2;
                                        }
                                        tmpTrou = SDL_CreateTextureFromSurface(renderer, trou);

                                        viderCase(renderer, texture, tmpTrou, T[i]);
                                        ind=mouvement(renderer, texture, T, i, Tab, pion);

                                        if(testRecup(ind, Tab, &player[2], TabTmp)!= 0)
                                        {
                                            recuperer(ind, Tab, &player[2], renderer, texture, tmpTrou, T);
                                        }
                                        printf("id joueur: %i\n",player[2].id);
                                        printf("score sup joueur: %i\n\n",player[2].score);


                                        if(player[2].id==1)
                                        {
                                            player[0].score+=player[2].score;
                                            afficheScore(renderer, texture, player[0]);
                                            printf("score joueur 1 = %i\n\n",player[0].score);
                                            player[2].id = player[1].id;
                                        }
                                        else
                                        {
                                            player[1].score+=player[2].score;
                                            afficheScore(renderer, texture, player[1]);
                                            printf("score joueur 2 = %i\n\n", player[1].score);
                                            player[2].id = player[0].id;
                                        }
                                        afficheInfo(renderer, texture, player[2]);


                                        stop=possible(Tab, &player[2], renderer, texture, CaseDispo);

                                        if (stop!=3 && stop)
                                            Terminer(renderer, texture, player,Tab);



                                    }
                                    else
                                    {
                                        SDL_SetRenderTarget(renderer,NULL);
                                        notif=IMG_Load("Notification.PNG");
                                        notification=SDL_CreateTextureFromSurface(renderer, notif);
                                        SDL_FreeSurface(notif);
                                        pos.x=311;
                                        pos.y=38;
                                        SDL_QueryTexture(notification, NULL, NULL, &pos.w, &pos.h);
                                        SDL_RenderCopy(renderer, notification, NULL, &pos);
                                        SDL_RenderPresent(renderer);
                                        SDL_Delay(1400);
                                        SDL_SetRenderTarget(renderer,NULL);
                                        SDL_RenderCopy(renderer, texture, NULL, NULL);
                                        SDL_RenderPresent(renderer);
                                    }
                                }
                            }
                        }
                        if((event.button.x>=814 && event.button.x<=814+src.w) && (event.button.y>=497 && event.button.y<=497+src.h))
                        {
                            Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");
                            Mix_PlayChannel(-1, clickEffect, 0);
                            menuValue=menu(renderer, texture);
                            if (menuValue!=2)
                                goto Quit;
                        }
                    }
                    break;

                default:
                    break;
                }
            }
        }






        state = EXIT_SUCCESS;

    Quit:
        Mix_FreeMusic(bgSound);
        Mix_FreeChunk(videEffect);
        Mix_FreeChunk (clickEffect);

        SDL_FreeSurface(pion);
        SDL_FreeSurface(trou);

        SDL_DestroyTexture(BouttonMenu);
        SDL_DestroyTexture(tmp);
        SDL_DestroyTexture(tmpTrou);
        SDL_DestroyTexture(texture);




        if(renderer != NULL)
            SDL_DestroyRenderer(renderer);
        if(window != NULL)
            SDL_DestroyWindow(window);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();

        if (menuValue!=3)
            goto Debut;

    }
    return state;

}
