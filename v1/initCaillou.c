#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct Caillou Caillou;
struct Caillou
{
    int id;
    SDL_Surface *SCImg;
    SDL_Surface *SC;
};

void InitCaillou(Caillou *C, int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        C[i].id=i+1;
    }
    C[0].SC=IMG_Load("c1.PNG");
    C[0].SCImg=IMG_Load("c1Img.PNG");

    C[1].SC=IMG_Load("c2.PNG");
    C[1].SCImg=IMG_Load("c2Img.PNG");
}
