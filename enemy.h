#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdbool.h>
#include "math.h"
#include "SDL.h"

/*EMENY*/

 struct object {
   SDL_Surface *sprite; 
   int colorkey;
   SDL_Rect rc_image;
   SDL_Rect coord;
   float speed;
   unsigned int direction;
   float x;
   float y;
   char type;
};
typedef struct object *object_type;


object_type create_new_object(char type, SDL_Surface *screen, float x, float y);

/*LIST OF ENEMY*/

typedef struct List * list_of_object;
struct List{
  object_type first;
  list_of_object rest;
};


list_of_object create_new_list_of_object();
list_of_object cons(object_type object, list_of_object L);
pt_sprite convert_enemy_type_to_pt_spite (object_type object);
void deplacement_object(object_type object, bool direction, char** table);


#endif
