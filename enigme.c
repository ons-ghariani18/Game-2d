/**
 * @file enigme5.c
 * @author ons ghariani (you@domain.com)
 * @brief source file 
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright esprit (c) 2023
 * 
 */
#include "enigme5.h"
void afficherbackgroound(imageenigme c,SDL_Surface *screen)
{

    SDL_BlitSurface(c.img, &c.posfromimg,screen, &c.posinscreen);
}

void afficherEnigme(Enigme e ,SDL_Surface *screen)
{
 
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
    }

    // Load the font
    TTF_Font *font = TTF_OpenFont("src/font/ARLRDBD.ttf", 20);
    TTF_Font *font2 = TTF_OpenFont("src/font/ARLRDBD.ttf", 14);

    if (!font)
    {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }
    if (!font2)
    {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }
    // Create the question surface
    SDL_Surface *questionSurface = TTF_RenderText_Blended(font2, e.question, (SDL_Color){255, 255, 255});
    if (!questionSurface)
    {
        fprintf(stderr, "Failed to render question: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Create the choice surfaces
    SDL_Surface *choice1Surface = TTF_RenderText_Blended(font, e.reponse , (SDL_Color){255, 255, 255});
    SDL_Surface *choice2Surface = TTF_RenderText_Blended(font,e.choix1 , (SDL_Color){255, 255, 255});
    SDL_Surface *choicecSurface = TTF_RenderText_Blended(font,e.choix2, (SDL_Color){255, 255, 255});
    SDL_Surface *selectionright = IMG_Load("src/selection/finalblade.png");
    SDL_Surface *selectionleft = IMG_Load("src/selection/finalbladeright.png");

    if (!choice1Surface || !choice2Surface)
    {
        fprintf(stderr, "Failed to render choices: %s\n", SDL_GetError());
        SDL_FreeSurface(questionSurface);
        TTF_CloseFont(font);
        return;
    }
    if (!selectionright)
    {
        fprintf(stderr, "Failed to render selectionright: %s\n", SDL_GetError());
        SDL_FreeSurface(questionSurface);
        SDL_FreeSurface(selectionright);
        TTF_CloseFont(font);
        return;
    }
 

    // Blit the surfaces to the screen
    SDL_Rect questionRect = {10, 100, questionSurface->w, questionSurface->h};
    SDL_Rect choice1Rect = {131, 233, choice1Surface->w, choice1Surface->h};
    SDL_Rect choice2Rect = {131, 350, choice2Surface->w, choice2Surface->h};
    SDL_Rect choicecRect = {131, 455, choicecSurface->w, choicecSurface->h};
    if (e.solved == 0)//kena mezel mejewebch
    {
        afficherbackgroound(e.background,screen);
        afficher_animation(e.anim);
        SDL_BlitSurface(questionSurface, NULL,  screen, &questionRect);
        SDL_BlitSurface(choice1Surface, NULL, screen, &choice1Rect);
        SDL_BlitSurface(choice2Surface, NULL, screen, &choice2Rect);
        SDL_BlitSurface(choicecSurface, NULL, screen, &choicecRect);
        if (e.selected != -1)
        {
            SDL_Rect selectionrightright, selectionrightleft;


            if (e.selected == 0)
            {
                SDL_Rect selectionrightright = {60, 233, questionSurface->w, questionSurface->h};
                SDL_Rect selectionrightleft = {443, 233, questionSurface->w, questionSurface->h};
            }
            else if (e.selected == 1)
            {
                SDL_Rect selectionrightright = {60, 350, questionSurface->w, questionSurface->h};
                SDL_Rect selectionrightleft = {443, 350, questionSurface->w, questionSurface->h};
            }
            else if (e.selected == 2)
            {
                SDL_Rect selectionrightright = {60, 455, questionSurface->w, questionSurface->h};
                SDL_Rect selectionrightleft = {443, 455, questionSurface->w, questionSurface->h};
            }
            SDL_BlitSurface(selectionleft, NULL, screen, &selectionrightright);
            SDL_BlitSurface(selectionright, NULL, screen, &selectionrightleft);
        }
    }
    else if (e.solved == 1)
    {
        SDL_BlitSurface(e.won.img, NULL, screen, &e.background.posinscreen);
        Mix_HaltMusic();                     

    }
    else if (e.solved == 2)
    {
        SDL_BlitSurface(e.lost.img, NULL, screen,&e.background.posinscreen);
        Mix_HaltMusic();  
    }
    else if (e.solved == 3)
    {
        SDL_BlitSurface(e.timeout.img, NULL, screen,&e.background.posinscreen);
        Mix_HaltMusic(); 
    }

    // Free the surfaces and font
    SDL_FreeSurface(questionSurface);
    SDL_FreeSurface(choice1Surface);
    SDL_FreeSurface(choice2Surface); 
    TTF_CloseFont(font);
}

int next_button(int oldvalue, int operation, int max)
{
    if ((oldvalue > max) || (oldvalue < 0))
    {
        return 0;
    }
    if (operation == 2)
    {
        if (oldvalue == max)
        {
            return 0;
        }
        else
        {
            oldvalue++;
        }
    }
    else if (operation == 0)
    {
        if (oldvalue == 0)
        {
            return max;
        }
        else
        {
            oldvalue--;
        }
    }
    return oldvalue;
}
void geneerEnigme(Enigme *p, char *nomfichier)
{
    p->solved = 0;
    initilisation_newscore(&p->newscore);
    initilisation_won(&p->won);
    initilisation_lost(&p->lost);
    initilisation_time_out(&p->timeout);
    // Open the file for reading
    FILE *file = fopen(nomfichier, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", nomfichier);
        exit(1);
    }

//*************************************** 
    int num_lines = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            num_lines++;
        }
    }
    
