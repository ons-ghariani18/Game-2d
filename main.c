#include "texte.h"
#include "image.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main (int argc, char** argv) {
 	SDL_Surface *screen=NULL,*screen1=NULL,*screen2=NULL,*screen3=NULL,*screen4=NULL;	
 	int loop = 0,blp=0,nbg=1,volume=5,pr=0,x=0,z=1,pr1=0,j=0,i=0,blbg=0,bl3=0,bl4=0;	
 	int bl=0,bl1=0,bll=0,bl11=0,bl22=1,a=0,bl2=1,ii=0,y=0,y1=0,p2=1,h=0,h1=0,vv=0,pasAvancement=0,pasAvancement1=0,direction=0,direction1=0,pw=80,ph=107,redimensionnement=20,b,n,k=0,np=1,lvl=1;
 	float dt=0,dt1=0,bx,by,bx1,by1;
 	
 	int keysheld[323]={0};
 		  SDL_Surface *surf1 = SDL_LoadBMP("back1.bmp");
 		  SDL_Surface *surf2 = SDL_LoadBMP("back2.bmp");
 		  SDL_Surface *surf3 = SDL_LoadBMP("back3.bmp");
 		   SDL_Surface *surf=surf1;
 	char zz[10];
 	char scores[8]="lol.txt";
 	int sp=1000000;
 	char nom[20]="aziz";
 	char message[20],ch[20];
 	char nj[20];
 	Uint32 score=0,duree;
	image img;
	Personne perso,perso1;
	perso.p=0;
	perso1.p=1;
        enemy e;
	Background bg,bg1;
	bg.b=0;
 	bg1.b=1;
 	bg.lvl=1;
 	
 	SDL_Event event;
 	texte t,t1,t2;	
 	minimap m;
 	m.lvl=1;
 	//SDL_Rect camera;
 	text t11,t22;
 	
 	int t4[9]={-1,0,1,-1,0,0,-1,0,0};
 	int lignes_gagnantes[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
 	tic ti;
 	int coup,x1;
 	int pl1=0,pl2=0;
	//char nj[20];
	image s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,fs0,fs1,a0,a1,a2,a3,logo,logo1,cm,cm1,tunis,usa,uk,titre,fleche,bgg,bgg1,bg2,bg3,bg4,v0,v1,v2,v3;
	image bouton_play,bouton_play1,bouton_settings,bouton_settings1,bouton_credit,bouton_credit1,bouton_quit,bouton_quit1;
 	image *p=&bouton_play,*s=&bouton_settings,*c=&bouton_credit,*q=&bouton_quit,*v=&v3,*p1,*f=&fs0,*ss[10]={&s9,&s0,&s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8},sb,mg,ttt,m1,names,per1,per2,per11,per21;	
 	texte tt,tt1;
 	atexit(SDL_Quit);
 	Mix_Music *music;
 	Mix_Chunk *son;
 	Mix_Chunk *son1;
 	Mix_Music *music1;
 	
 	SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_TIMER |SDL_INIT_AUDIO );
 	TTF_Init();
 	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)!=0)
  	{
  		 printf("ERROR: %s\n",SDL_GetError());
   		return 1; 
 	 }
 	screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
 	if (!screen) {
 		printf("erreur %s\n",SDL_GetError());
 		return 1;}
 	if(Mix_OpenAudio(48000,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1){
		printf("Erreur : %s \n",Mix_GetError());
		return 1;
	}
 	son = Mix_LoadWAV("sound.wav");
 	son1 = Mix_LoadWAV("jump.wav");
 	music = Mix_LoadMUS("music.mp3");
 	music1 = Mix_LoadMUS("music1.mp3");
 	init_background(&bgg,0,0,"bg.png");
 	init_background(&bgg1,0,0,"bg1.png");
	init_background(&bg2,0,0,"bg2.png");
	init_background(&bg3,0,0,"bg3.png");
	init_image(&bouton_play,771,400,"play.png");
 	init_image(&bouton_play1,771,400,"play1.png");
 	init_image(&bouton_settings,772,500,"settings.png");
 	init_image(&bouton_settings1,768,500,"settings1.png");
 	init_image(&bouton_credit,772,600,"credit.png");
 	init_image(&bouton_credit1,772,600,"credit1.png");
 	init_image(&bouton_quit,770,700,"quit.png");
 	init_image(&bouton_quit1,770,700,"quit1.png");
 	init_image(&v0,900,550,"v0.png");
 	init_image(&v1,900,550,"v1.png");
  	init_image(&v2,900,550,"v2.png");
  	init_image(&v3,900,550,"v3.png");
 	init_image(&fleche,0,0,"fleche.png");
 	init_image(&titre,350,150,"titre.png");
 	init_image(&tunis,6,950,"tunis.png");
  	init_image(&usa,128,950,"usa.png");
    	init_image(&uk,200,950,"uk.png");
 	init_image(&logo,1755,981,"logo.png");
 	init_image(&logo1,53,905,"logo1.png");
 	init_image(&cm,990,500,"cm.png");
  	init_image(&cm1,990,650,"cm1.png");
 	init_image(&a0,3,0,"a0.png");
 	init_image(&a1,3,0,"a1.png");
 	init_image(&a2,960,0,"a0.png");
 	init_image(&a3,960,0,"a1.png");
 	init_image(&fs0,900,700,"fs0.png");
 	init_image(&fs1,900,700,"fs1.png");
 	init_image(&s0,0,0,"s0.png");
 	init_image(&s1,0,0,"s1.png");
 	init_image(&s2,0,0,"s2.png");
 	init_image(&s3,0,0,"s3.png");
 	init_image(&s4,0,0,"s4.png");
 	init_image(&s5,0,0,"s5.png");
 	init_image(&s6,0,0,"s6.png");
 	init_image(&s7,0,0,"s7.png");
 	init_image(&s8,0,0,"s8.png");
 	init_image(&s9,0,0,"s9.png");	
	initTexte(&tt,-12,985,250,250,250,"OpenSans-Bold.ttf",18);
	initTexte(&tt1,3,970,250,250,250,"Roboto-BoldItalic.ttf",20);
		 
	init_image(&per1,830,850,"p1.png");
	init_image(&per2,969,850,"p2.png");
	init_image(&per11,830,850,"p11.png");
	init_image(&per21,969,850,"p21.png");
	
	init_image(&names,1169,200,"names.png");	
		 
	init_image(&sb,0,0,"semi_black.png");
	init_image(&mg,710,400,"main game.png");
	init_image(&ttt,710,500,"tic tac toe.png");
	init_image(&bg4,0,0,"bg.jpg");
	init_image(&m1,650,0,"map1.png");
	//initialiserTic (&ti);
	Mix_PlayMusic(music,-1);
	
	initBack(&bg);
 	initBack(&bg1);
 	//Mix_PlayMusic(music,-1);
	initPerso(&perso);
	initPerso(&perso1);
	initTexte(&t,1600,5,250,250,250,"Roboto-BoldItalic.ttf",30);
	initTexte(&t1,1700,5,250,250,250,"Roboto-BoldItalic.ttf",30);
	initTexte(&t2,1780,5,250,250,250,"Roboto-BoldItalic.ttf",30);
	initVie(&img);	
	initminimap(&m);
	inittext (&t11);
        inittext2 (&t22);
        initEnemy(&e);
        animateX(&e);
        sauvegarder( sp, nom,  scores);
	meilleur( scores, &sp, nj);
	printf("  ******************************\n"); 
        printf("the best score %d belongs to %s\n",sp,nj) ;   
        printf("  ******************************\n");  
	//son = Mix_LoadWAV("jump.wav");
	while(!loop) {
	  switch(nbg) {
case 1: 
	afficher(bgg,screen);
	if(x==0) {
	afficher(a0,screen);
	afficher(a2,screen);
	x=1;}
	else { 
	afficher(a1,screen);
	afficher(a3,screen);
	x=0;}
	afficher(*p,screen);
	afficher(*s,screen);
	afficher(*c,screen);
	afficher(*q,screen);
	afficher(titre,screen);
	afficher(tunis,screen);
	afficher(usa,screen);
	afficher(uk,screen);
	afficher(logo,screen);
	afficher(logo1,screen);
	displaytexte(tt,screen,"©opyright -all rights resreved-");
	if (blbg==1)
{
afficher(sb,screen);
afficher(mg,screen);
afficher(ttt,screen);
}
else if (blbg==2)
{
afficher(sb,screen);
afficher(m1,screen);
}

	SDL_Flip(screen);
break;
case 2:  
	afficher(bgg1,screen1);
	afficher(fleche,screen1);
	afficher(*v,screen1);
	afficher(*f,screen1);
	if (np==1)
	afficher(per11,screen1);
	else
	afficher(per1,screen1);
	if (np==1)
	afficher(per2,screen1);
	else 
	afficher(per21,screen1);
	afficher(*ss[i],screen1);
	j++;
	if (j>20) {
	j=0;
	i++;}
	if (i>9) {
	i=0;
	j=-200;}
	displaytexte(tt1,screen1,"Click: m:menu, s:Settings, p:Play, c:Credit, Esc:Quit");
	SDL_Flip(screen1);
break;
case 3: 
	//afficher(bg2,screen2);
	//printf("%.0f %.0f\n",dt,dt1);
	//printf("%d\n",perso.direction);
	bg.np=np;
	//bg.lvl=lvl;
	m.lvl=lvl;
	if(lvl==1 && pl1==1 && pl2==1)
	{
	lvl=2;
	pl1=0;
	pl2=0;
	}
	printf("%d\n",h);
	duree=SDL_GetTicks();
	ii++;
	if(ii%8==0)
	{img.pos2.x+=60;
	if (img.pos2.x==300) img.pos2.x=0;}
	aficherBack(bg,screen2);
	scrolling(&bg,direction,pasAvancement);
	if (lvl==1)
	//animerBackground(&bg);
	afficherPerso(perso,screen2);
	animerPerso (&perso);
	if(np==2)
	{
	aficherBack(bg1,screen2);
	scrolling(&bg1,direction1,pasAvancement1);
	if (lvl==1)
	animerBackground(&bg1);
	afficherPerso(perso1,screen2);
	animerPerso (&perso1);
	}
	
	duree=duree/1000;
	sprintf(message, "%d", duree);
	afficheVie(img,screen2);
	displaytexte(t1,screen2,zz);
	sprintf(zz,"%d",score);
	//deplacerPerso (&perso1,dt1);
	displaytext(t11,t22,screen2,message);
	displaytexte(t,screen2,"Score: ");
	displaytexte(t2,screen2,"Vie: ");
	MAJMinimap(perso,&m,bg.pos2,redimensionnement);
	affichermap(m,screen2);  
	afficher(fleche,screen2);
	SDL_Flip(screen2);
	 
       e.hauteur=e.pos.y-perso.pos2.y;
       if (bg.pos2.x==0)
       {if(e.state==WAITING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2);
       }
       else if(e.state==FOLLOWING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2); 
       }
       else if(e.state==ATTACKING)
       {
       printf("*");
       e.folie=1;
       //accelerer(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2);
       }
       }
        else 
        if (bg.pos2.x>0)
        {
        if(e.max>0 && e.min>0)
        {
       //e.hauteur=e.pos.y-perso.pos2.y;
       if(e.state==WAITING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2);
       }
       else if(e.state==FOLLOWING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2); 
       }
       else if(e.state==ATTACKING)
      {
       printf("*");
       e.folie=1;
       //accelerer(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       displayEnemy(&e,screen2);
      }
        /*displayEnemy(&e,screen);
        moveEnnemyX(&e);*/
        }
        if(e.max>0 && e.min<0)
        {
        if(e.state==WAITING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       }
       else if(e.state==FOLLOWING)
       {
       e.folie=0;
       moveEnnemyX(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
       }
       else if(e.state==ATTACKING)
      {
       printf("*");
       e.folie=1;
       //accelerer(&e);
       IAmove(&e,perso.pos1,bg.pos2.x,b);//perso
      }
        if(e.pos.x>0)
        {
        displayEnemy(&e,screen2);
        }
        }
        }
	b=bg.pos2.x;
       if(bg.pos2.x>750)
       {SDL_FreeSurface(e.imgR);}
       /*if(perso.pos2.x==3000 && perso.pos2.y==875.1)
       {
        displayEnemy1(&e,screen2);
        moveEnnemyX1(&e);
        
       }*/
	/*if(k==0)
        {
        b=e.max;
        n=e.min;
        k++;
        }
        if(bg.pos2.x==0)
        {
        displayEnemy(&e,screen);
        moveEnnemyX(&e);
        }
        else 
        if (bg.pos2.x>0)
        {
         e.max=b-bg.pos2.x;
         e.min=n-bg.pos2.x;
        if(e.max>0 && e.min>0)
        {
        displayEnemy(&e,screen);
        moveEnnemyX(&e);
        }
        if(e.max>0 && e.min<0)
        {
        moveEnnemyX(&e);
        if(e.pos.x>0)
        {
        displayEnemy(&e,screen);
        }
        }
        }*/
	//loop=collisionBB(perso,e);
        if (loop==1)
        {
          perso.vie--;
          e.hp--;
          if (perso.vie!=0)
            {loop=0;}
          else 
            {loop=1;}
          /*if (e.hp==0)
            e.etat=1;*/
        }
	bx=bg.pos2.x+perso.pos1.x;
        by=perso.pos1.y;//372
        perso.P[0].x=bx;
        perso.P[0].y=by;
        perso.P[1].x=bx+pw/2;
        perso.P[1].y=by;
        perso.P[2].x=bx+pw;
        perso.P[2].y=by;
        perso.P[3].x=bx;
        perso.P[3].y=by+ph/2;
        perso.P[4].x=bx;
        perso.P[4].y=by+ph;
        perso.P[5].x=bx+pw/2;
        perso.P[5].y=by+ph;
        perso.P[6].x=bx+pw;
        perso.P[6].y=by+ph;
        perso.P[7].x=bx+pw;
        perso.P[7].y=by+ph/2;
	
	if (perso.dx>=-60 && perso.dx<=y )
	 perso.dx++;
	 
	if(perso.pos1.y>=865)
	 y=0; 
	else y++;
	
	if (bl2==0 &&(collisionPP(perso, surf)==2))
{
 perso.dy=perso.pos1.y;
 perso.up=0;
 //x=0;
 bl2=1;
}
	
	if (perso.up==1)
	{
	if(bl==0)
	{
	Mix_PlayChannel(-1,son1,0);
	perso.dx=-60;
	bl=1;
	 //bl2=0;
	}
	
	}
	else if(perso.up==2){
	//y=10;
	if(bl1==0){
	Mix_PlayChannel(-1,son1,0);
	perso.dy=perso.pos1.y;
	
	perso.dx=-60;
	bl1=1;
	 bl2=0;
	}
	}
	else 
	{
	bl=0;
	bl1=0;
	//perso.dy=870;
	perso.dx=1;
	  if(!((isblack(perso.P[4],surf)&&isblack(perso.P[5],surf) )|| (isblack(perso.P[5],surf)&&isblack(perso.P[6],surf))||(isblack(perso.P[4],surf)&&isblack(perso.P[5],surf)&&isblack(perso.P[6],surf) )))
         perso.dy=875;
          perso.dx=0;
	}
	if (perso.dx>=y) perso.up=0;
	if(dt>3.5)
	dt=3.5; 
	else if(dt<0)
	{
	perso.direction=0;
	dt=0;
	}
	
	if (perso1.dx>=-60 && perso1.dx<=y1 )
	 perso1.dx++;

	if(perso1.pos1.y>=865)
	 y1=0;
	else y1++;

	if (bl22==0 &&(collisionPP(perso1, surf)==2))
{
 perso1.dy=perso1.pos1.y;
 perso1.up=0;
 //x=0;
 bl22=1;
}

