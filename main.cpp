#include "SDL.h"
#include "SDL_ttf.h"
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
unsigned int oldtime = 0;
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
  SDLKey tabkey[3] = {SDLK_UP, SDLK_LEFT, SDLK_RIGHT};
  int i;
  hero->y += 3.0; /* pour calculer si collision avec bloc en dessous */
  if((collision_hero_decor(hero, table[level]))!=0) { /* on autorise appui sur haut si perso pas dans le ciel ou si il a droit au double saut */
    if(key[tabkey[0]]) { //UP
      oldtime = SDL_GetTicks();
    }
  }
  hero->y -= 3.0; /* reprend sa pos */

  if(key[tabkey[1]]) { //LEFT
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
      if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2 || collision_hero_decor(hero, table[level])==4)
	hero->x += 1.5;
      
    }
  }
    
  if(key[tabkey[2]]) { //RIGHT
    if ( hero->rc_image.x > SPRITE_WIDTH )
      hero->rc_image.x = 0;
    if ( hero->rc_image.x == SPRITE_WIDTH )
      hero->rc_image.x = 0;
    else
      hero->rc_image.x += SPRITE_WIDTH;
    hero->x += 1.5;
    if ((collision_hero_decor(hero, table[level]))==1 || collision_hero_decor(hero, table[level])==2 || collision_hero_decor(hero, table[level])==4 )
      hero->x -= 1.5; 
      
  }
}	       

