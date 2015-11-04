#include "sprite.h"
#include "enemy.h"

int collision_hero_decor (pt_sprite hero,char** table);
list_of_object spawn_life(pt_sprite hero, list_of_object life, SDL_Surface *screen);

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime, char** table, list_of_object life, SDL_Surface *screen)
{
  if (time - oldtime <= 500 && time - oldtime > 0) {
    hero->y -= 3.2;

    if (4==collision_hero_decor(hero, table)) {
      printf("yolo");
      life = cons(create_new_object('L', screen, life->first->x + 30, life->first->y), life);
    }

    if (0!=collision_hero_decor(hero, table)) {
      hero->y += 3.2;
    }
  } else {
    hero->y += 3.0;
    if (0!=collision_hero_decor(hero, table)) {
      hero->y -= 3.0;
    }
  }    
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
