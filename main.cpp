#include "SDL.h"
#include <time.h>
#include "sprite.cpp"
#include "enemy.cpp"
#include "level.cpp"
#include "affichage.cpp"
#include "collision.cpp"

#define TAILLE_TUILE 32
#define NB_BLOCS_HAUTEUR 24
#define NB_BLOCS_LARGEUR 32
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define SPRITE_WIDTH  24
#define SPRITE_HEIGHT 62
#define NBPLAYERS 1

int gameover = 0;
unsigned int oldtime = 10000000;
int level = 0;
int levelover = 0;
int hero_choice = 1;

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
      case SDLK_KP1:
	if (level == 0){
	  levelover = 1;
	  level += 1;
	  hero_choice = 1;
	}
	break;
      case SDLK_KP2:
	if (level == 0){
	  levelover = 1;
	  level += 1;
	  hero_choice = 2;
	    }
	break;
      case SDLK_KP3:
	if (level == 0){
	  levelover = 1;
	  level += 1;
	  hero_choice = 3;
	}
	break;
      case SDLK_KP4:
	if (level == 0){
	  levelover = 1;
	  level += 1;
	  hero_choice = 4;
	}
	break;
      }
      keys[event.key.keysym.sym]=1;
      break;
    }
  }
}

void HandleEvent(char* key, SDL_Surface *screen)
{
  SDLKey tabkey[NBPLAYERS][4] = {SDLK_UP, SDLK_LEFT, SDLK_RIGHT};
  int i;
  for (i=0; i<NBPLAYERS; i++){
    hero->y += 3.0; /* pour calculer si collision avec bloc en dessous */
    if((collision_hero_decor(hero, table[level]))!=0) { /* on autorise appui sur haut si perso pas dans le ciel ou si il a droit au double saut */
      if(key[tabkey[i][0]]) { //UP
	oldtime = SDL_GetTicks();
      }
    }
    hero->y -= 3.0; /* reprend sa pos */

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
      hero->x -= 1.5;
      if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2)
	hero->x += 1.5;
      
    }
  }
    
  if(key[tabkey[i][2]]) { //RIGHT
    if ( hero->rc_image.x > SPRITE_WIDTH )
      hero->rc_image.x = 0;
    if ( hero->rc_image.x == SPRITE_WIDTH )
      hero->rc_image.x = 0;
    else
      hero->rc_image.x += SPRITE_WIDTH;
      hero->x += 1.5;
      if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2)
	hero->x -= 1.5; 
      
  }
  
  
  }
}	       

