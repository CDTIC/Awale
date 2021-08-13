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
void dispositionInit(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, SDL_Surface *pion);
void tabInit(int *Tab, int *Etat);

int setRand(int min, int max);
int mouvement(SDL_Renderer *renderer, SDL_Texture *texture, Case *T, int id, int *Tab, int *Etat, SDL_Surface *pion);
void recuperer(int ind, int *Tab, int *Etat, Joueur *player,SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case *T);
Info acceuil(Plateau *P, Caillou *C, int value);
void afficheInfo(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);
void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);
void afficheScore(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);

Info choix(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, Plateau *P, Caillou *C);
int suivant(int i, int n, int p);
void changer(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *texture1, int j, int k, Plateau *P, Caillou *C, int i);
int menu(SDL_Renderer *renderer, SDL_Texture *texture);


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
        SDL_Texture *texture=NULL, *tmp=NULL, *tmpTrou=NULL, *BouttonMenu=NULL;
        SDL_Surface *surface=NULL, *pion=NULL, *trou=NULL, *BtnMenu=NULL;
        SDL_Rect dist={0,0,0,0}, src={0,0,0,0};

        TTF_Font *police = NULL;
        Mix_Chunk *videEffect = Mix_LoadWAV("videSound.WAV");
        Mix_Chunk *clickEffect = Mix_LoadWAV("clickSound.WAV");

        int state = EXIT_FAILURE;

        int i=0, ind=0;

        // Declaration du tableau de cases//
        Case T[12];

        //Declaration du tableau contenant le nombre de cailloux par case//
        int Tab[12];
        int Etat[12]; //Declaration du tableau d'état contenant le nombre de cailloux par case//

        // Initialisation du tableau de case//
         tabInit(Tab,Etat); // Initialisation du tableau de case//


        // Definition des cases//
        defCase(T);

        police = TTF_OpenFont("NunitoExtraBold.ttf", 40);

        //Definition desjoueurs: tableau de 2 joueurs (0 et 1)+ un joueur switch//

        Joueur player[3];

        player[0].id=setRand(1,2);
        player[0].score=0;
        player[1].id=1;
        player[1].score=0;
        player[2].id=2;
        player[2].score=0;

        //chargement des images des différezntes structures //
        BtnMenu=IMG_Load("btnMenu.PNG");

        surface = P[informations.idPlateau].SP;
        //pion = IMG_Load("c1.PNG");
        pion = C[informations.idCaillou].SC;
        //trou = IMG_Load("casePfBoisClair.PNG");
        trou = P[informations.idPlateau].caseP1;

        TTF_Init(); //initialisation de SDL_ttf

        //initialisation de SDL_video et de l'audio (et vérification)//

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

        //SDL_FreeSurface(pion);libération de l'espace mémoire occupée par "pion"//

        SDL_SetRenderTarget(renderer, NULL);

        SDL_QueryTexture(texture, NULL, NULL, &dist.w, &dist.h);

        SDL_RenderCopy(renderer, texture, NULL, &dist);

        SDL_RenderPresent(renderer);

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
                        //Mix_PlayChannel(-1, moveEffect, 0);
                        //Mix_PlayMusic(bgSound, 0);
                        for(i=0; i<12; i++)
                        {
                            if((event.button.x>=T[i].x && event.button.x<=T[i].x+100) && (event.button.y>=T[i].y && event.button.y<=T[i].y+100))
                            {

                                if(T[i].ligne == player[0].id && Tab[i]!=0)
                                {
                                    if(informations.idPlateau == 1)
                                        {
                                            if(T[i].ligne==1)
                                                trou = P[1].caseP1;
                                            else
                                                trou = P[1].caseP2;
                                        }
                                        tmpTrou = SDL_CreateTextureFromSurface(renderer, trou);
                                    do{

                                        viderCase(renderer, texture, tmpTrou, T[i]); // copie une case vide sur la case indiqué//

                                        ind=mouvement(renderer, texture, T, i, Tab, Etat, pion); //deplacement des pions //

                                        // ind=actuCase(Tab,Etat,T, i); //recuperer l'indice de la case sur laquelle le dernier pion a été posé//

                                        recuperer(ind, Tab, Etat, player, renderer, texture, tmpTrou, T); //teste si la condition pour bouffer les pions est respectée\
                                        vide et actualise les cases concernées//
                                        afficheScore(renderer, texture, player[1]);
                                        afficheScore(renderer, texture, player[2]);

                                        SDL_Delay(2000);

                                        printf("score joueurswitch= %i\n", player[0].score);

                                        if(player[0].id==1 && (player[0].score || (Tab[ind]==1 || Tab[ind]==0)))
                                        {
                                        player[0].id = player[2].id;
                                        }

                                        else
                                            if (player[0].id==2 && (player[0].score || (Tab[ind]==1 || Tab[ind]==0)))
                                                player[0].id = player[1].id;


                                        afficheInfo(renderer, texture, player[0]);
                                        i=ind;


                                        printf("Le joueur actuel est joueur %d\n",player[0].id);
                                    }while (a==player[0].id);
                                }//else on effectue un son
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

