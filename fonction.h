#ifndef Image_H
#define Image_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
  	int x,y;
} point;

typedef struct
{       
	point P[8];
	int direction_animation,up,direction,mouvement,score,vie,dy,dx,p;
        SDL_Rect pos1,pos2;
	SDL_Surface * img;
} Personne;

typedef struct
{
	SDL_Rect pos1;
	SDL_Rect pos2;
	SDL_Surface * img;
} image;
void init_image(image *a,int x,int y,char nom[]);
void init_background(image *bg,int x,int y,char nom[]);
void liberer(image a);
void afficher(image a,SDL_Surface *screen);

typedef struct
{
 SDL_Surface * xobg;
 SDL_Rect      pos_xobg;
 SDL_Surface * imgx;
 SDL_Rect      pos_imgx;
 SDL_Surface * imgo;
 SDL_Rect      pos_imgo;
 int tabsuivi[9];
 int player;//1 humain 2 computer
 int tournbr;
 SDL_Rect pos;
 TTF_Font *font;
 SDL_Surface *surfacetext;
 SDL_Color textcolor;
 char texte[20];
}tic;

void initialiserTic (tic * t) ; 
void afficherTic(int tabsuivi[],SDL_Surface* screen,tic t);
int atilganer(int tabsuivi[]);
void Resultat (int tabsuivi[],SDL_Surface* screen,tic t);
int minmax(int tabsuivi[9],int joueur);
void calcul_coup(int tabsuivi[9]);
void liberer_tic( tic t);

typedef struct
{
  	int i,b,np,lvl;
	SDL_Rect pos1,pos2;
	SDL_Surface * img, *img1 ,*img2;
} Background;

typedef struct
{
int lvl;
 SDL_Surface * img_minimap;
 SDL_Rect      pos_minimap,pos2_minimap;
 SDL_Surface * min_main;
 SDL_Rect      pos_minmain;
} minimap;
void initminimap(minimap *m);
void affichermap( minimap m, SDL_Surface * screen);
void MAJMinimap(Personne p , minimap * m, SDL_Rect camera, int redimensionnement);
void liberer22(minimap m);
void sauvegarder( int score, char nomjoueur[], char nomfichier[]);
void meilleur( char nomfichier[], int *score, char nomjoueur[]);  

void initBack(Background * b);
void aficherBack(Background b, SDL_Surface * screen);
void animerBackground( Background * e);
int collisionPP( Personne p, SDL_Surface * Masque);
void scrolling (Background * b, int direction, int pasAvancement);
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int isblack(point P,SDL_Surface* surf);

void initPerso(Personne *p);
void afficherPerso(Personne p, SDL_Surface * screen);
void deplacerPerso (Personne *p, float dt);
void animerPerso (Personne* p);
void saut (Personne* p);
//void liberer(image a);
void liberer2(Background a);
void liberer1(Personne a);
void initVie(image *img);
void afficheVie(image img, SDL_Surface * screen);

typedef enum STATE STATE;
enum STATE{WAITING,FOLLOWING,ATTACKING,ESCAPING};
typedef struct 
{
SDL_Rect psObstacle;
SDL_Surface *obstacle;
}personne;
/**
* @struct enemy
* @brief struct pour  enemy
*/
typedef struct 
{
SDL_Rect pos;/*!< current positon*/
SDL_Surface *imgR;
SDL_Surface *imgL;
//int marge;
int hp;
int Mhp;
int dir;
int max;
int min;
int dep;
int rectangle;
int hauteur;
SDL_Rect carre[6];
SDL_Rect carre1[6];
SDL_Rect carre2[6];
SDL_Rect carre3[6];
STATE state;
int folie;
}enemy;
void initEnemy(enemy *e);
void displayEnemy(enemy *e,SDL_Surface* screen);
void animateX(enemy *e);
void moveEnnemyX(enemy *e);
int  collisionBB(Personne p,enemy e);
void updateEnnemiState (enemy* e,int dist);
//void anime(enemy *e);
void accelerer(enemy *e);
void mouvement(enemy* e,SDL_Rect posPerso);
void displayAttack(enemy *e,SDL_Rect posPerso);
void IAmove(enemy *e,SDL_Rect posPerso,int k,int k1);
void initEnemy1(enemy *e);
void animate1X(enemy *e);
void moveEnnemyX1(enemy *e);
int  collisionBB1(Personne p,enemy e);
void updateEnnemiState1(enemy* e,int dist);
void IAmove1(enemy *e,SDL_Rect posPerso);
#endif