int main(int argc, char** argv)
{
  SDL_Surface *screen,*temp,*tileset;
  object_type ghost_enemy_1, ghost_enemy_2, mini_champi_enemy_1, mini_champi_enemy_2, mini_champi_enemy_3, robot_enemy_1, missile_enemy_1;
  object_type life_1,life_2,life_3;
  list_of_object enemy_list, enemy_list_copy,enemy_list_prev;
  list_of_object life_of_hero_list, life_of_hero_list_copy;
  int past_time_enemy, present_time_enemy, time_axe = 0;
  int invulnerable_time = -1500, invulnerable_time2 = -1500;
  int sleep_time = 0;
  char direction = 'R', direction_rob = 'R';


  /* set sprite position */
  hero->coord.x = hero->x = TAILLE_TUILE + 1;
  hero->coord.y = hero->y = SCREEN_HEIGHT - SPRITE_HEIGHT - TAILLE_TUILE - 1;
  //On défini ça ici parce que sinon il revient à la meme position à chaque changement de niveau
  /* set animation frame */
  hero->rc_image.x = 0;
  hero->rc_image.y = 0;
  hero->rc_image.w = SPRITE_WIDTH;
  hero->rc_image.h = SPRITE_HEIGHT;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");

  /* create window */
  screen = SDL_SetVideoMode(TAILLE_TUILE*NB_BLOCS_LARGEUR, TAILLE_TUILE*NB_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

 
    
  while (!gameover){
    //load tileset
    temp = SDL_LoadBMP("tileset.bmp");
    tileset = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    
    /* set keyboard repeat */
    SDL_EnableKeyRepeat(70, 70);

    /* load sprite */
    switch (hero_choice){
    case 1:
      temp = SDL_LoadBMP("sprite.bmp");
      hero->sprite = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);   
      break;
    case 2:
      temp = SDL_LoadBMP("sprite_1.bmp");
      hero->sprite = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);   
      break;
    case 3:
      temp = SDL_LoadBMP("sprite_2.bmp");
      hero->sprite = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);   
      break;
    case 4:
      temp = SDL_LoadBMP("sprite_3.bmp");
      hero->sprite = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);   
      break;
    }

    // Eliminer les ennemis qu'on n'a pas tué quand on change de tableau
    if (enemy_list != NULL){
      enemy_list = NULL;
      free(enemy_list);
    }

    /* create list of new enemy */

    switch (level) {
    case 1 : //1st level
      //enemy_list = create_new_list_of_object();
      ghost_enemy_1 = create_new_object('G',screen, 200, 152, 'L');
      ghost_enemy_2 = create_new_object('G',screen, 1000, 280, 'L');
      mini_champi_enemy_1 = create_new_object('C',screen, 700, 684, 'L');
      mini_champi_enemy_2 = create_new_object('C',screen, 725, 684, 'L');
      mini_champi_enemy_3 = create_new_object('C',screen, 750, 684, 'L');
      robot_enemy_1 = create_new_object('S',screen, 350, 405, 'L');
      missile_enemy_1 = create_new_object('H',screen, 1024, 410, 'L');
      enemy_list = cons(ghost_enemy_1, enemy_list);
      enemy_list = cons(ghost_enemy_2, enemy_list);
      enemy_list = cons(mini_champi_enemy_1, enemy_list);
      enemy_list = cons(mini_champi_enemy_2, enemy_list);
      enemy_list = cons(mini_champi_enemy_3, enemy_list);
      enemy_list = cons(robot_enemy_1, enemy_list);
      enemy_list = cons(missile_enemy_1, enemy_list);

      /* create list of new hero lives */
      life_of_hero_list = create_new_list_of_object(); 
      life_1 = create_new_object('L',screen, 5, 5, 'L');
      life_2 = create_new_object('L',screen, 35, 5, 'L');
      life_3 = create_new_object('L',screen, 65, 5, 'L');
      life_of_hero_list = cons(life_1, life_of_hero_list);
      life_of_hero_list = cons(life_2, life_of_hero_list);
      life_of_hero_list = cons(life_3, life_of_hero_list);
      break;
    case 2 : //2nd level
      //enemy_list = create_new_list_of_object();
      ghost_enemy_1 = create_new_object('G',screen, 200, 152, 'L');
      enemy_list = cons(ghost_enemy_1, enemy_list);
      break;
    }
   
      
    /* setup sprite colorkey and turn on RLE */
    hero->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
    SDL_SetColorKey(hero->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, hero->colorkey);
	  
    levelover = 0;
    past_time_enemy =SDL_GetTicks();

    char key[SDLK_LAST]= {0};
 
					    
    /* message pump */
    while (!levelover&&!gameover) {
      SDL_Event event;
	  
      // fonction affichage
      Afficher(screen,tileset,table[level],NB_BLOCS_HAUTEUR, NB_BLOCS_LARGEUR);
	  
      if(!level)
	afficher_menu(screen);

      HandleEvent(key, screen);
      update_events(key);
      
      jump(hero, SDL_GetTicks(), oldtime, table[level], life_of_hero_list, screen); // jumps only if oldtime < SDLGetTicks() so if u press up */
      reload_pos(hero);

      CheckLevel(hero, table[level], &level, &levelover, screen);

      /* collide with edges of screen */
      Collision_screen_hero(hero);

      /* draw the sprite */
      if (level > 0 && level < 6){
	SDL_BlitSurface(hero->sprite, &hero->rc_image, screen, &hero->coord);
      }

      /* draw the enemy sprite */
      enemy_list_prev = NULL;
      enemy_list_copy = enemy_list;
      while (enemy_list_copy != NULL){
	SDL_BlitSurface(enemy_list_copy->first->sprite, &enemy_list_copy->first->rc_image, screen, &enemy_list_copy->first->coord);
	present_time_enemy = SDL_GetTicks();

	if ((SDL_GetTicks()-time_axe > 8000)&&(level==1)) {
	  time_axe = SDL_GetTicks();
	  enemy_list = cons(create_new_object('H',screen, 200, 410, 'R'), enemy_list);
	}

	/* deplacement of the enemy */
	if (enemy_list_copy->first->type == 'C'){ /*mini-champi*/
	  if (((present_time_enemy - past_time_enemy)/2500)%2 == 0){
	    direction = 'R';
	  } else {
	    direction = 'L';    
	  }
	  deplacement_object(enemy_list_copy->first,&direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'G'){ /*ghost*/
	  if (((present_time_enemy - past_time_enemy)/8500)%2 == 0){
	    direction = 'L';
	  } else {
	    direction = 'R';    
	  }
	  deplacement_object(enemy_list_copy->first,&direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'H'){ /*hache*/
	  deplacement_object(enemy_list_copy->first,&enemy_list_copy->first->direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'S' /*|| enemy_list_copy->first->type == 'M'*/){ /*Squarel*/
	  pt_sprite enemy = convert_enemy_type_to_pt_spite (enemy_list_copy->first);
	  if(0==collision_hero_decor(enemy, table[level])) {
	    pt_sprite temp_pos = enemy; 
	    temp_pos->x = enemy->x + 16; /* regarde tuile à droite */
	    temp_pos->y = enemy->y;
	      
	    direction_rob = dir(temp_pos, table[level]); /* si tuile à droite vide : va à gauche */
	  }
	  deplacement_object(enemy_list_copy->first, &direction_rob, table[level]);
	}

	Collision_screen_enemy(enemy_list_copy->first);
	if (Collision_H_E(hero, enemy_list_copy->first) == 2) {
	  if (SDL_GetTicks()-invulnerable_time > 1500) {
	    invulnerable_time = SDL_GetTicks();
	    if (life_of_hero_list != NULL){
	      life_of_hero_list = life_of_hero_list -> rest;
	    }
	    
	    if (life_of_hero_list == NULL){
	      levelover = 1;
	      level = 7;
	    }
	  }
	}
	if (Collision_H_E(hero, enemy_list_copy->first) == 1 || enemy_list_copy->first->type == 'H' && enemy_list_copy->first->x <=-50){
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
	if (enemy_list_copy != NULL)
	  enemy_list_copy = enemy_list_copy->rest;
      }

      /* draw the hero lives sprite */
      life_of_hero_list_copy = life_of_hero_list;
      while (life_of_hero_list_copy != NULL && level > 0 && level < 7){
	SDL_BlitSurface(life_of_hero_list_copy->first->sprite, &life_of_hero_list_copy->first->rc_image, screen, &life_of_hero_list_copy->first->coord);
	life_of_hero_list_copy = life_of_hero_list_copy->rest;
      }



      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);

      //régulation du rythme du programme
      if (SDL_GetTicks()-sleep_time > 20) {
	sleep_time = SDL_GetTicks();
      } else { 
	SDL_Delay(20 - (SDL_GetTicks() - sleep_time));
      }	      
    }
  }

  /* clean up */
  SDL_FreeSurface(hero->sprite);
  if (enemy_list != NULL)
    SDL_FreeSurface(enemy_list->first->sprite);
  SDL_FreeSurface(tileset);
  SDL_Quit();

  return 0;
}

