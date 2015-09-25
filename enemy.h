#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include "math.h"
#include "SDL.h"

/*EMENY*/

 struct enemy {
   SDL_Surface *sprite; 
   int colorkey;
   SDL_Rect rc_image;
   SDL_Rect coord;
   float vitesse;
   unsigned int direction;
   float x;
   float y;
   float vx;
   float vy;
};
typedef struct enemy *enemy_type;


enemy_type create_new_enemy(char type, SDL_Surface *screen){
  enemy_type enemy =(enemy_type)malloc(sizeof(struct enemy));
  SDL_Surface * temp;
  switch (type) {
  case 'R': /*Robot*/
  temp = SDL_LoadBMP("robot_1.bmp");
  enemy->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

/* setup sprite colorkey and turn on RLE */
  enemy->colorkey = SDL_MapRGB(screen->format, 150, 0, 150);
  SDL_SetColorKey(enemy->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, enemy->colorkey);

 /* set enemy sprite position */
  enemy->coord.x = 400;
  enemy->coord.y = 430;

  /* set animation frame of the enemy */
  enemy->rc_image.x = 0;
  enemy->rc_image.y = 0;
  enemy->rc_image.w = 40;
  enemy->rc_image.h = 50;

  break;
  }
}



/*LIST OF ENEMY*/

typedef struct List_of_enemy * list_of_enemy;
struct List_of_enemy{
  enemy_type first;
  list_of_enemy  rest;
};


list_of_enemy create_new_list_of_enemy(){
  list_of_enemy L;
  L=(list_of_enemy)malloc(sizeof(list_of_enemy));
  return L;
}


list_of_enemy cons(enemy_type enemy, list_of_enemy L){
  list_of_enemy L1 = create_new_list_of_enemy();
  L1->first = enemy;
  L1->rest = L;
  return L1;
}





#endif
