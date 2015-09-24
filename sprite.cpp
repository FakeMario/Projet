#include "sprite.h"

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime)
{
  if (time - oldtime <= 1000) {
    hero->y -= 0.15;
  } else if (hero->y < 430) {
    hero->y += 0.15;
  }
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
      
  
