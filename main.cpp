#include "SDL.h"
#include "sprite.cpp"
#include "enemy.cpp"
#include "level.cpp"
#include "affichage.cpp"
#include "collision.cpp"

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define SPRITE_WIDTH  50
#define SPRITE_HEIGHT 128
#define NBPLAYERS 1

int gameover = 0;
unsigned int oldtime = 10000000;
int level = 0;
int levelover = 0;
int time_j = -730;

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

void HandleEvent(char* key, SDL_Surface *screen, int *time_j)
{
  SDLKey tabkey[NBPLAYERS][3] = {SDLK_UP, SDLK_LEFT, SDLK_RIGHT};
  int i;
  for (i=0; i<NBPLAYERS; i++){
    /*if (SDL_GetTicks() - *time_j > 730) {
     *time_j = SDL_GetTicks(); NE PAS DELETE */	    	    
      if(key[tabkey[i][0]]) { //UP
	oldtime = SDL_GetTicks();
      }
      //}
      
    if(key[tabkey[i][1]]) { //LEFT
      /* Movement sprite*/
      if ( hero->rc_image.x < 2*SPRITE_WIDTH )
	hero->rc_image.x = 2*SPRITE_WIDTH;
      if ( hero->rc_image.x == 3*SPRITE_WIDTH )
	hero->rc_image.x = 2*SPRITE_WIDTH;
      else
	hero->rc_image.x += SPRITE_WIDTH;
      /* Deplacement*/
      if (hero->x >= 0){
	hero->x -= 0.1;
	if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2)
	  hero->x += 0.1;
      
      }
    }
    
    if(key[tabkey[i][2]]) { //RIGHT
      if ( hero->rc_image.x > SPRITE_WIDTH )
	hero->rc_image.x = 0;
      if ( hero->rc_image.x == SPRITE_WIDTH )
	hero->rc_image.x = 0;
      else
	hero->rc_image.x += SPRITE_WIDTH;
      
      hero->x += 0.1;
      if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2)
	hero->x -= 0.1;
      
      
    }
  }
}	       

