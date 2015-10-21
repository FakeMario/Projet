#include "sprite.h"

int collision_hero_decor (pt_sprite hero,char** table);

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime, char** table)

{
  if (time - oldtime <= 300 && time - oldtime > 0) {
    hero->y -= 0.95;
    if (0!=collision_hero_decor(hero, table))
      hero->y += 0.95;
  }
  else if (hero->y < 700) {
    hero->y += 0.8;
    if (0!=collision_hero_decor(hero, table)) {
      hero->y -= 0.8;
    }
  }
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
