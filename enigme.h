/**
 * @file enigme5.h
 * @author ons ghariani (you@domain.com)
 * @brief header file 
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright esprit (c) 2023
 * 
 */
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_mixer.h>

typedef struct imageenigme 
{
  SDL_Rect posinscreen, posfromimg;
  SDL_Surface *img;
  SDL_Surface *screen;
} imageenigme;
typedef struct animation_enigme 
{
  SDL_Rect posinscreen, posfromimg[8];
  SDL_Surface *img;
  int frame;
  SDL_Surface *screen;
} animation_enigme;
typedef struct Enigme
{
  char question[255]; 
  char reponse[255];  
  char choix1[255];   
  char choix2[255];   
  int solution;       
  int selected;       
  int solved;         
  imageenigme won, lost, timeout, newscore, background;
  animation_enigme anim;
} Enigme;

typedef struct
{
  char name[50];
  int hp;
  int score;
  int current_level;
} perso;

typedef struct
{
  int x_pos; 
  int y_pos; 
} background;

void geneerEnigme(Enigme *p, char *nomfichier);     
void afficherEnigme(Enigme e, SDL_Surface *screen); 
void load(perso *p, background *b, char *nomfichier, char *nom);
void savegame(perso p, background b, char *nomfichier);
void animerpuzzle(Enigme *p);// main enigmes functions


// extra function
int next_button(int oldvalue, int operation, int max);                 
void afficherbackgroound(imageenigme c, SDL_Surface *screen);          
void afficher_newscore(int score, SDL_Surface *screen, imageenigme c); 
void afficher_animation(animation_enigme c);
// les initlisation des images
void initilisationimagebackground(imageenigme *c);
void initilisation_won(imageenigme *c);
void initilisation_lost(imageenigme *c);
void initilisation_time_out(imageenigme *c);
void initilisation_newscore(imageenigme *c);
void initilisation_animation(animation_enigme *c);
//*********************************
