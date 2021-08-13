#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


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

void afficheNbr(SDL_Renderer *renderer, SDL_Texture *texture, int *Tab, Case *T, int id);

void viderCase(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case T);

void recuperer(int ind, int *Tab,int *Etat, Joueur *player,SDL_Renderer *renderer, SDL_Texture *texture, SDL_Texture *tmpTrou, Case *T)
{

    int i=0;
    player[0].score=0;


    if (Tab[ind]==4)
        {
            player[player[0].id].score+=4;
            printf("Score Joueur %d : %d\n",player[player[0].id].id,player[player[0].id].score);
            Tab[ind]=0;
            viderCase(renderer, texture,tmpTrou, T[ind]);
            afficheNbr(renderer, texture, Tab, T, ind);
            SDL_Delay(1000);
        }
    for(i=0;i<12;i++)

        if ((player[0].id != T[i].ligne) && Tab[i]==4 && Etat[i]>0)
           {
                player[T[i].ligne].score+=4;
                printf("Score Joueur %d : %d\n",player[T[i].ligne].id,player[T[i].ligne].score);
                Tab[i]=0;
                viderCase(renderer, texture, tmpTrou, T[i]);
                afficheNbr(renderer, texture, Tab, T, i);
                SDL_Delay(1000);
           }

}
