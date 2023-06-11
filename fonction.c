#include <SDL/SDL.h>
#include "image.h"
#include <SDL/SDL_image.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "texte.h"
#define SCREEN_W 1920 
#define SCREEN_H 1080
#define SPRITE_W 400
#define SPRITE_H 300
void init_image(image *a,int x,int y,char nom[])
{
 	a->img = IMG_Load(nom);
 		if (a->img == NULL) {
 			return;
 		}
 	a->pos1.x=x;
 	a->pos1.y=y;
 }
void init_background(image *bg,int x,int y,char nom[])
 {
	 bg->img= IMG_Load(nom);
 		if(bg->img ==	NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 		return;
 }
 	bg->pos1.x=x;
 	bg->pos1.y=y;
 }
void liberer(image a)
{
	SDL_FreeSurface(a.img);
}
void afficher(image a,SDL_Surface *screen)
{
	SDL_BlitSurface(a.img,NULL,screen,&a.pos1);
}
 
 void initialiserTic (tic *ti)
{
int i;
ti->xobg= IMG_Load("xobg.png");
ti->pos_xobg.x=0 ;
ti->pos_xobg.y=0;
ti->imgx= IMG_Load("x.png");
ti->pos_imgx.x= 0;
ti->pos_imgx.y=0;
ti->imgo= IMG_Load("o.png");
ti->pos_imgo.x=0 ;
ti->pos_imgo.y=0;
for(i=0;i<9;i++)
{
ti->tabsuivi[i]=0;
}
ti->player=1;
ti->tournbr=0;
ti->pos.x=500;
ti->pos.y=150;
ti->textcolor.r=255;
ti->textcolor.g=255;
ti->textcolor.b=255;
ti->font=TTF_OpenFont("Roboto-BoldItalic.ttf",70);
}
void afficherTic(int tabsuivi[],SDL_Surface* screen,tic t)
{
int i;
SDL_BlitSurface(t.xobg,NULL,screen,&t.pos_xobg);
for(i=0;i<9;i++)
{
if (tabsuivi[i]==-1)
{
t.pos_imgx.x=133*(i%3);    
t.pos_imgx.y=133*(i/3);    
SDL_BlitSurface(t.imgx,NULL,screen,&t.pos_imgx);
}
else
if (tabsuivi[i]==1)
{
t.pos_imgo.x=133*(i%3);    
t.pos_imgo.y=133*(i/3);   
SDL_BlitSurface(t.imgo,NULL,screen,&t.pos_imgo);
}
}
}
int atilganer(int tabsuivi[])
{
int i;
int lignes_gagnantes[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
for(i=0;i<8;i++)
{
if ((tabsuivi[lignes_gagnantes[i][0]]== -1 )&&(tabsuivi[lignes_gagnantes[i][1]]==-1)&&(tabsuivi[lignes_gagnantes[i][2]]==-1))
return -1;
else 
if ((tabsuivi[lignes_gagnantes[i][0]]== 1 )&&(tabsuivi[lignes_gagnantes[i][1]]==1)&&(tabsuivi[lignes_gagnantes[i][2]]==1))

return  1;

}
return 0;
}
void Resultat (int tabsuivi[],SDL_Surface* screen,tic t)
{
int r=2;
char message[10];

r=atilganer(tabsuivi);

if(r==-1)
 {
 //printf("victory\n");
strcpy(message,"victory!");
t.textcolor.r=0;
t.textcolor.g=255;
t.textcolor.b=0;
}
else 
if(r==1)
//printf("game over\n");
{strcpy(message,"gameover");
t.textcolor.r=255;
t.textcolor.g=0;
t.textcolor.b=0;
}
//printf("null\n");
else 

strcpy(message,"null");
t.surfacetext=TTF_RenderText_Solid(t.font,message,t.textcolor);
SDL_BlitSurface(t.surfacetext,NULL,screen,&t.pos);

}
/*void Resultat (int tabsuivi[],SDL_Surface* screen,tic t)
{
int r;
char message[10];
r=atilganer(tabsuivi);
if(r==-1)
//printf("victory\n");
strcpy(message,"victory!");
else 
if(r==1)
//printf("game over\n");
strcpy(message,"gameover");
//printf("null\n");
else
strcpy(message,"null");
t.surfacetext=TTF_RenderText_Solid(t.font,message,t.textcolor);
SDL_BlitSurface(t.surfacetext,NULL,screen,&t.pos);
}*/
int minmax(int tabsuivi[9],int joueur)
{
int gagnant=atilganer(tabsuivi);
if(gagnant!=0)
return gagnant*joueur;
int coup=-1;
int score=-2;
int i;
for(i=0;i<9;i++)
{
if (tabsuivi[i]==0)
 {
tabsuivi[i]=joueur;
int mmscore=-minmax(tabsuivi,joueur*-1);
if(mmscore>score)
   {
score=mmscore;
coup=i;
   }
tabsuivi[i]=0;
 }
}
if(coup==-1)
return 0;
return score;
}
void calcul_coup(int tabsuivi[9])
{
int coup=-1;
int score=-2;
int i;
for(i=0;i<9;i++)
{
if (tabsuivi[i]==0)
 {
tabsuivi[i]=1;
int mmscore=-minmax(tabsuivi,-1);
tabsuivi[i]=0;
if(mmscore>score)
   {
score=mmscore;
coup=i;
   }
 }
}
tabsuivi[coup]=1;
}
void liberer_tic( tic t)
{
SDL_FreeSurface(t.xobg);
SDL_FreeSurface(t.imgx);
SDL_FreeSurface(t.imgo);
}

void initPerso(Personne *p)
{
 	p->img = IMG_Load("perso2.png");
 		if (p->img == NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 			return;
 		}
 		if (p->p==0)
 		{
 	p->pos1.x=250;
 	p->pos1.y=875.1;
 	p->pos1.w=SPRITE_W;
 	p->pos1.h=SPRITE_H;
 	p->pos2.x=0;
 	p->pos2.y=0;
 	p->pos2.w=SPRITE_W/4;
 	p->pos2.h=SPRITE_H/3;
 	} 
 	else
 	{
 	p->pos1.x=1210;
 	p->pos1.y=875.1;
 	p->pos1.w=SPRITE_W;
 	p->pos1.h=SPRITE_H;
 	p->pos2.x=0;
 	p->pos2.y=SPRITE_H/2;
 	p->pos2.w=SPRITE_W/4;
 	p->pos2.h=SPRITE_H/6;
 	}
 	
 	p->direction_animation=0;
 	p->up=0;
 	p->mouvement=0;
 	p->dy=870;
 	p->dx=1;
 	p->direction=1;
 	p->score=0;
 	p->vie=5;
 	
 }
 
/*void init_background(image *bg,char nom[])
 {
	 bg->img= IMG_Load(nom);
 		if(bg->img ==	NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 		return;
 			}
 	bg->pos1.x=0;
 	bg->pos1.y=0;
 	bg->pos2.x=7;
 	bg->pos2.y=0;
 	bg->pos2.w=(SCREEN_W);
 	bg->pos2.h=(SCREEN_H);
 }*/
/*void liberer(image a)
{
	SDL_FreeSurface(a.img);
}*/
void liberer1(Personne a)
{
	SDL_FreeSurface(a.img);
}
void afficherPerso(Personne p, SDL_Surface * screen)
{
	SDL_BlitSurface(p.img,&p.pos2,screen,&p.pos1);
	//SDL_BlitSurface(p.img,&p.pos4,screen,&p.pos3); 
}
//void afficher(image a,SDL_Surface *screen)
//{
//	SDL_BlitSurface(a.img,&a.pos2,screen,&a.pos1);
//}
void deplacerPerso (Personne *p, float dt)
{
	p->pos1.x+=(0.5*dt*dt+dt)*p->direction;

	//if(p->pos1.x>1800)
	//p->pos1.x=1800;
	//else if (p->pos1.x<7)
	//p->pos1.x=7;
}
void animerPerso (Personne* p)
{
	
	p->pos2.x+=p->pos2.w;
	if (p->pos2.x == SPRITE_W) p->pos2.x=0;
	p->pos2.y=p->direction_animation*p->pos2.h;
	
}

void saut (Personne* p)
{
p->pos1.y=0.1*p->dx*p->dx+6*p->dx+p->dy;
}
void initVie(image *img)
{
 	img->img = IMG_Load("vie.png");
 		if (img->img == NULL) {
 		printf("erreur unable to load: %s\n",SDL_GetError());
 			return;
 		}
 	img->pos1.x=1835;
 	img->pos1.y=0;
 	img->pos1.h=49;
 	img->pos1.w=300;
 	img->pos2.x=0;
 	img->pos2.y=0;
 	img->pos2.h=img->pos1.h;
 	img->pos2.w=img->pos1.w/5;
 }
void afficheVie(image img, SDL_Surface * screen)
{
	SDL_BlitSurface(img.img,&img.pos2,screen,&img.pos1); 
}


void liberer2(Background a)
{
SDL_FreeSurface(a.img1);
}


void initBack(Background * b)
{
if (b->lvl==1)
 b->img1= IMG_Load("bg11.png");
 else if (b->lvl==2)
 b->img1= IMG_Load("bg22.png");
 else
 b->img1= IMG_Load("bg33.png");
 /*if(b->img1 == NULL) {
 printf("erreur unable to load: %s\n",SDL_GetError());
 return;
 }*/
 b->img2= IMG_Load("bg2.png");
 if(b->img2 == NULL) {
 printf("erreur unable to load: %s\n",SDL_GetError());
 return;
 }
 if (b->b==0)
 {
 	b->pos1.x=0;
 	b->pos1.y=0;
 	b->pos2.x=0;
 	b->pos2.y=0;
 	if (b->np==2)
 	b->pos2.w=960;
 	else
 	b->pos2.w=1920;
 	b->pos2.h=1080;
 }
 else
 {
 	b->pos1.x=960;
 	b->pos1.y=0;
 	b->pos2.x=0;
 	b->pos2.y=0;
 	b->pos2.w=960;
 	b->pos2.h=1080;
 }
 	b->i=0;
 	b->img=b->img1;
 	
 	
}

void aficherBack(Background b, SDL_Surface * screen)
{
SDL_BlitSurface(b.img,&b.pos2,screen,&b.pos1);
//SDL_BlitSurface(b.img,&b.pos4,screen,&b.pos3);
}

void scrolling (Background * b, int direction, int pasAvancement)
{
switch(direction)
{
case 0:
b->pos2.x=pasAvancement;
break;
case 1:
//b->pos2.y=pasAvancement;
break;

}
}

void animerBackground( Background * e)
{
if (e->i % 2 == 0)
e->img=e->img1;
else
e->img=e->img2;
e->i++;
}
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y)
{
SDL_Color color;
Uint32 col=0;
char* pPosition=(char*) pSurface->pixels;
pPosition+=(pSurface->pitch * y);
pPosition+=(pSurface->format->BytesPerPixel *x);
memcpy(&col,pPosition,pSurface->format->BytesPerPixel);
SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
return (color);
}

