#include "enemy.h"

/*CREATE ENEMY*/

object_type create_new_object(char type, SDL_Surface *screen, float x, float y){
  object_type object =(object_type)malloc(sizeof(struct object));
  SDL_Surface * temp;
  switch (type) {
  case 'R': /*Robot*/
  temp = SDL_LoadBMP("robot_1.bmp");
  object->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  object->colorkey = SDL_MapRGB(screen->format, 150, 0, 150);
  SDL_SetColorKey(object->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, object->colorkey);
  object->x = x;
  object->y = y;
  object->coord.x = (int)object->x;
  object->coord.y = (int)object->y;
  object->rc_image.x = 0;
  object->rc_image.y = 0;
  object->rc_image.w = 40;
  object->rc_image.h = 50;
  break;

  case 'C':
    temp = SDL_LoadBMP("mini_champi.bmp");
    object->sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    object->colorkey = SDL_MapRGB(screen->format, 150, 0, 150);
    SDL_SetColorKey(object->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, object->colorkey);
    object->x = x;
    object->y = y;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    object->rc_image.x = 0;
    object->rc_image.y = 0;
    object->rc_image.w = 20;
    object->rc_image.h = 20;
    break;
    
  }
  return object;
}



/*LIST OF OBJECT */

list_of_object create_new_list_of_object(){
  return NULL;
}


list_of_object cons(object_type object, list_of_object L){
  list_of_object L1 = create_new_list_of_object();
  L1 = (list_of_object) malloc(sizeof(struct List));
  L1->first = object;
  L1->rest = L;
  return L1;
}



void deplacement_object(object_type object, char direction)
{
  switch (direction) {
  case 'L': /*Left*/
    object->x -= 0.04;
    object->y += 0;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    break;
  case 'R': /*Right*/
    object->x += 0.04;
    object->y += 0;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    break;
  }

}


// void deplacement_sprite_enemy(enemy_type enemy, char direction){

//   switch (direction) {
//   case 'L': /*Left*/
//     enemy->rc_image.x = enemy->rc_image.x+enemy->rc_image.w;
//       if (enemy->rc_image.x == 2 * enemy->rc_image.w || enemy->rc_image.x == 4 * enemy->rc_image.w){
//   	enemy->rc_image.x=0;
//       }
//     break;
//   case 'R': /*Right*/
//     enemy->rc_image.x = >rc_image.x + enemy->rc_image.w;

//       if (enemy->rc_image.x== 4 * enemy->rc_image.w){
//   	enemy->rc_image.x= 2 * enemy->rc_image.w;
//       }
//     break;
//   }

// }

