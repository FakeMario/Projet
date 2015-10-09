#include "sprite.h"

int collision_hero_decor (pt_sprite hero,char** table, int min, int max);

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime, char** table, int min, int max)

{
  if (time - oldtime <= 300 && time - oldtime > 0) {
    hero->y -= 0.75;
    if (0!=collision_hero_decor(hero, table, min, max))
      hero->y += 0.75;
    }
  else if (hero->y < 700) {
    hero->y += 0.5;
    if (0!=collision_hero_decor(hero, table, min, max))
      hero->y -= 0.5;
  }
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