int isblack(point P,SDL_Surface* surf)
{
//printf("lol");
SDL_Color c;
c=GetPixel(surf,P.x,P.y);

return (c.b==0 && c.g==0 && c.r==0);
}

int collisionPP( Personne p, SDL_Surface * Masque)
{
if ((isblack(p.P[2],Masque)&&isblack(p.P[7],Masque) )|| (isblack(p.P[6],Masque)&&isblack(p.P[7],Masque))||(isblack(p.P[2],Masque)&&isblack(p.P[6],Masque)&&isblack(p.P[7],Masque))||isblack(p.P[7],Masque))
	return 1;
else if ((isblack(p.P[4],Masque)&&isblack(p.P[5],Masque) )|| (isblack(p.P[5],Masque)&&isblack(p.P[6],Masque))||(isblack(p.P[4],Masque)&&isblack(p.P[5],Masque)&&isblack(p.P[6],Masque) ) || isblack(p.P[5],Masque))
	return 2;
else if ((isblack(p.P[0],Masque)&&isblack(p.P[3],Masque) )|| (isblack(p.P[3],Masque)&&isblack(p.P[4],Masque))||(isblack(p.P[0],Masque)&&isblack(p.P[3],Masque)&&isblack(p.P[4],Masque))||isblack(p.P[3],Masque))
	return -1;
	else
	return 0;

}


