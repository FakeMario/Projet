#include "sprite.h"
#include "enemy.h"

int collision_hero_decor (pt_sprite hero,char** table);
list_of_object spawn_life(pt_sprite hero, list_of_object life, SDL_Surface *screen);

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime, char** table, bool* item_tile)
{
  if (time - oldtime <= 500 && time - oldtime > 0) {
    hero->y -= 3.2;
    if (4==collision_hero_decor(hero, table)) {
      *item_tile = true;
    }

    if (0!=collision_hero_decor(hero, table)) {
      hero->y += 3.2; /* si collision descend d'un pixel */
    }
  } else {
    hero->y += 3.2; /* apres saut, heros retombe */
    if (0!=collision_hero_decor(hero, table)) {
      hero->y -= 3.2; /* si collision avec sol remonte d'un pixel */
    }
  }    
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
