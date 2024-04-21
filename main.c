#include "tictac.h"


int main()
{
    SDL_Surface *screen;
    int cont = 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("Unable to initialize SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }
    
    

    screen = SDL_SetVideoMode(900, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption("Tic-Tac-Toe", NULL);
    SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL);
    
   

    
   
    tic t;
    initialiserTic(&t);

    SDL_Surface *xx , *o , *texte ;
    TTF_Font *police = TTF_OpenFont("Pixeboy.ttf", 120);
    SDL_Color couleur = {0, 0, 0};
    SDL_Surface *Joueur, *Ordinateur;
    
    while (cont)
    {
        afficherTic(t, screen);
        choisirXO(screen, &xx, &o, &texte, police, couleur, &Joueur, &Ordinateur);

        if ((t.tour < 9) && atilgagner(t.tabsuivi) == 0)
        {
            if ((t.tour + t.joueur) % 2 == 0)
            {
                calcul_coup(t.tabsuivi);
                t.tour++;
            }
            else
            {
                SDL_Event event;
                SDL_WaitEvent(&event);

                if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        int mx = event.button.x / t.pos.w;
                        int my = event.button.y / t.pos.h;
                        int coup = 3 * my + mx;
                        if (t.tabsuivi[coup] == 0)
                        {
                            t.tabsuivi[coup] = 1;
                            t.tour++;
                        }
                    }
                }
                else if (event.type == SDL_QUIT)
                {
                    cont = 0;
                }
            }
        }
        else
        {
            Resultat(&t, screen);
            cont = 0;
        }

        SDL_Flip(screen);
    }

    liberer(t);
    SDL_FreeSurface(xx);
    SDL_FreeSurface(o);
    SDL_FreeSurface(texte);
    TTF_CloseFont(police);
    
   
    TTF_Quit();
    SDL_Quit();

    return 0;
}