void initminimap(minimap *m)
{
if(m->lvl==1)
m->img_minimap= IMG_Load("minibg.png");
else if(m->lvl==2)
m->img_minimap= IMG_Load("minibg2.png");
else
m->img_minimap= IMG_Load("minibg3.png");
m->pos_minimap.x=100 ;
m->pos_minimap.y=5;

m->pos2_minimap.x=0;
m->pos2_minimap.y=0;
m->pos2_minimap.w=384;
m->pos2_minimap.h=216;
m->min_main=IMG_Load("minimain.png");
m->pos_minmain.x=200;
m->pos_minmain.y=3;
}
void affichermap (minimap m, SDL_Surface * screen)
{
SDL_BlitSurface(m.img_minimap,&m.pos2_minimap,screen,&m.pos_minimap);
SDL_BlitSurface(m.min_main,NULL,screen,&m.pos_minmain);
}
void MAJMinimap(Personne p , minimap * m, SDL_Rect camera, int redimensionnement)
{
SDL_Rect posJoueurABS;
m->pos_minmain.x= (p.pos1.x ) * redimensionnement/100+13;
m->pos_minmain.y= 0.5*(p.pos1.y ) * redimensionnement/100;
/*m->pos2_minimap.x ++;
posJoueurABS.x = p.pos1.x + camera.x;
posJoueurABS.y = p.pos1.y + camera.y;*/
//m->pos_minmain.x=posJoueurABS.x * redimensionnement/100;
//m->pos_minmain.y=posJoueurABS.y * redimensionnement/100;
m->pos2_minimap.x =camera.x* redimensionnement/100;

}
 void liberer22(minimap m)
{
SDL_FreeSurface(m.img_minimap);
SDL_FreeSurface(m.min_main);
}
/*void sauvegarder( int score, char nomjoueur[], char scores[])
{
FILE* f=NULL;
f=fopen(scores,"w");
if(f!=NULL)
    {
  fprintf (f,"playername:%s,score:%d\n",nomjoueur,score);
    
    fclose(f);
}
}
void meilleur( char scores[], int *score, char nomjoueur[])
{  //text t,t1;
   FILE* f=NULL;
   char player[20] ;
   //char message[20];   
   int mc;
 // inittext3 (&t);
  //inittext4 (&t1);
f=fopen(scores,"r");
if (f!=NULL)
{
mc=0;
while(fscanf(f,"%s %d\n",nomjoueur,score)!=EOF)
{
    if(mc<score)
   { 
    mc=score;
    strcpy(player,nomjoueur);
   }

}
/*sprintf(message, "%d", mc);
displaytext2( t,screen ,mc )
displaytext3( t,screen ,player )
*score=mc;*/
//}
//}*/
void sauvegarder( int score, char nomjoueur[], char scores[])
{
FILE* f=NULL;
f=fopen(scores,"a");
if(f!=NULL)
    {
  fprintf (f,"%s %d\n",nomjoueur,score);

    fclose(f);
}
}

