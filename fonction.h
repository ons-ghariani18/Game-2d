#ifndef Texte_H
#define Texte_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "image.h"
typedef struct 
{
SDL_Rect pos;
TTF_Font *font;
SDL_Surface *surfacetext;
SDL_Color textcolor;
char texte[20];
}text;
typedef struct
{
	SDL_Rect position;
	TTF_Font * font;
	SDL_Surface * surfaceTexte;
	SDL_Color texteCoulor;
	char texte [50];
} texte;
void initTexte(texte *t,int x,int y,int r,int g,int b,char name[], int p);
void freeTexte(texte t);
void freeTexte1(texte t,texte t1);
void displaytexte(texte t,SDL_Surface *screen,char name[]);
void inittext (text *t);
void inittext2 (text *t);
void freetext(text t);
void displaytext(text t,text t2,SDL_Surface *screen,char message[]);
#endif
