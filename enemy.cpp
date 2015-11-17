#include "enemy.h"

/*CREATE ENEMY*/
char dir(object_type object, char* direction, char** table);

object_type create_new_object(char type, SDL_Surface *screen, float x, float y, char direction){
  object_type object =(object_type)malloc(sizeof(struct object));
  SDL_Surface * temp;
  object->type = type;
  object->direction = direction;
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
    object->speed = 0.4;
    break;

 case 'S': /*Squarel*/
    temp = SDL_LoadBMP("Squarel.bmp");
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
    object->rc_image.w = 37;
    object->rc_image.h = 46;
    object->speed = 0.3;
    break;

 case 'H': /*Hache*/
    temp = SDL_LoadBMP("hache.bmp");
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
    object->rc_image.w = 31;
    object->rc_image.h = 31;
    object->speed = 0.7;
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

    case 'P': /*Coins*/
    temp = SDL_LoadBMP("coin.bmp");
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
    object->rc_image.w = 30;
    object->rc_image.h = 29;
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

void free_list(list_of_object L)
{
  if(L != NULL) {
    SDL_FreeSurface(L->first->sprite);
    free(L->first);
    free(L);
    free_list(L->rest);

  }
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


void deplacement_object(object_type object, char* direction, char** table)
{
  pt_sprite enemy = convert_enemy_type_to_pt_spite (object);
  if (object->type == 'G'){
    if (0==collision_hero_decor(enemy, table) || 4==collision_hero_decor(enemy, table)) {
      object->y += 4.5;
    } else { /* si collision quand il marche */
      enemy->y -= 3.5; /* en le soulevant il ne touche plus le sol */
      if (0!=collision_hero_decor(enemy, table) && 4!=collision_hero_decor(enemy, table)) { /*si vrai : bloc sur le passage*/
  	enemy->y -= 32; /* on remonte la hitbox d'un bloc */
  	if (0==collision_hero_decor(enemy, table)|| 4==collision_hero_decor(enemy, table)) { // seulement un bloc de haut
	  object->y -= 3.5; // dans ce cas l'ennemi peut l'escalader
	}
      }
    }
  }

  enemy = NULL;
  free(enemy);
  switch (*direction) {
  case 'L': /*Left*/
    object->x -= object->speed;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    object->rc_image.x = object->rc_image.x+object->rc_image.w;
    if (object->type !='H'){
      if (object->rc_image.x == 2 * object->rc_image.w || object->rc_image.x == 4 * object->rc_image.w){
	object->rc_image.x=0;
      }
    } else {
      if (object->rc_image.x== 6 * object->rc_image.w){
	object->rc_image.x= 3 * object->rc_image.w;
      }
    }
    break;
  case 'R': /*Right*/
    object->x += object->speed;
    object->coord.x = (int)object->x;
    object->coord.y = (int)object->y;
    object->rc_image.x = object->rc_image.x + object->rc_image.w;
    if (object->type != 'H'){
      if (object->rc_image.x== 4 * object->rc_image.w){
	object->rc_image.x= 2 * object->rc_image.w;
      }
    } else {
      if (object->rc_image.x== 3 * object->rc_image.w || object->rc_image.x == 6 * object->rc_image.w){
	object->rc_image.x= 0;
      }
    }
    break;
  }
}

char dir (pt_sprite adjacent_tile, char** table)
{
  if (0==collision_hero_decor(adjacent_tile, table)) {
    return 'L';
  }
  return 'R';
}

list_of_object spawn_life(bool item_tile, bool* void_item, list_of_object life, SDL_Surface *screen)
{
  if(item_tile && ! *void_item) {
    life = cons(create_new_object('L', screen, life->first->x + 30, life->first->y, 'L'), life);
    *void_item = true;
  }
  return life;
}