void meilleur( char scores[], int *score, char nomjoueur[])
{
   FILE* f=NULL;
   char player[20] ;
   int mc,s;

f=fopen(scores,"r");
if (f!=NULL)
{
mc=0;
while(fscanf(f,"%s %d\n",player,&s)!=EOF)
{
    if(mc<s)
   {
    mc=s;
    strcpy(nomjoueur,player);
   }
*score=mc;
}
}

fclose(f);
}
//////////////////////////enemy zone///////////////////////////
void initEnemy(enemy *e)
{
 e->imgR=IMG_Load("all.png");
 e->dir=rand()%2;
 e->max=800;
 e->min=0;
 if(e->dir==0)
  {
    e->pos.x=200;
  }
 else 
  if(e->dir==1)
  {
   e->pos.x=785;
  }
  e->pos.y=900;
  e->rectangle=0;
  e->Mhp=15000;//23
  e->hp=e->Mhp;
  e->state=WAITING;
  e->folie=0;
  e->dep=1;
  //e->a=0;
}
void displayEnemy(enemy *e,SDL_Surface* screen)
{
  if(e->dir==0)//left
 {
   if(e->folie==1/* && (e->hauteur>=0 && e->hauteur<60)*/ )
   {SDL_BlitSurface(e->imgR,&e->carre2[e->rectangle],screen,&e->pos);}
   else
   if(e->folie==0 /*|| (e->hauteur<0 && e->hauteur>60)*/ )
   {SDL_BlitSurface(e->imgR,&e->carre[e->rectangle],screen,&e->pos);}
   SDL_Flip(screen);
   e->rectangle++;
   if (e->rectangle==4)
   e->rectangle=0;
 }
  if(e->dir==1)//right
 {
   if(e->folie==0)
   {SDL_BlitSurface(e->imgR,&e->carre1[e->rectangle],screen,&e->pos);} 
   else
   if(e->folie==1)
   {SDL_BlitSurface(e->imgR,&e->carre3[e->rectangle],screen,&e->pos);}
   SDL_Flip(screen);
   e->rectangle++;
   if (e->rectangle==4)
   e->rectangle=0;
 }
 SDL_Delay(40);
 }
 