int main(int argc, char** argv)
{
  SDL_Surface *screen,*temp,*tileset, *coins_img, *coins;
  TTF_Font *police = NULL;
  SDL_Color text_color = {255, 255, 255, 0};
  SDL_Rect coins_text_pos, coins_pos;
  object_type life_1,life_2,life_3;
  list_of_object enemy_list, enemy_list_copy,enemy_list_prev;
  list_of_object life_of_hero_list, life_of_hero_list_copy;
  int past_time_enemy, present_time_enemy, time_axe = 0;
  int invulnerable_time = -1500;
  int sleep_time = 0;
  char direction = 'R', direction_rob = 'R';
  int nb_coins = 0;
  char nb_coins_aff[10] = "";
  bool item_tile, void_item;

  /* Initalize font */
  TTF_Init();
  police = TTF_OpenFont("angelina.TTF", 35);
  sprintf(nb_coins_aff, "X %d", nb_coins);
  coins = TTF_RenderText_Blended(police, nb_coins_aff, text_color);
  coins_text_pos.x = 800;
  coins_text_pos.y = 0;

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

    //load coins
    temp = SDL_LoadBMP("coin.bmp");
    coins_img = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);  

    coins_pos.x = coins_text_pos.x - 50;
    coins_pos.y = coins_text_pos.y;

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

    /* create list of new enemy */
    enemy_list = NULL;
    enemy_list = lvl_gen(level, screen, enemy_list);
    time_axe = SDL_GetTicks();

    if (level == 0) {
      /* create list of new hero lives */
      life_of_hero_list = create_new_list_of_object(); 
      life_1 = create_new_object('L',screen, 5, 5, 'L');
      life_2 = create_new_object('L',screen, 35, 5, 'L');
      life_3 = create_new_object('L',screen, 65, 5, 'L');
      life_of_hero_list = cons(life_1, life_of_hero_list);
      life_of_hero_list = cons(life_2, life_of_hero_list);
      life_of_hero_list = cons(life_3, life_of_hero_list);
    }
   
    item_tile = false; // si on a touché un bloc à item
    void_item = false; // si ce bloc est vide

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
      
      jump(hero, SDL_GetTicks(), oldtime, table[level], &item_tile); // jumps only if oldtime < SDLGetTicks() so if u press up */
      reload_pos(hero); //set hero->coord.x = hero->x same for y
      life_of_hero_list = spawn_life(item_tile, &void_item, life_of_hero_list, screen); /* item_tile = true if u jump under an item tile */
      /* void_item = true if u have already hit the block */
   

      /* collide with edges of screen */
      Collision_screen_hero(hero);

      /* draw the sprite */
      if (level > 0 && level < 6){
	SDL_BlitSurface(hero->sprite, &hero->rc_image, screen, &hero->coord);
      }
      
      // draw coins and number of coins
      if (level > 0 && level < 6){
	SDL_FreeSurface(coins);
	nb_coins = 1;
	sprintf(nb_coins_aff, "X %d", nb_coins);
	coins = TTF_RenderText_Blended(police, nb_coins_aff, text_color);
	SDL_BlitSurface(coins, NULL, screen, &coins_text_pos);
	SDL_BlitSurface(coins_img, NULL, screen, &coins_pos);
	//printf("%s", nb_coins_aff);
      }

      /* draw the enemy sprite */
      enemy_list_prev = NULL;
      enemy_list_copy = enemy_list;
      while (enemy_list_copy != NULL){
	SDL_BlitSurface(enemy_list_copy->first->sprite, &enemy_list_copy->first->rc_image, screen, &enemy_list_copy->first->coord);
	present_time_enemy = SDL_GetTicks();

	if ((SDL_GetTicks()-time_axe > 8000)&&(level==1)) {
	  time_axe = SDL_GetTicks();
	  enemy_list = cons(create_new_object('H',screen, 1024, 410, 'L'), enemy_list);
	}

	/* comme le lvl 3 contient uniquement des haches, cons les éléments du début du lvl tous les x secs revient à ajouter les haches à cet endroit toutes les x sec */
	if ((SDL_GetTicks()-time_axe > 6000)&&(level==3)) {
	  time_axe = SDL_GetTicks();
	  enemy_list = lvl_gen(level, screen, enemy_list);
	}


	/* deplacement of the enemy */
	if (enemy_list_copy->first->type == 'C'){ /*mini-champi*/
	  if (((present_time_enemy - past_time_enemy)/2500)%2 == 0){
	    enemy_list_copy->first->direction = 'R';
	  } else {
	    enemy_list_copy->first->direction = 'L';    
	  }
	  deplacement_object(enemy_list_copy->first,&enemy_list_copy->first->direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'G'){ /*ghost*/
	  if (((present_time_enemy - past_time_enemy)/8500)%2 == 0){
	    enemy_list_copy->first->direction = 'L';
	  } else {
	    enemy_list_copy->first->direction = 'R';    
	  }
	  deplacement_object(enemy_list_copy->first,&enemy_list_copy->first->direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'H'){ /*hache*/
	  deplacement_object(enemy_list_copy->first,&enemy_list_copy->first->direction, table[level]);
	}

	if (enemy_list_copy->first->type == 'S'){ /*Squarel*/
	  pt_sprite enemy = convert_enemy_type_to_pt_spite (enemy_list_copy->first);
	  if (enemy_list_copy->first->direction == 'L') { /* ennemi prend en compte le centre de l'ecureuil */
	    enemy->x = enemy->x - enemy->rc_image.w / 2;
	  } else {
	    enemy->x = enemy->x + enemy->rc_image.w / 2;
	  }
	  if(0==collision_hero_decor(enemy, table[level])) {
	    pt_sprite temp_pos = enemy; 
	    temp_pos->x = enemy->x + 16; /* regarde tuile à droite */
	    temp_pos->y = enemy->y;
	      
	    enemy_list_copy->first->direction = dir(temp_pos, table[level]); /* si tuile à droite vide : va à gauche */
	  }
	  deplacement_object(enemy_list_copy->first, &enemy_list_copy->first->direction, table[level]);
	  enemy = NULL;
	  free(enemy);
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
      while (life_of_hero_list_copy != NULL && level > 0 && level < 6){
	SDL_BlitSurface(life_of_hero_list_copy->first->sprite, &life_of_hero_list_copy->first->rc_image, screen, &life_of_hero_list_copy->first->coord);
	life_of_hero_list_copy = life_of_hero_list_copy->rest;
      }


      CheckLevel(hero, table[level], &level, &levelover, screen);
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);

      //régulation du rythme du programme
      if (SDL_GetTicks()-sleep_time > 20) {
	sleep_time = SDL_GetTicks();
      } else { 
	SDL_Delay(20 - (SDL_GetTicks() - sleep_time));
      }	      
    }
    free_list(enemy_list);
    free_list(enemy_list_copy);
  }

  /* clean up */
  SDL_FreeSurface(hero->sprite);
  free(hero);				 
  
  TTF_CloseFont(police);
  TTF_Quit();
  SDL_FreeSurface(coins);
			       
  SDL_FreeSurface(tileset);
  SDL_Quit();

  return 0;
}

