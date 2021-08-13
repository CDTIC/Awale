#include <stdio.h>

void definitionType()
{
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
}
