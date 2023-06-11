/**
 * @file main.c
 * @author ons ghariani (you@domain.com)
 * @brief main file 
 * @version 0.1
 * @date 2023-05-12
 * 
 * @copyright esprit (c) 2023
 * 
 */
#include "enigme5.h"
int main(int argc, char *argv[])
{
 
    Uint32 t_prev2, t_prev1, t_prev3;
    int score = 100;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();
    
      SDL_Surface *screen;
  screen = SDL_SetVideoMode(530, 652, 16, SDL_SWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "Unable to set video mode: %s\n", SDL_GetError());
        return 1;
    }
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000) == -1)
    {
        printf("Error opening audio: %s\n", Mix_GetError());
        return 1;
    }
    Mix_Music *music = Mix_LoadMUS("src/music/Grieg - In the Hall of the Mountain King.mp3");
    Mix_Music *music_win = Mix_LoadMUS("src/music/Grieg - In the Hall of the Mountain King.mp3");
    if (!music)
    {
        printf("Error loading sound: %s\n", Mix_GetError());
        return 1;
    }
    Mix_PlayMusic(music, 1); 

    
    SDL_WM_SetCaption("SDL Game", NULL);

    
    SDL_Event event;
    int done = 0;
    
    Enigme e;
    e.selected = -1;
    int one = 0;

    geneerEnigme(&e, "src/questions.txt");
    initilisationimagebackground(&e.background);
   

    initilisation_animation(&e.anim);
    e.anim.screen = screen;
    

    Mix_VolumeMusic(60);
    int diplayscore = 0;
    int newscore = 0;
    
        
    
           perso p, p2;
  p.current_level = 2;
  p.hp = 2;
  strcpy(p.name, "ons");
  p.score = 400;
  background b, b2;
  b.x_pos = 6000;
  b.y_pos = 0;    
      load(&p2, &b2, "src/load and save/save.txt", "ons");
          
          printf("name: %s\n", p2.name);
          printf("HP: %d\n", p2.hp);
          printf("Score: %d\n", p2.score);
          printf("Current level: %d\n", p2.current_level);
          printf("X position: %d\n", b2.x_pos);
          printf("Y position: %d\n", b2.y_pos);
          
savegame(p, b, "src/load and save/save.txt");   
    while (!done)
    { 
        if (SDL_GetTicks() - t_prev1 > 2000) 
        {
            if (e.solved != 0)
            {
                diplayscore = 1;
            }
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
            afficherEnigme(e, screen);

              animerpuzzle(&e);
            t_prev1 = SDL_GetTicks();
        }

        if (e.solved != 0 && SDL_GetTicks() - t_prev3 > 20 || diplayscore == 1)
        {

            afficherEnigme(e, screen);
            if (e.solved == 1 && score != newscore)
            {
                score++;
            }
            else if (e.solved != 1 && score != newscore)
            {
                score--;
            }
            afficher_newscore(score, screen, e.newscore);

            t_prev3 = SDL_GetTicks();
        }
        // Process events
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    if ((e.selected + 1) == e.solution)
                    {
                        e.solved = 1;
                        newscore = score + 100;
                    }
                    else
                    {
                        e.solved = 2;
                        if (score > 100)
                            newscore = score - 100;
                    }
                    break;
                case SDLK_ESCAPE:
                    done = 1;
                    break;
                case SDLK_UP:
                   if (SDL_GetTicks() - t_prev2 > 150 && e.solved == 0) 
                    {
                        e.selected = next_button(e.selected, 0, 2);
                        afficherEnigme(e, screen);
                        t_prev2 = SDL_GetTicks();
                    }
                    break;
                case SDLK_DOWN:
                    if (SDL_GetTicks() - t_prev2 > 150 && e.solved == 0) 
                    {
                        e.selected = next_button(e.selected, 2, 2);
                        afficherEnigme(e, screen);
                        t_prev2 = SDL_GetTicks();
                    }
                    break;
                }
                break;
                                 case SDL_MOUSEMOTION:
      if (e.selected != 0 && event.motion.x >= 87   && event.motion.x <= 428  && event.motion.y >= 212&& event.motion.y <= 292)
        {
          e.selected = 0;
                        afficherEnigme(e, screen);
        }  
        
        else if (e.selected != 1 && event.motion.x >= 87   && event.motion.x <= 643   && event.motion.y >= 325 && event.motion.y <= 408 )
        {
          e.selected = 1;
                        afficherEnigme(e, screen);
        }
        // bt_quit
        else if (e.selected != 2 && event.motion.x >= 87   && event.motion.x <= 643   && event.motion.y >= 429  && event.motion.y <= 509 )
        {
          e.selected = 2;
                        afficherEnigme(e, screen);
        }
        else

            if (e.selected != -1 && !(event.motion.x >= 87   && event.motion.x <= 643   && event.motion.y >= 212 && event.motion.y <= 292) && !(event.motion.x >= 87   && event.motion.x <= 643   && event.motion.y >= 325 && event.motion.y <= 408 ) && !(event.motion.x >= 87   && event.motion.x <= 643   && event.motion.y >= 429  && event.motion.y <= 509 ))
        {
          e.selected = -1;
                        afficherEnigme(e, screen);
        } 
        break;
              case SDL_MOUSEBUTTONDOWN:

if ((e.selected + 1) == e.solution)
                    {
                        e.solved = 1;
                        newscore = score + 100;
                    }
                    else
                    {
                        e.solved = 2;
                        if (score > 100)
                            newscore = score - 100;
                    }

        break;
            }
        }

        SDL_Flip(screen);
    }
    // Clean up SDL
    SDL_Quit();

    return 0;
}
