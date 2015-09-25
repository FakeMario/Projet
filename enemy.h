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
   float speed;
   unsigned int direction;
   float x;
   float y;
};
typedef struct enemy *enemy_type;


enemy_type create_new_enemy(char type, SDL_Surface *screen, float x, float y, float speed);



/*LIST OF ENEMY*/

typedef struct List_of_enemy * list_of_enemy;
struct List_of_enemy{
  enemy_type first;
  list_of_enemy  rest;
};


list_of_enemy create_new_list_of_enemy();

list_of_enemy cons(enemy_type enemy, list_of_enemy L);





#endif