int main(int argc, char** argv)
{
  SDL_Surface *screen,*temp,*tileset;
  object_type robot_enemy_1, robot_enemy_2, mini_champi_enemy_1, mini_champi_enemy_2;
  object_type life_1,life_2,life_3;
  list_of_object enemy_list, enemy_list_copy,enemy_list_prev;
  list_of_object life_of_hero_list, life_of_hero_list_copy;
  int past_time_enemy, present_time_enemy;
  int invulnerable_time = -1500, invulnerable_time2 = -1500;

  /* set sprite position */
  hero->coord.x = hero->x = 0;
  hero->coord.y = hero->y = 300;
  //On défini ça ici parce que sinon il revient à la meme position à chaque changement de niveau
  /* set animation frame */
  hero->rc_image.x = 0;
  hero->rc_image.y = 0;
  hero->rc_image.w = SPRITE_WIDTH;
  hero->rc_image.h = SPRITE_HEIGHT;


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
    enemy_list = create_new_list_of_object();
    robot_enemy_1 = create_new_object('G',screen, 250, 200);
    robot_enemy_2 = create_new_object('G',screen, 200, 200);
    mini_champi_enemy_1 = create_new_object('C',screen, 700, 250);
    mini_champi_enemy_2 = create_new_object('C',screen, 750, 250);
    enemy_list = cons(robot_enemy_1, enemy_list);
    enemy_list = cons(robot_enemy_2, enemy_list);
    enemy_list = cons(mini_champi_enemy_1, enemy_list);
    enemy_list = cons(mini_champi_enemy_2, enemy_list);

    /* create list of new hero lives */
    life_of_hero_list = create_new_list_of_object();
    life_1 = create_new_object('L',screen, 5, 5);
    life_2 = create_new_object('L',screen, 35, 5);
    life_3 = create_new_object('L',screen, 65, 5);
    life_of_hero_list = cons(life_1, life_of_hero_list);
    life_of_hero_list = cons(life_2, life_of_hero_list);
    life_of_hero_list = cons(life_3, life_of_hero_list);

      
    /* setup sprite colorkey and turn on RLE */
    hero->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
    SDL_SetColorKey(hero->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, hero->colorkey);
	  
    levelover = 0;
    past_time_enemy =SDL_GetTicks();


    char key[SDLK_LAST]= {0};
 
					    
    /* message pump */
    while (!levelover&&!gameover)
      {
	SDL_Event event;
	  
	// fonction affichage

	Afficher(screen,tileset,table[level],NB_BLOCS_HAUTEUR, NB_BLOCS_LARGEUR);
	   
	HandleEvent(key, screen, &time_j);
	update_events(key);
      
	jump(hero, SDL_GetTicks(), oldtime, table[level]); // jumps only if oldtime < SDLGetTicks() so if u press up */
	reload_pos(hero);

	CheckLevel(hero, table[level], &level, &levelover, screen);

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
	enemy_list_prev = NULL;
	enemy_list_copy = enemy_list;
	while (enemy_list_copy != NULL){
	  printf("%p \n", enemy_list_copy->first);
	  SDL_BlitSurface(enemy_list_copy->first->sprite, &enemy_list_copy->first->rc_image, screen, &enemy_list_copy->first->coord);
	  if (Collision_H_E(hero, enemy_list_copy->first) == 2) {
	    if (SDL_GetTicks()-invulnerable_time > 1500) {
	      invulnerable_time = SDL_GetTicks();
	      if (life_of_hero_list != NULL){
		life_of_hero_list = life_of_hero_list -> rest;
	      }
	    
	      if (life_of_hero_list == NULL){
		printf("Gameover\n");
		gameover = 1;
	      }

	      printf("Moins une vie\n");
	    }

	  }

	  
	  present_time_enemy = SDL_GetTicks();
	  /* deplacement of the enemy */
	  if (((present_time_enemy - past_time_enemy)/6000)%2 == 0){
	    deplacement_object(enemy_list_copy->first,'L');
	    /* deplacement sprite enemy */
	    enemy_list_copy->first->rc_image.x = enemy_list_copy->first->rc_image.x + enemy_list_copy->first->rc_image.w;
	    if(enemy_list_copy->first->rc_image.x == 2 * enemy_list_copy->first->rc_image.w || enemy_list_copy->first->rc_image.x == 4 * enemy_list_copy->first->rc_image.w ){
	      enemy_list_copy->first->rc_image.x = 0;
	    }
	  } else {
	    deplacement_object(enemy_list_copy->first,'R');
	    /* deplacement sprite enemy */
	    enemy_list_copy->first->rc_image.x = enemy_list_copy->first->rc_image.x + enemy_list_copy->first->rc_image.w;
	    if(enemy_list_copy->first->rc_image.x == 4 * enemy_list_copy->first->rc_image.w){
	      enemy_list_copy->first->rc_image.x = 2 * enemy_list_copy->first->rc_image.w;
	    }
	  }

	  if (Collision_H_E(hero, enemy_list_copy->first) == 1) {
	    free(enemy_list_copy->first);
	    if (NULL!=enemy_list_prev) {
	      enemy_list_prev->rest = enemy_list_copy->rest;
	    } else {
	      enemy_list = enemy_list->rest;
	    }
	    free(enemy_list_copy);
	    enemy_list_copy = enemy_list_prev;
	  }




	  enemy_list_prev = enemy_list_copy;
	  enemy_list_copy = enemy_list_copy->rest;
	}    
	/* draw the hero lives sprite */
	life_of_hero_list_copy = life_of_hero_list;
	while (life_of_hero_list_copy != NULL){
	  SDL_BlitSurface(life_of_hero_list_copy->first->sprite, &life_of_hero_list_copy->first->rc_image, screen, &life_of_hero_list_copy->first->coord);
	  life_of_hero_list_copy = life_of_hero_list_copy->rest;
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

