#include <stdio.h>
#include <stdlib.h>

    typedef struct Joueur Joueur;
    struct Joueur
    {
        int id;
        int score;
    };

int testRecup (int ind, int *Tab, Joueur *player, int *TabTmp)
{

    int i=0, j=0, sum=0;
    player->score=0;
    for (i=0;i<12;i++)
        TabTmp[i]=Tab[i];


    if( (player->id == 2 && ind<=5))
    {

            for(j=ind; j<=5 && (Tab[j]==2 || Tab[j]==3); j++)
            {
                TabTmp[j]=0;
            }
            for(i=0;i<6;i++)
                sum+=TabTmp[i];
    }
        else
            if ((player->id == 1 && ind>=6))
            {
                for(j=ind; j>=6 && (Tab[j]==2 || Tab[j]==3); j--)
                {
                    TabTmp[j]=0;
                }
                for(i=6;i<12;i++)
                    sum+=TabTmp[i];
            }

    return sum;
}