//*************************************** 
     srand(time(NULL));
    int line_num = rand() % num_lines;
 
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < line_num; i++)
    {
        while ((c = fgetc(file)) != EOF && c != '\n') ;
    }

  
    char line[256];
    fgets(line, sizeof(line), file);  

    
    sscanf(line, "%255[^;];%255[^;];%255[^;];%255[^;];%d;", p->question, p->reponse, p->choix1, p->choix2, &p->solution);

    
    fclose(file);
}

//les fonction d affichages
void afficher_animation(animation_enigme c)
{
    SDL_BlitSurface(c.img, &c.posfromimg[c.frame], c.screen, &c.posinscreen);
}

void afficher_newscore(int score, SDL_Surface *screen, imageenigme c) {

 
    char scoreStr[10];
  

    
    TTF_Font *font = TTF_OpenFont("src/font/ARLRDBD.ttf", 28);
        if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Color color = { 255, 255, 255 };
 
    SDL_snprintf(scoreStr, sizeof(scoreStr), "%d", score);
    
    SDL_Surface *timeSurface = TTF_RenderText_Solid(font, scoreStr, color);

    
    SDL_Rect destRect = { 250, 430, 0, 0 };

 
 
 
    SDL_BlitSurface(c.img, NULL, screen, &c.posinscreen);
     SDL_BlitSurface(timeSurface, NULL, screen, &destRect);

    
    SDL_FreeSurface(timeSurface);
    TTF_CloseFont(font);

}
//les initialisation des images
void initilisationimagebackground(imageenigme *c)
{
    c->img = IMG_Load("src/engime/finalback.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding background img %s\n", TTF_GetError());
        return;
    }
    c->posfromimg.h = c->img->h;
    c->posfromimg.w = c->img->w;
    c->posfromimg.x = 0;
    c->posfromimg.y = 0;

    c->posinscreen.h = c->img->h;
    c->posinscreen.w = c->img->w;
    c->posinscreen.x = 0;
    c->posinscreen.y = 0;
}
void initilisation_lost(imageenigme *c)
{
    c->img = IMG_Load("src/status/lost.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding lost img %s\n", TTF_GetError());
        return;
    }
    c->posfromimg.h = c->img->h;
    c->posfromimg.w = c->img->w;
    c->posfromimg.x = 0;
    c->posfromimg.y = 0;
}
void initilisation_time_out(imageenigme *c)
{
    c->img = IMG_Load("src/status/time_out.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding time out img %s\n", TTF_GetError());
        return;
    }
    c->posfromimg.h = c->img->h;
    c->posfromimg.w = c->img->w;
    c->posfromimg.x = 0;
    c->posfromimg.y = 0;
}
void initilisation_won(imageenigme *c)
{
    c->img = IMG_Load("src/status/winenigme.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding won img %s\n", TTF_GetError());
        return;
    }
    c->posfromimg.h = c->img->h;
    c->posfromimg.w = c->img->w;
    c->posfromimg.x = 0;
    c->posfromimg.y = 0;
};
void initilisation_newscore(imageenigme *c)
{
    c->img = IMG_Load("src/score/new score.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding won img %s\n", TTF_GetError());
        return;
    }

    c->posinscreen.h = c->img->h;
    c->posinscreen.w = c->img->w;
    c->posinscreen.x = 152;
    c->posinscreen.y = 414;
};
void initilisation_animation(animation_enigme *c)
{
    int SPRITE_WIDTH = 21;
    int SPRITE_HEIGHT = 60;

    c->img = IMG_Load("src/animation/timer.png");
    if (c->img == NULL)
    {
        fprintf(stderr, "error loding background img %s\n", TTF_GetError());
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        c->posfromimg[i].x = i * SPRITE_WIDTH;
        c->posfromimg[i].y = 0;
        c->posfromimg[i].w = SPRITE_WIDTH;
        c->posfromimg[i].h = SPRITE_HEIGHT;
    }

    c->posinscreen.h = c->img->h;
    c->posinscreen.w = c->img->w;
    c->posinscreen.x = 16;
    c->posinscreen.y = 577;
    c->frame = 0;
}
void savegame(perso p, background b, char *nomfichier)
{
  FILE *f = fopen(nomfichier, "a");
  if (f == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier");
    exit(EXIT_FAILURE);
  }
  fprintf(f, "%s %d %d %d %d %d\n", p.name, p.hp, p.score, p.current_level, b.x_pos, b.y_pos);
  fclose(f);
}
void load(perso *p, background *b, char *nomfichier, char *nom)
{
  FILE *f = fopen(nomfichier, "r");
  if (f == NULL)
  {
    perror("Erreur lors de l'ouverture du fichier");
    exit(EXIT_FAILURE);
  }
  
  fseek(f, 0, SEEK_END); 
  if (ftell(f) == 0)
  { 
    printf("Empty file\n");
    fclose(f);
    exit(1);
  }
  rewind(f); 

  int found = 0;
  char buffer[256]; 

  while (!found && fgets(buffer, sizeof(buffer), f))
  {

    sscanf(buffer, "%s %d %d %d %d %d", p->name, &p->hp, &p->score, &p->current_level, &b->x_pos, &b->y_pos);
    if (strcmp(p->name, nom) == 0)
    {
      found = 1;
    }
  }
  if (!found)
  {
    printf("Personne '%s' non trouvee dans le fichier.\n", nom);
    exit(EXIT_FAILURE);
  }
  fclose(f);
}
void animerpuzzle(Enigme *e){
 if(e->solved==0) {
 e->anim.frame++;
            if (e->anim.frame > 7&&e->solved==0)
            {
                e->solved = 3;
                e->anim.frame = 0;
            }
  } 
 




};
 



 