bx1=bg.pos2.x+perso1.pos1.x-960;
        by1=perso1.pos1.y;//372
        perso1.P[0].x=bx1;
        perso1.P[0].y=by1;
        perso1.P[1].x=bx1+pw/2;
        perso1.P[1].y=by1;
        perso1.P[2].x=bx1+pw;
        perso1.P[2].y=by1;
        perso1.P[3].x=bx1;
        perso1.P[3].y=by1+ph/2;
        perso1.P[4].x=bx1;
        perso1.P[4].y=by1+ph;
        perso1.P[5].x=bx1+pw/2;
        perso1.P[5].y=by1+ph;
        perso1.P[6].x=bx1+pw;
        perso1.P[6].y=by1+ph;
        perso1.P[7].x=bx1+pw;
        perso1.P[7].y=by1+ph/2;

	if (perso1.up==1)
	{
	if(bll==0)
	{
	Mix_PlayChannel(-1,son1,0);
	perso1.dx=-60;
	bll=1;
	 //bl22=0;
	}

	}
	else if(perso1.up==2){
	//y=10;
	if(bl11==0){
	Mix_PlayChannel(-1,son1,0);
	perso1.dy=perso1.pos1.y;

	perso1.dx=-60;
	bl11=1;
	 bl22=0;
	}
	}
	else
	{
	bll=0;
	bl11=0;
	//perso1.dy=870;
	perso1.dx=1;
	  if(!((isblack(perso1.P[4],surf)&&isblack(perso1.P[5],surf) )|| (isblack(perso1.P[5],surf)&&isblack(perso1.P[6],surf))||(isblack(perso1.P[4],surf)&&isblack(perso1.P[5],surf)&&isblack(perso1.P[6],surf) )))
         perso1.dy=875;
          perso1.dx=0;
	}
	if (perso1.dx>=y) perso1.up=0;
	if(dt1>3.5)
	dt1=3.5;
	else if(dt1<=0)
	{
	perso1.direction=0;
	dt1=0;
	}
	
	saut(&perso);
	saut(&perso1);
	/*if (keysheld[SDLK_UP])
	{
	perso.up++; 
		if(perso.up>2)
		perso.up=1;
		pasAvancement=vv;
		direction=1;
	}*/
	if (keysheld[SDLK_RIGHT])
	{
	perso.mouvement=1;
		perso.direction=1;
	}
	else if (keysheld[SDLK_LEFT])
	{
	perso.mouvement=1;
		perso.direction=-1;
	}
	else{
	perso.mouvement=0;
	}
	
	if (keysheld[SDLK_d])
	{
	perso1.mouvement=1;
	perso1.direction=1;
	}
	else if (keysheld[SDLK_a])
	{
	perso1.mouvement=1;
	perso1.direction=-1;
	}
	/*else if (keysheld[SDLK_w])
	{
	perso1.up++; 
	if(perso1.up>2)
	perso1.up=1;
	direction1=1;
	}*/
	else
	perso1.mouvement=0;
	
	
	if ((h>3500)&&(bl4==0)&&(bg.lvl==2))
	{
	printf("lol");
	bl4=1;
	bg.lvl=3;
m.lvl=3;
h=0;
initBack(&bg);
initPerso(&perso);
initminimap(&m);
initEnemy(&e);
surf=surf2;
	} 
	
	if ((h>3500)&&(bl3==0))
	{
	bl3=1;
	bg.lvl=2;
m.lvl=2;
h=0;
initBack(&bg);
initPerso(&perso);
initminimap(&m);
initEnemy(&e);
surf=surf1;
	}
	
	switch (perso.mouvement) {
		case 1:
		//printf("lol\n");
		switch (perso.direction) {
		case 1:
		//printf("lol\n");
		pasAvancement=h;
		direction=0;
                if (collisionPP(perso, surf)!=1)
		if(h<5692)
	        if (perso.pos1.x<750)
		deplacerPerso (&perso,dt);
		else
		h+=(0.5*dt*dt+dt);
	
		 if(p2==1)
		 perso.direction_animation=2;
		 else
		  perso.direction_animation=5;
		 perso.direction=1;
		// perso.pos2.y=214;
		 dt+=0.09;
		 score += SDL_GetTicks()/1000;
		
		 break;
		 case -1:
		 pasAvancement=h;
			direction=0;
			
			  if (collisionPP(perso, surf)!=-1)
			if(h>0)
			if (perso.pos1.x>20)
			deplacerPerso (&perso,dt);
			else
			h-=(0.5*dt*dt+dt);
			//h-=5; 
		 if(p2==1)
		 perso.direction_animation=1;
		 else perso.direction_animation=4;
		 perso.direction=-1;
		// perso.pos2.y=107;
		 dt+=0.09;
		
		 break;}
		 break;
		case 0: 
			//perso.pos2.y=107
			if (p2==1)
			perso.direction_animation=0;
			else perso.direction_animation=3;
			perso.pos2.x=0;
			if (dt>0)
			dt-=0.20;
			break;}
			
			switch (perso1.mouvement) {
		case 1:
		switch (perso1.direction) {
		case 1:
		pasAvancement1=h1;
		direction1=0;
               if (collisionPP(perso1, surf)!=1)
		if(h1<5692)
	        if (perso1.pos1.x<1710)
		deplacerPerso (&perso1,dt1);
		else
		h1+=(0.5*dt1*dt1+dt1);
    
		  perso1.direction_animation=5;
		 perso1.direction=1;
		
		 dt1+=0.09;
		 score += SDL_GetTicks()/1000;
		
		 break;
		 case -1:
		 pasAvancement1=h1;
			direction1=0;
			
			  if (collisionPP(perso1, surf)!=-1)
			if(h1>0)
			if (perso1.pos1.x>20)
			deplacerPerso (&perso1,dt1);
			else
			h1-=(0.5*dt1*dt1+dt1);
			//h1-=5; 
		perso1.direction_animation=4;
		 perso1.direction=-1;
		// perso1.pos2.y=107;
		 dt1+=0.09;
		
		 break;}
		 break;
		case 0: 
			//perso1.pos2.y=107
			
			 perso1.direction_animation=3;
			 perso1.pos2.x=0;
			if (dt1>0)
			dt1-=0.20;
			break;}
			
		//dt = SDL_GetTicks() - t_prev;
		//if(1000/fps>dt)
		//SDL_Delay(1000/fps-dt);
	
