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

typedef struct Joueur Joueur;
struct Joueur
{
    int id;
    int score;
};

void defCase(Case *T);
void viderCase(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case T);
void dispositionInit(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int l);
void tabInit(int *Tab, int *Etat);

int setRand(int min, int max);
int mouvement(SDL_Renderer *renderer, SDL_Texture *texture,Case *T, int id, int *Tab, int *Etat);
void recuperer(int ind, int *Tab, int *Etat, Joueur *player,SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case *T);
void afficheInfo(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);
void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);
void afficheScore(SDL_Renderer *renderer, SDL_Texture *texture, Joueur player);




int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer =NULL;
    SDL_Texture *texture=NULL, *tmp=NULL, *tmpTrou=NULL;
    SDL_Surface *surface=NULL, *pion=NULL, *trou=NULL;


    TTF_Font *police = NULL;

    int state = EXIT_FAILURE;
    int i=0, ind=0, a=0;

    Case T[12]; // Declaration du tableau de cases//

    int Tab[12]; //Declaration du tableau contenant le nombre de cailloux par case//


    int Etat[12]; //Declaration du tableau d'état contenant le nombre de cailloux par case//


    tabInit(Tab,Etat); // Initialisation du tableau de case//

    defCase(T); // Definition des cases//

    police = TTF_OpenFont("NunitoExtraBold.ttf", 40);

    Joueur player[3];   //Definition desjoueurs: tableau de 2 joueurs (0 et 1) + un joueur switch//

    player[0].id=setRand(1,2);
    player[0].score=0;
    player[1].id=1;
    player[1].score=0;
    player[2].id=2;
    player[2].score=0;

    printf("Le joueur actuel est joueur %d\n",player[0].id);
    TTF_Init();
    //Verification de la position de la case sur la ligne//

    for(i=0; i<12; i++)
        printf("T[%d].x = %d\n",i+1,T[i].x);

    //chargement des images des différezntes structures //

    surface = IMG_Load("plateauF.PNG");
    pion = IMG_Load("caillouF.PNG");
    trou = IMG_Load("case.PNG");

    //initialisation de SDL_video (et vérification)//

    if(0 != SDL_Init(SDL_INIT_VIDEO))//Si l'initialisation ne s'est pas bien passe
    {
        fprintf(stderr,"Erreur SDL_INIT_VIDEO :%s",SDL_GetError());// Affichage de l'erreur
        goto Quit;
    }

    //Creation de la fenetre//

    window = SDL_CreateWindow("AWALE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,940,551,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateWindow :%s",SDL_GetError());
        goto Quit;
    }

    //creation du rendu et vérification//

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateRenderer : %s",SDL_GetError());
        goto Quit;
    }

    // Création d'une texture (temporaire) à partir de la surface ("PLATEAU")//
    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(tmp == NULL)
    {
        fprintf(stderr,"Erreur SDL_CreateTextureFromSurface : %s",SDL_GetError());
        goto Quit;
    }

    // création texture "texture" sur laquelle on va copie "tmp" afin de pouvoir y dessiner//

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    if(NULL == texture)
    {
        fprintf(stderr,"Erreur SDL_CreateTexture : %s",SDL_GetError());
        goto Quit;
    }

    // Creation d'une texture tmpTrou (Case vide) à partir de la surface trou (image "case")//

    tmpTrou = SDL_CreateTextureFromSurface(renderer, trou);
    if(tmpTrou == NULL)
    {
        fprintf(stderr,"Erreur SDL_LoadBMP :%s",SDL_GetError());
        goto Quit;
    }


    SDL_SetRenderTarget(renderer, texture); //la cible de notre rendu est maintenant la texture//

    SDL_RenderCopy(renderer, tmp, NULL, NULL); //copie de "tmp" sur "texture": on peut maintenant dessiner sur texture (Plateau initial)//

    SDL_FreeSurface(surface); //libération de l'espace mémoire occupée par "surface"//

    SDL_FreeSurface(pion); //libération de l'espace mémoire occupée par "pion"//

    SDL_FreeSurface(trou);
    //Initialisation du jeu//

    dispositionInit(renderer, texture, Tab, T, i); //Appel de la fonction dispositionInit chargée de disposer\
    4 pions dans chacune des 12 cases et d'afficher le Plateau initial//

    afficheInfo(renderer, texture, player[0]);

    for(i=0; i<12; i++)
        afficheNbr(renderer, texture, Tab, T, i);

    afficheScore(renderer, texture, player[1]);
    afficheScore(renderer, texture, player[2]);


    //deroulement du jeu//

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
                    for(i=0; i<12; i++)
                    {
                        if((event.button.x>=T[i].x && event.button.x<=T[i].x+100) && (event.button.y>=T[i].y && event.button.y<=T[i].y+100))
                        {

                            if(T[i].ligne == player[0].id && Tab[i]!=0)
                            {
                                a=player[0].id;
                                printf("%i",a);


                                do{

                                    viderCase(renderer, texture, tmpTrou, T[i]); // copie une case vide sur la case indiqué//

                                    ind=mouvement(renderer, texture, T, i, Tab, Etat); //deplacement des pions //

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
                                        if(player[0].id==2 && (player[0].score || (Tab[ind]==1 || Tab[ind]==0)))
                                            player[0].id = player[1].id;

                                    afficheInfo(renderer, texture, player[0]);
                                    i=ind;


                                    printf("Le joueur actuel est joueur %d\n",player[0].id);
                                 }while (a==player[0].id);

                            }//else on effectue un son
                        }
                    }


                }
                break;

            default:
                break;
            }
        }
    }


    state = EXIT_SUCCESS;
    //pause();

    Quit:  //Sortie de programme//
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);


    TTF_Quit();
    SDL_Quit();

    return state;

}


