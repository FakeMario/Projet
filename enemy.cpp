#include "enemy.h"

/*CREATE ENEMY*/

object_type create_new_object(char type, SDL_Surface *screen, float x, float y){
  object_type object =(object_type)malloc(sizeof(struct object));
  SDL_Surface * temp;
  object->type = type;
  switch (type) {
  case 'G': /*Ghost*/
    temp = SDL_LoadBMP("ghost.bmp");
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
    object->rc_image.w = 41;
    object->rc_image.h = 40;
    break;

  case 'C': /*Mini-Champi*/
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

 case 'M': /*Missile*/
    temp = SDL_LoadBMP("LargeMissiles.bmp");
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

  case 'L': /*Life of the hero*/
    temp = SDL_LoadBMP("life.bmp");
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
    object->rc_image.w = 25;
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
  list_of_object L1 = (list_of_object) malloc(sizeof(struct List));
  L1->first = object;
  L1->rest = L;
  return L1;
}

pt_sprite convert_enemy_type_to_pt_spite (object_type object){
  pt_sprite enemy = (pt_sprite)malloc(sizeof(struct s_sprite));
  enemy->x = object->x;
  enemy->y = object->y;
  enemy->sprite = object->sprite;
  enemy->colorkey = object->colorkey;
  enemy->rc_image = object->rc_image;
  enemy->coord = object->coord;
  return enemy;
}


void deplacement_object(object_type object, bool direction, char** table)
{
  pt_sprite enemy = convert_enemy_type_to_pt_spite (object);
  if (object->type == 'C' || object->type == 'G'){
    if (0==collision_hero_decor(enemy, table)){
      object->y += 0.75;
    }//  else {
    //   object->y -= 0.75;
    // }
  }
  //printf("%d \n", direction);
  if (object->type == 'R'){
    if (0==collision_hero_decor(enemy, table)){
      direction = !direction;
      //printf("%d \n", direction);  
    }
  }
  
  switch (direction) {
  case 0: /*Left*/
    object->x -= 0.08;
    // if ((collision_hero_decor(enemy, table))==1 || collision_hero_decor(enemy, table)==2) {
    //    object->x += 0.08;
    //    }
    object->y += 0;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    object->rc_image.x = object->rc_image.x+object->rc_image.w;
    if (object->rc_image.x == 2 * object->rc_image.w || object->rc_image.x == 4 * object->rc_image.w){
      object->rc_image.x=0;
    }
    break;
  case 1: /*Right*/
    object->x += 0.08;
    // if ((collision_hero_decor(enemy, table))==1 || collision_hero_decor(enemy, table)==2) {
    //    object->x -= 0.08;
    //    }
    object->y += 0;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    object->rc_image.x = object->rc_image.x + object->rc_image.w;

    if (object->rc_image.x== 4 * object->rc_image.w){
      object->rc_image.x= 2 * object->rc_image.w;
    }
    break;
  }
}

