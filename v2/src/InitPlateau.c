#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>

typedef struct Plateau Plateau;
struct Plateau
{
    int id;
    SDL_Surface *SPImg;
    SDL_Surface *SP;
    SDL_Surface *caseP1;
    SDL_Surface *caseP2;
};

void InitPlateau(Plateau *P, int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        P[i].id=i+1;
    }
    P[0].SP=IMG_Load("PfBoisClair.PNG");
    P[0].SPImg=IMG_Load("PfBoisClairIMG-2F.PNG");
    P[0].caseP1=IMG_Load("casePfBoisClair.PNG");
    P[0].caseP2=NULL;

    P[1].SP=IMG_Load("PfPlastiqueGris.PNG");
    P[1].SPImg=IMG_Load("PfPlastiqueGrisIMG-2f.PNG");
    P[1].caseP2=IMG_Load("caseOrangePfPlastiqueGris.PNG");
    P[1].caseP1=IMG_Load("caseVertPfPlastiqueGris.PNG");
}
