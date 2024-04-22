#ifndef TICTAC_H
#define TICTAC_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    SDL_Surface  * back, * xx , * o ;
    int tabsuivi[9];
    SDL_Rect pos;
    int joueur ; 
    int tour; 
    SDL_Surface *t;
    TTF_Font * font ; 
    SDL_Color color ; 
    char texte[50]; 
    SDL_Rect pos_text ; 
    


} tic ; 

void initialiserTic(tic * t );
void afficherTic(tic t,SDL_Surface * screen);
int atilgagner(int tabsuivi[]);
void Resultat(tic *t, SDL_Surface *screen);
void liberer(tic t);
int minmax(int tabsuivi[],int joueur);
void calcul_coup(int tabsuivi[]);
void choisirXO(SDL_Surface *screen, SDL_Surface **xx, SDL_Surface **o, SDL_Surface **texte, TTF_Font *police, SDL_Color couleur, SDL_Surface **Joueur, SDL_Surface **Ordinateur);


#endif // TICTAC_H

