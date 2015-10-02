
#include "SDL.h"
#include "sprite.cpp"
#include "enemy.cpp"
#include "tiles.cpp"

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_WIDTH  50
#define SPRITE_HEIGHT     128
#define CAMERA_SPEED 1
#define NBPLAYERS 1

int gameover;
unsigned int oldtime = 10000000;
int level = 1;
int levelover = 0;

/* source and destination rectangles */
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
      if ( hero->rc_image.x < 2*SPRITE_WIDTH )
	hero->rc_image.x = 2*SPRITE_WIDTH;
      if ( hero->rc_image.x == 3*SPRITE_WIDTH )
	hero->rc_image.x = 2*SPRITE_WIDTH;
      else
	hero->rc_image.x += SPRITE_WIDTH;
    }

    if(key[tabkey[i][2]]) { //RIGHT
      if ( hero->rc_image.x > SPRITE_WIDTH )
	hero->rc_image.x = 0;
      if ( hero->rc_image.x == SPRITE_WIDTH )
	hero->rc_image.x = 0;
      else
	hero->rc_image.x += SPRITE_WIDTH;
    }
  }
}	       

int main(int argc, char** argv)
{
  SDL_Surface *screen,*temp,*tileset;
  enemy_type robot_enemy_1, robot_enemy_2;
  list_of_enemy enemy_list, enemy_list_copy;

  gameover = 0;

  while (!gameover){
    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(TAILLE_TUILE*NB_BLOCS_LARGEUR, TAILLE_TUILE*NB_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    //load tileset
    temp = SDL_LoadBMP("tileset.bmp");
    tileset = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

   
    
    /* set keyboard repeat */
    SDL_EnableKeyRepeat(70, 70);

    /* load sprite */
    temp = SDL_LoadBMP("sprite.bmp");
    hero->sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);   

    /* create list of new enemy */
    enemy_list = create_new_list_of_enemy();
    robot_enemy_1 = create_new_enemy('R',screen, 250, 200, 0);
    robot_enemy_2 = create_new_enemy('R',screen, 200, 200, 0);
    enemy_list = cons(robot_enemy_1, enemy_list);
    enemy_list = cons(robot_enemy_2, enemy_list);

    /* setup sprite colorkey and turn on RLE */
    hero->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
    SDL_SetColorKey(hero->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, hero->colorkey);
  
    /* set sprite position */
    hero->coord.x = hero->x = 300;
    hero->coord.y = hero->y = 700;

    /* set animation frame */
    hero->rc_image.x = 0;
    hero->rc_image.y = 0;
    hero->rc_image.w = SPRITE_WIDTH;
    hero->rc_image.h = SPRITE_HEIGHT;

    levelover = 0;

    char key[SDLK_LAST]= {0};

    /* message pump */
    while (!levelover&&!gameover)
      {
	SDL_Event event;
		
	/* look for an event */
	// fonction affichage
	Afficher(screen,tileset,table,NB_BLOCS_LARGEUR,NB_BLOCS_HAUTEUR);

	HandleEvent(key, screen);
	update_events(key);
      
	jump(hero, SDL_GetTicks(), oldtime); // jumps only if oldtime < SDLGetTicks() so if u press up */
	reload_pos(hero);

	/* collide with edges of screen */
	if (hero->coord.x <= 0)
	  hero->coord.x = 0;
	if (hero->coord.x >= SCREEN_WIDTH - SPRITE_WIDTH) 
	  hero->coord.x = SCREEN_WIDTH - SPRITE_WIDTH;

	if (hero->coord.y <= 0)
	  hero->coord.y = 0;
	if (hero->coord.y >= SCREEN_HEIGHT - SPRITE_HEIGHT) 
	  hero->coord.y = SCREEN_HEIGHT - SPRITE_HEIGHT;

	/* draw the sprite */
	SDL_BlitSurface(hero->sprite, &hero->rc_image, screen, &hero->coord);

	/* draw the enemy sprite */
	enemy_list_copy = enemy_list;
	while (enemy_list_copy != NULL){
	  SDL_BlitSurface(enemy_list_copy->first->sprite, &enemy_list_copy->first->rc_image, screen, &enemy_list_copy->first->coord);
	  enemy_list_copy = enemy_list_copy->rest;
	}

	/* update the screen */
	SDL_UpdateRect(screen, 0, 0, 0, 0);
      }
  }
  /* clean up */
  SDL_FreeSurface(hero->sprite);
  SDL_FreeSurface(enemy_list->first->sprite);
  SDL_FreeSurface(tileset);
  SDL_Quit();

  return 0;
}
