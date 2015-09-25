#include "enemy.h"
#include "SDL.h"

/*CREATE ENEMY*/

enemy_type create_new_enemy(char type, SDL_Surface *screen, float x, float y, float speed){
  enemy_type enemy =(enemy_type)malloc(sizeof(struct enemy));
  SDL_Surface * temp;
  switch (type) {
  case 'R': /*Robot*/
  temp = SDL_LoadBMP("robot_1.bmp");
  enemy->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  enemy->colorkey = SDL_MapRGB(screen->format, 150, 0, 150);
  SDL_SetColorKey(enemy->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, enemy->colorkey);
  enemy->x=x;
  enemy->y=y;
  enemy->coord.x = (int)enemy->x;
  enemy->coord.y = (int)enemy->y;
  enemy->rc_image.x = 0;
  enemy->rc_image.y = 0;
  enemy->rc_image.w = 40;
  enemy->rc_image.h = 50;
  enemy->speed = speed;



  break;
  }
}



/*LIST OF ENEMY */

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
