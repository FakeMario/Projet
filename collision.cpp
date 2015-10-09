#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16
#define SPRITE_WIDTH  50
#define SPRITE_HEIGHT 128
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768

int Collision_H_E(pt_sprite hero, object_type enemy);


int collision_hero_decor (pt_sprite hero,char** table) {
  int i,j;
  SDL_Rect coord;
  printf("on teste les collisions\n");
  object_type tuile =(object_type)malloc(sizeof(struct object));
  for (i=0; i<NB_BLOCS_LARGEUR; i++){
    for (j=0; j<NB_BLOCS_HAUTEUR; j++){
      if (table[j][i]!='0'){ //si on n'est pas sur une case ciel
	coord.x = i*TAILLE_TUILE;
	coord.y = j*TAILLE_TUILE;
	tuile->x = coord.x;
	tuile->y = coord.y;
	tuile->rc_image.h = tuile->rc_image.w = TAILLE_TUILE;
	if(Collision_H_E(hero, tuile)!=0) {
	  printf("collision avec la case %d %d\n", i, j);
	  return Collision_H_E(hero, tuile);
	}
      }
    }
  }
  printf("pas de collision\n");
  return 0;
}


int Collision_H_E(pt_sprite hero, object_type enemy)
{
  if ((enemy->x >= hero->x + hero->rc_image.w)      // ennemi trop à droite
      || (enemy->x + enemy->rc_image.w < hero->x) // trop à gauche
      || (enemy->y >= hero->y + hero->rc_image.h) // trop en bas
      || (enemy->y + enemy->rc_image.h < hero->y))  // trop en haut
    return 0; 
  else
    if (enemy->y - enemy->rc_image.h > hero->y) // on saute sur l'ennemi
      return 1;
    else
      return 2; 
}