void animateX(enemy *e)
{
int c;
 for(c=0;c<4;c++)
 {
  e->carre[c].x=0+c*100;
  e->carre[c].y=0;
  e->carre[c].w=100;
  e->carre[c].h=100;
  e->carre1[c].x=0+c*100;
  e->carre1[c].y=100;
  e->carre1[c].w=100;
  e->carre1[c].h=100;
  e->carre2[c].x=0+c*100;
  e->carre2[c].y=200;
  e->carre2[c].w=100;
  e->carre2[c].h=100;
  e->carre3[c].x=0+c*100;
  e->carre3[c].y=300;
  e->carre3[c].w=100;
  e->carre3[c].h=100;
 }
}

void moveEnnemyX(enemy *e)
{
 //if(e->etat==0)
 if (e->pos.x>e->max)
 {
  e->dir=1;
 }
  if (e->pos.x<e->min)
 {
  e->dir=0;
 }
 if(e->dir==0)
 {
 e->pos.x=e->pos.x+15;
 }
 else if (e->dir==1)
 {
 e->pos.x=e->pos.x-15;
 }

}

int collisionBB(Personne p,enemy e)
{
 if ((p.pos1.x+p.pos2.w<e.pos.x)||(p.pos1.x>e.pos.x+e.pos.w)||(p.pos1.y+p.pos2.h<e.pos.y)||(p.pos1.y>e.pos.y+e.pos.h))
 {
 return 0;
 }
 else 
 {
 return 1;
 }
}
void updateEnnemiState (enemy* e,int dist)
{
switch(e->state)
{
case WAITING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else if (dist>100)
{e->state=WAITING;}
break;
case FOLLOWING:
if (dist<50)
{e->state=ATTACKING;}
else if (dist>100)
{e->state=WAITING;}
else if(dist<100 && dist>50)
{e->state=FOLLOWING;}
break;

case ATTACKING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else 
if(dist>100)
{e->state=WAITING;}
else 
if (dist<50)
{e->state=ATTACKING;}
break;
}
}
void accelerer(enemy *e)
{

 if (e->pos.x>e->max)
 {
  e->dir=1;
 }
  if (e->pos.x<e->min)
 {
  e->dir=0;
 }
 if(e->dir==0)
 {
 e->pos.x=e->pos.x+5;
 }
 else if (e->dir==1)
 {
 e->pos.x=e->pos.x-5;
 }
 
}
void mouvement(enemy* e,SDL_Rect posPerso)
{
int largeur;
largeur=180;
if(e->pos.x==posPerso.x-50)
{e->dir=1;}
if(e->pos.x==posPerso.x+largeur+20)
{e->dir=0;}
if(e->dir==0)
{
e->pos.x=e->pos.x+5;
}
else 
if(e->dir==1)
{e->pos.x=e->pos.x-5;}
}
/*void displayAttack(enemy *e,SDL_Rect posPerso)
{
if(e->pos.x==posPerso.x)
{e->dir=1;}
if(e->pos.x==posPerso.x+180)
{e->dir=0;}
}*/
void IAmove(enemy *e,SDL_Rect posPerso,int k,int k1)
{
 int dist;
 dist=e->pos.x-(posPerso.x);
 if(e->state==ATTACKING)
 {
  e->min=posPerso.x;
  e->max=posPerso.x+100;
 }
 if(k>0)
 {
 e->min=e->min-k+k1;
 e->max=e->max-k+k1;
 e->pos.x=e->pos.x-k+k1;
 e->pos.x=e->pos.x-k+k1;
 }
 if (e->min<-100)
 {  
 e->min=-100;
 }
  if(dist<0)
  {dist=-dist;}
 /*if (dist>0 ||dist<100)
 {
  if(e->pos.x>posPerso.x)
 {
 e->a=1;
 }
 else 
 if(e->pos.x<posPerso.x)
 {
 e->a=2;
 }
 }*/
 updateEnnemiState(&(*e),dist);
}
/////////////////////////////////////////////////////////////////////////////////////enemy 2//////////////////////////////////////////////////////////////////////////////////////////////////
void initEnemy1(enemy *e)
{
 e->imgR=IMG_Load("all.png");
 /*e->dir=rand()%2;
 e->max=800;
 e->min=0;*/
 /*if(e->dir==0)
  {
    e->pos.x=200;
  }
 else 
  if(e->dir==1)
  {
   e->pos.x=785;
  }*/
  e->pos.y=900;
  e->rectangle=0;
  e->Mhp=15000;//23
  e->hp=e->Mhp;
  e->state=WAITING;
  /*e->folie=0;*/
  //e->dep=1;
  //e->a=0;
}
void animate1X(enemy *e)
{
int c;
 for(c=0;c<4;c++)
 {
  /*e->carre[c].x=0+c*100;
  e->carre[c].y=0;
  e->carre[c].w=100;
  e->carre[c].h=100;*/
  e->carre1[c].x=0+c*100;
  e->carre1[c].y=100;
  e->carre1[c].w=100;
  e->carre1[c].h=100;
  e->carre2[c].x=0+c*100;
  e->carre2[c].y=200;
  e->carre2[c].w=100;
  e->carre2[c].h=100;
  if(c>2)
  {
  e->carre3[c].x=0+c*100;
  e->carre3[c].y=300;
  e->carre3[c].w=100;
  e->carre3[c].h=100;
 }
 if(c>3)
 {
  e->carre3[c].x=0+c*(100/4);
  e->carre3[c].y=(300/3)*2;
  e->carre3[c].w=100;
  e->carre3[c].h=100;

 }
 }
 }

