#include "tictac.h"



/////////////////////////////////////initialisation//////////////////////////////////////

void initialiserTic(tic *t)
{

    t->back = IMG_Load("back.png");
    t->xx = IMG_Load("xx.png");
    t->o = IMG_Load("o.png");
    for (int i = 0; i < 9; i++)
    {
        t->tabsuivi[i] = 0;
    }

    t->pos.x = 0;
    t->pos.y = 0;
    t->pos.w = 300;
    t->pos.h = 300;

    t->joueur = 1;
    t->tour = 0;

    t->font = TTF_OpenFont("Pixeboy.ttf", 40);

    t->color.r = 255;
    t->color.g = 255;
    t->color.b = 255;

    t->pos_text.x = 500;
    t->pos_text.y = 20;
    
    SDL_WM_SetCaption("Tic-Tac-Toe",NULL); 
    SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL); 
}




////////////////////////////////affichage/////////////////////////////////////////////

void afficherTic(tic t, SDL_Surface *screen)
{
    SDL_BlitSurface(t.back, NULL, screen, NULL);
    for (int i = 0; i < 9; i++)
    {
        t.pos.x = (t.pos.w ) * (i % 3) ;
        t.pos.y = (t.pos.h ) * (i / 3) ;
        if (t.tabsuivi[i] == 1)
            SDL_BlitSurface(t.o, NULL, screen, &t.pos);
        if (t.tabsuivi[i] == -1)
            SDL_BlitSurface(t.xx, NULL, screen, &t.pos);
    }
}







////////////////////////////////////alignement////////////////////////////////////////

int atilgagner(int tabsuivi[])
{
    int lignes_gagnates[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
    {
        if (tabsuivi[lignes_gagnates[i][0]] == tabsuivi[lignes_gagnates[i][1]])
        {
            if (tabsuivi[lignes_gagnates[i][0]]== tabsuivi[lignes_gagnates[i][2]]) 
            return tabsuivi[lignes_gagnates[i][0]];
        }
            
    }
    return 0;
}








////////////////////////////////////resultats/////////////////////////////////////

void Resultat(tic *t, SDL_Surface *screen)
{


    int resultat;
    resultat = atilgagner(t->tabsuivi);
    if (resultat == 1)
    {
      
        strcpy(t->texte, "Victoire");
        t->t = TTF_RenderText_Blended(t->font, t->texte, t->color);
        SDL_BlitSurface(t->t, NULL, screen, &t->pos_text);
    }
    if (resultat == -1)
    {
        
        strcpy(t->texte, "Defaite");
        t->t = TTF_RenderText_Blended(t->font, t->texte, t->color);
        SDL_BlitSurface(t->t, NULL, screen, &t->pos_text);
    }
    if (resultat == 0)
    {
        strcpy(t->texte, "Nul");
        t->t = TTF_RenderText_Blended(t->font, t->texte, t->color);
        SDL_BlitSurface(t->t, NULL, screen, &t->pos_text);
    }
}







////////////////////////////////////liberation////////////////////////
void liberer(tic t)
{
    SDL_FreeSurface(t.back);
    SDL_FreeSurface(t.xx);
    SDL_FreeSurface(t.o);
    TTF_CloseFont(t.font);
    TTF_Quit();
    SDL_Quit();
}







//////////////////////////////minmax/////////////////////////////

int minmax(int tabsuivi[], int joueur)
{
    int gagnant = atilgagner(tabsuivi);
    if (gagnant != 0)
        return gagnant * joueur;
    int coup = -1;
    int score = 2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = joueur;
            int mmscore = -minmax(tabsuivi, joueur * -1);
            if (mmscore > score)
            {
                score = mmscore;
                coup = 1;
            }
            tabsuivi[i] = 0;
        }
    }
    if (coup == -1)
        return 0;
    return score;
}









////////////////////////////calculer coup////////////////////////////////

void calcul_coup(int tabsuivi[])
{
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = 1;
            int mmscore = -minmax(tabsuivi, -1);
            tabsuivi[i] = 0;
            if (mmscore > score)
            {
                score = mmscore;
                coup = i;
            }
        }
    }
    tabsuivi[coup] = -1;
}





void choisirXO(SDL_Surface *screen, SDL_Surface **xx, SDL_Surface **o, SDL_Surface **texte, TTF_Font *police, SDL_Color couleur, SDL_Surface **Joueur, SDL_Surface **Ordinateur) {
    SDL_Event event;
    SDL_Rect position;

    // Rendu des textes "X" et "O"
    *xx = TTF_RenderText_Blended(police, "X", couleur);
    *o = TTF_RenderText_Blended(police, "O", couleur);
    *texte = TTF_RenderText_Blended(police, " X/O ? ", couleur);

    position.x = (screen->w / 2) - ((*texte)->w / 2);
    position.y = (screen->h / 2) - ((*texte)->h / 2);

    // Affichage du texte au centre de l'écran
    SDL_BlitSurface(*texte, NULL, screen, &position);
    SDL_Flip(screen);

    while (1) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        exit(EXIT_SUCCESS);
                        break;
                    case SDLK_x:
                        *Joueur = *xx; // Affectation des surfaces correspondantes
                        *Ordinateur = *o;
                        // Freeing memory
                        SDL_FreeSurface(*texte);
                        TTF_CloseFont(police);
                        TTF_Quit();
                        return;
                        break;
                    case SDLK_o:
                        *Joueur = *o; // Affectation des surfaces correspondantes
                        *Ordinateur = *xx;
                        // Freeing memory
                        SDL_FreeSurface(*texte);
                        TTF_CloseFont(police);
                        TTF_Quit();
                        return;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}








