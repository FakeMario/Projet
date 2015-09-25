
#include "SDL.h"
#include "sprite.cpp"
#include "enemy.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE     128
#define CAMERA_SPEED 1
#define NBPLAYERS 1

int gameover;
unsigned int oldtime = 10000000;
bool jumping = false;
int level = 1;
int levelover = 0;

/* source and destination rectangles */
SDL_Rect camera;
pt_sprite hero = (pt_sprite) malloc (sizeof(s_sprite));

void update_events(char*keys);
void HandleEvent(char* key, SDL_Surface *screen);

void update_events(char* keys){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
    case SDL_QUIT:
      gameover = 1;
      break;

    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;
      
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym){
      case SDLK_ESCAPE:
	gameover = 1;
	break;
      }
      keys[event.key.keysym.sym]=1;
      break;
    }
  }
}

void HandleEvent(char* key, SDL_Surface *screen)
{
  SDLKey tabkey[NBPLAYERS][3] = {SDLK_UP, SDLK_LEFT, SDLK_RIGHT};
  int i;
  for (i=0; i<NBPLAYERS; i++){
    if(key[tabkey[i][0]]) { //UP
      oldtime = SDL_GetTicks();
    }
    
    if(key[tabkey[i][1]]) { //LEFT
      if ( hero->rc_image.x < 2*SPRITE_SIZE )
	hero->rc_image.x = 2*SPRITE_SIZE;
      if ( hero->rc_image.x == 3*SPRITE_SIZE )
	hero->rc_image.x = 2*SPRITE_SIZE;
      else
	hero->rc_image.x += SPRITE_SIZE;
      camera.x -= CAMERA_SPEED;
      if (camera.x <= 0)
	camera.x = 2000-640;
    }

    if(key[tabkey[i][2]]) { //RIGHT
      if ( hero->rc_image.x > SPRITE_SIZE )
	hero->rc_image.x = 0;
      if ( hero->rc_image.x == SPRITE_SIZE )
	hero->rc_image.x = 0;
      else
	hero->rc_image.x += SPRITE_SIZE;

      camera.x += CAMERA_SPEED;
    }
  }
}	       

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *background;
  SDL_Rect rcBackground;
  enemy_type robot_enemy;
  list_of_enemy enemy_list;

  gameover = 0;

  while (!gameover){
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);

  /* load sprite */
  temp = SDL_LoadBMP("sprite.bmp");
  hero->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* load background */
  switch(level){
  case 1:
    temp  = SDL_LoadBMP("background.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    break;
  case 2:
    temp = SDL_LoadBMP("background2.bmp");
    background = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    break;
    levelover = 0;
  }

  /* create list of new enemy */
  enemy_list = create_new_list_of_enemy();
  robot_enemy = create_new_enemy('R',screen);
  enemy_list = cons(robot_enemy, enemy_list);

  /* setup sprite colorkey and turn on RLE */
  hero->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(hero->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, hero->colorkey);
  
  /* set sprite position */
  hero->coord.x = hero->x = 300;
  hero->coord.y = hero->y = 335;

  /* set animation frame */
  hero->rc_image.x = 0;
  hero->rc_image.y = 0;
  hero->rc_image.w = SPRITE_SIZE;
  hero->rc_image.h = SPRITE_SIZE;

  /* Init camera (point of view) */
  camera.h = SCREEN_HEIGHT;
  camera.w = SCREEN_WIDTH;
  camera.x = 0;
  camera.y = 0;

  levelover = 0;

  char key[SDLK_LAST]= {0};

  /* message pump */
  while (!levelover&&!gameover)
    {
      SDL_Event event;
		
      /* look for an event */

      HandleEvent(key, screen);
      update_events(key);
      
      jump(hero, SDL_GetTicks(), oldtime); // jumps only if oldtime < SDLGetTicks() so if u press up */
      reload_pos(hero);

      /* collide with edges of screen */
      if (hero->coord.x <= 0)
	hero->coord.x = 0;
      if (hero->coord.x >= SCREEN_WIDTH - SPRITE_SIZE) 
	hero->coord.x = SCREEN_WIDTH - SPRITE_SIZE;

      if (hero->coord.y <= 0)
	hero->coord.y = 0;
      if (hero->coord.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
	hero->coord.y = SCREEN_HEIGHT - SPRITE_SIZE;

      // Next level when we are at the end of the screen
      if (camera.x >= 2000-SCREEN_WIDTH){
	levelover = 1;
	camera.x = 0;
	level ++;
      }
      
      SDL_BlitSurface(background, &camera, screen, NULL);

      /* draw the sprite */
      SDL_BlitSurface(hero->sprite, &hero->rc_image, screen, &hero->coord);

      /* draw the enemy sprite */
      SDL_BlitSurface(enemy_list->first->sprite, &enemy_list->first->rc_image, screen, &enemy_list->first->coord);

      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
  }
  /* clean up */
  SDL_FreeSurface(hero->sprite);
  SDL_FreeSurface(enemy_list->first->sprite);
  SDL_FreeSurface(background);
  SDL_Quit();

  return 0;
}