void moveEnnemyX1(enemy *e)
{
 //if (e->dep==1)
 /*{*/
 if (e->pos.x>e->max)
 {
  e->dir=1;
 }
  if (e->pos.x<e->min)
 {
  e->dir=0;
 }
 if(e->dir==0)
 {
 e->pos.x=e->pos.x+15;
 }
 else if (e->dir==1)
 {
 e->pos.x=e->pos.x-15;
 }
 }
/*}*/
int collisionBB1(Personne p,enemy e)
{
 if ((p.pos2.x+p.pos2.w<=e.pos.x)||(p.pos2.x>=e.pos.x+e.pos.w)||(p.pos2.y+p.pos2.h<=e.pos.y)||(p.pos2.y>=e.pos.y+e.pos.h))
 {
 return 0;
 }
 else 
 {
 return 1;
 }
}

void updateEnnemiState1(enemy* e,int dist)
{
switch(e->state)
{
case WAITING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else if (dist>100)
{e->state=WAITING;}
break;
case FOLLOWING:
if (dist<50)
{e->state=ATTACKING;}
else if (dist>100)
{e->state=WAITING;}
else if(dist<100 && dist>50)
{e->state=FOLLOWING;}
break;
case ATTACKING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else 
if(dist>100)
{e->state=WAITING;}
else 
if (dist<50)
{e->state=ATTACKING;}
break;
}
}
void IAmove1(enemy *e,SDL_Rect posPerso)
{
 int dist;
 dist=e->pos.x-(posPerso.x);
/* if(e->state==ATTACKING)
 {
  e->min=posPerso.x;
  e->max=posPerso.x+100;
 }*/
 /*if(k>0)
 {
 e->min=e->min-k+k1;
 e->max=e->max-k+k1;
 e->pos.x=e->pos.x-k+k1;
 e->pos.x=e->pos.x-k+k1;
 }*/
 if (e->min<-100)
 {  
 e->min=-100;
 }
  if(dist<0)
  {dist=-dist;}
 /*if (dist>0 ||dist<100)
 {
  if(e->pos.x>posPerso.x)
 {
 e->a=1;
 }
 else 
 if(e->pos.x<posPerso.x)
 {
 e->a=2;
 }
 }*/
 updateEnnemiState1(&(*e),dist);
}
