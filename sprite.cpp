#include "sprite.h"

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime,int Haut, int Bas )
{
  if (time - oldtime <= 300 && time - oldtime > 0 && Haut) 
    hero->y -= 0.75;
  else if (hero->y < 700 && Bas) 
    hero->y += 0.5;
}
 
void reload_pos(pt_sprite hero)
{
  hero->coord.x = hero->x;
  hero->coord.y = hero->y;
}