break;
case 4:
	afficher(bg3,screen3);
	afficher(names,screen3);
	afficher(fleche,screen3);
	SDL_Flip(screen3);
break;
case 5:
      
 	
	afficher(bg4,screen4);
	afficherTic(ti.tabsuivi,screen4,ti);
	Resultat (ti.tabsuivi,screen4,ti);
	SDL_Flip(screen4);
	//Mix_PlayMusic(music1,-1);
if((ti.tournbr<9)&&(atilganer(ti.tabsuivi)==0))
{
if((ti.tournbr+ti.player)%2==0)
{
calcul_coup(ti.tabsuivi);
ti.tournbr++;
}
else 
{
 SDL_PollEvent(&event);
if(event.type==SDL_MOUSEBUTTONUP)
{
                        x=event.button.x/133;
                         y=event.button.y/133;
                        coup=3*y+x;
                        if(ti.tabsuivi[coup]==0)
                        {
                        ti.tabsuivi[coup]=-1;
                        ti.tournbr++;
                        }
}
else if (event.key.keysym.sym==SDLK_m)
//loop=1;
{
nbg=1;
screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
Mix_PlayMusic(music,-1);
}
}
}
break;}
	while (SDL_PollEvent(&event)){
		 switch (event.type) {
		case SDL_QUIT: 
			loop = 1; 
		break;
		case SDL_KEYDOWN:
		switch (nbg)
		{ case 3:
		keysheld[event.key.keysym.sym]=1;
		switch (event.key.keysym.sym) {
		case SDLK_UP:
		perso.up++; 
		if(perso.up>2)
		perso.up=1;
		pasAvancement=vv;
		direction=1;
		break;
			case SDLK_w:
		perso1.up++; 
		if(perso1.up>2)
		perso1.up=1;
		direction1=1;
		break;
		case SDLK_DOWN:
		pasAvancement=vv;
	        direction=1;
	        //if (v<560)
		//v+=5;
	        break;
		case SDLK_RIGHT:
		perso.mouvement=1;
		perso.direction=1;
		
		break;
		case SDLK_d:
		perso1.mouvement=1;
		perso1.direction=1;
		break;
		
		case SDLK_LEFT:
		perso.mouvement=1;
		perso.direction=-1;
		break;
			case SDLK_a:
		perso1.mouvement=1;
		perso1.direction=-1;
		break;
		case SDLK_j: 
		p2=2;
		break;
		case SDLK_k: 
		p2=1;
		break;
		case SDLK_ESCAPE: 
		loop =1; 
		break;
		}
		break;
		break;
		default:
		  switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: 
				loop = 1; 
			break;
			case SDLK_k:  
				if(volume<0){
				volume=0;}
				volume--;
				switch(volume){	
					case 0 :
						Mix_PauseMusic();
						v=&v0;
					break;
					case 1 :
				 		Mix_VolumeMusic(MIX_MAX_VOLUME/10);
				 		v=&v1;
					break;
					case 2 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/5);
					break;
					case 3 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/3);
						v=&v2;
					break;
             				case 4 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/2);
					break;
					case 5 :
						Mix_VolumeMusic(MIX_MAX_VOLUME);
						v=&v3;
					break;}
			break;
			case SDLK_o:  
				if(volume>5){
				volume=5;}
				volume++;
				switch(volume){
					case 1 :
						Mix_ResumeMusic();
						v=&v1;
					break;
					case 2 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/10);
					break;
					case 3 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/5);
						v=&v2;
					break;
					case 4 :
						Mix_VolumeMusic(MIX_MAX_VOLUME/3);
					break;
					case 5 :
						Mix_VolumeMusic(MIX_MAX_VOLUME);
						v=&v3;
					break;}				
			 break;   			 	
      			 case SDLK_f: 
				screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
      			 	screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
      			 	screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN);
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
				f=&fs1; 
				z=0; 
      			 break;
      			 case SDLK_n:    
      			 	screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 	screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 	screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
				f=&fs0; 
      			 	z=1;   
      			 break;
      			 case SDLK_p:
      			 	nbg=3;
      			 	if(z==0) {
				screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
				else if (z==1){
				screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}
      			 	break;
      			 	case SDLK_s: 
      			 	nbg=2;
      			 	if(z==0) {
				screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
				else if (z==1){
				screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}
      			 break;
      			 case SDLK_m:
      			 	nbg=1;
      			 	if(z==0) {
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
				else if (z==1){
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}
				
				
      			 break;
      			 case SDLK_c:
      			 	nbg=4;
      			 	if(z==0) {
				screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
				else if (z==1){
				screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}
				
				
      			 break;
      			 
      			 
      			 }
		break;}
		case SDLK_m:
		Mix_PauseMusic();
		Mix_PlayMusic(music,-1);
		break;
		case SDL_MOUSEMOTION:
		  switch(nbg) {
			case 1:
			if (event.button.x>=771 && event.button.x<=987 && event.button.y>=400 && event.button.y<=490 && blbg==0) {
				p=&bouton_play1; 
				if (blp==0) {
				Mix_PlayChannel(-1,son,0); 
				blp=1;}}
			else if (event.button.x>=772 && event.button.x<=991 && event.button.y>=500 && event.button.y<=590 && blbg==0) {
				s=&bouton_settings1; 
				if (blp==0) {
				Mix_PlayChannel(-1,son,0); 
				blp=1;}}
			else if (event.button.x>=772 && event.button.x<=991 && event.button.y>=600 && event.button.y<=689 && blbg==0) {
				c=&bouton_credit1; 
				if (blp==0){
				Mix_PlayChannel(-1,son,0); 
				blp=1;}}
			else if (event.button.x>=770 && event.button.x<=987 && event.button.y>=700 && event.button.y<=789 && blbg==0) {
				q=&bouton_quit1; 
				if (blp==0) {
				Mix_PlayChannel(-1,son,0); 
				blp=1;}}
				else {
				 blp=0; 
				 p=&bouton_play; 
				 s=&bouton_settings; 
				 c=&bouton_credit;
				 q=&bouton_quit;}
				 break;
			 case 2:
				 if (event.button.x>=900 && event.button.x<=1014 && event.button.y>=550 && event.button.y<=664 ) {
				 afficher(cm,screen1);
				 SDL_Flip(screen1);
				 SDL_WaitEvent(&event); }
				 if (event.button.x>=900 && event.button.x<=1014 && event.button.y>=700 && event.button.y<=814 ) {
				 afficher(cm1,screen1);
				 SDL_Flip(screen1);
				 SDL_WaitEvent(&event);}
				 break;}
				break;
			case SDL_MOUSEBUTTONUP:
			switch(nbg){
			case 1:
			
			 	
				if (event.button.x>=712 && event.button.x<=1051 && event.button.y>=500 && event.button.y<=590 && blbg==1) {
			  		nbg=5; 
			  		initialiserTic (&ti);
			  		Mix_PlayMusic(music1,-1);
			  		screen4 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
			  		 blbg=0;
			  		}
			  		
			  	if (event.button.x>=772 && event.button.x<=991 && event.button.y>=500 && event.button.y<=590 && nbg==1 && blbg==0 ) {
			  		nbg=2; 
			  		if(z==0) {
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
					else if (z==1){
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}
					
			  		
			  	if (event.button.x>=770 && event.button.x<=987 && event.button.y>=700 && event.button.y<=789 && blbg==0 )  {
			 	 	loop=1; }
			  		//SDL_PollEvent(&event); 
			  		//if (blbg==2 )printf("%d %d\n",event.button.x,event.button.y); 
			  	if (event.button.x>=915 && event.button.x<=962 && event.button.y>=785 && event.button.y<=820 && blbg==2)
			  	{
			  	nbg=3;
			  	blbg=0;
			  	}
			  	
			  	if (event.button.x>=711 && event.button.x<=1047 && event.button.y>=400 && event.button.y<=490 && blbg==1)
			  	{
			  	blbg=2;
					//nbg=3; 
				 
				 }
				 else blbg=0;
				 if (event.button.x>=710 && event.button.x<=1047 && event.button.y>=400 && event.button.y<=490 && blbg==0) {
					blbg=1;
					
					if(z==0) {
					screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
			 		else if (z==1){
					screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}
					
			  	if (event.button.x>=772 && event.button.x<=991 && event.button.y>=600 && event.button.y<=689 && blbg==0) {
			 		nbg=4;
			 		if(z==0) {
					screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
				 	else if (z==1){
					screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}  
			 break;
			 case 2:
			// printf("%d %d  %d\n",event.button.x,event.button.y,np);
			 	if (event.button.x>=0 && event.button.x<=102 && event.button.y>=0 && event.button.y<=102 ) {
					nbg=1;
					if(z==0){ 
      			 		screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
      			 		screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
					else if (z==1){ 
      			 		screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 		screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}
			   	else if (event.button.x>=900 && event.button.x<=1014 && event.button.y>=550 && event.button.y<=664 ) {
			 		pr++; 
			 		if (pr % 2 == 0) {
			 		v=p1; 
			 		Mix_ResumeMusic();}
			 		SDL_PollEvent(&event); 
			 		if (pr % 2 != 0) {
			 		p1=v; 
			 		v=&v0; 
			 		Mix_PauseMusic();}
			 		//SDL_PollEvent(&event);
			 		}
			 	else if (event.button.x>=900 && event.button.x<=1014 && event.button.y>=700 && event.button.y<=814 ) {
			 		pr1++; 
			 		if (pr1 % 2 == 0) {
				screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 	screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 	screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
					f=&fs0;
					z=1;
					printf("lol\n");
			 		}
			 		//SDL_PollEvent(&event); 
			 		if (pr1 % 2 != 0){	
				screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
      			 	screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
      			 	screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN);
				screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); 
				f=&fs1; 
				z=0;
				printf("non\n");}
			 		//SDL_PollEvent(&event); 
			 		}
			 	else if (event.button.x>=833 && event.button.x<=940 && event.button.y>=850 && event.button.y<=950 )
			 		{
			 		np=1;
			 		}
			 	else if (event.button.x>=960 && event.button.x<=1077 && event.button.y>=850 && event.button.y<=950 )
			 		{
			 		np=2;
			 		}
			   break;
      			   case 3:
      			 	if (event.button.x>=0 && event.button.x<=102 && event.button.y>=0 && event.button.y<=102 ) {
					nbg=1;
					if(z==0) { 
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);  
      			 		screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF |SDL_FULLSCREEN);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
					else if (z==1){ 
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 		screen3 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}
      			   break;
      			   case 4:
      			 	if (event.button.x>=0 && event.button.x<=102 && event.button.y>=0 && event.button.y<=102 ) {
					nbg=1;
					if(z==0) {
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);  
      			 		screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
					else if (z==1){
					screen1 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
      			 		screen2 = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
					screen = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_DOUBLEBUF);}}
      			   break;
      			  /* case 5:
      			
      			   break;*/
		break; 
		
		}
		case SDL_KEYUP:
		keysheld[event.key.keysym.sym]=0;
		//if(event.key.keysym.sym!=SDLK_UP)
		//perso.mouvement=0;
		//if(event.key.keysym.sym!=SDLK_w)
		//perso1.mouvement=0;
		break;
		
		//default: 
		//perso.mouvement=0;
		//perso1.mouvement=0;
		 } }}
	liberer(bgg);
	liberer(bgg1);
	liberer(bg2);
	liberer(bg3);
	liberer(logo);
	liberer(logo1);
	liberer(cm);
	liberer(cm1);
	liberer(a0);
	liberer(a2);
	liberer(a1);
	liberer(a3);
	liberer(fs0);
	liberer(fs1);
	liberer(titre);
	liberer(bouton_play);
	liberer(bouton_play1);
	liberer(bouton_settings);
	liberer(bouton_settings1);
	liberer(bouton_credit);
	liberer(bouton_credit1);
	liberer(bouton_quit);
	liberer(bouton_quit1);
	liberer(fleche);
	liberer(tunis);
	liberer(usa);
	liberer(uk);
	liberer(v0);
	liberer(v1);
	liberer(v2);
	liberer(v3);
	liberer(s0);
	liberer(s1);
	liberer(s2);
	liberer(s3);
	liberer(s4);
	liberer(s5);
	liberer(s6);
	liberer(s7);
	liberer(s8);
	liberer(s9);
	liberer(sb);
	liberer(mg);
	liberer(names);
	liberer(ttt);
	liberer(m1);
	liberer(per1);
	liberer(per2);
	liberer(per11);
	liberer(per21);
	liberer(bg4);
	liberer_tic(ti);
	freeTexte1(tt,tt1);
	TTF_CloseFont(tt.font);
	TTF_CloseFont(ti.font);
	
	
	Mix_FreeChunk(son);
	Mix_FreeMusic(music); 
	Mix_FreeMusic(music1); 
	liberer2(bg);
	liberer2(bg1);
        SDL_FreeSurface(e.imgR);
	Mix_FreeMusic(music);
	liberer(img);
	liberer1(perso);
	liberer1(perso1);
	freeTexte(t);
	TTF_CloseFont(t.font);
	freeTexte(t1);
	TTF_CloseFont(t1.font);
	freeTexte(t2);
	TTF_CloseFont(t2.font);
	liberer22(m);
	freetext(t11);
	freetext(t22);
	TTF_CloseFont(t11.font);
	TTF_CloseFont(t22.font);
	Mix_FreeChunk(son);
	Mix_FreeChunk(son1);
	TTF_Quit();
	return 0; }
