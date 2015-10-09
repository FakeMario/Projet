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


void collision_hero_decor (pt_sprite hero,char** table, bool Gauche, bool Droite, bool Haut, bool Bas){
  int i,j;
  SDL_Rect coord;
  object_type object =(object_type)malloc(sizeof(struct object));
  for (i=0; i<NB_BLOCS_LARGEUR; i++){
    for (j=0; j<NB_BLOCS_HAUTEUR; j++){
      if (table[j][i]!='0'){ //si on n'est pas sur une case ciel
	//si le hero est à gauche ou à droite du bloc
	coord.x = i*TAILLE_TUILE;
	coord.y = j*TAILLE_TUILE;
	//	coord.w = coord.h = TAILLE_TUILE;
	object->x = coord.x;
	object->y = coord.y;
	object->rc_image.h = object->rc_image.w = TAILLE_TUILE;
	//printf("%c",table[j][i]);
	if(Collision_H_E(hero, object)==2)
	  printf("toast");
      }
    }
  }
}


int Collision_H_E(pt_sprite hero, object_type enemy)
{
  if ((enemy->x >= hero->x + hero->rc_image.w)      // ennemi trop à droite
      || (enemy->x + enemy->rc_image.w <= hero->x) // trop à gauche
      || (enemy->y >= hero->y + hero->rc_image.h) // trop en bas
      || (enemy->y + enemy->rc_image.h <= hero->y))  // trop en haut
    return 0; 
  else
    if (enemy->y - enemy->rc_image.h > hero->y) // on saute sur l'ennemi
      return 1;
    else
      return 2; 
}

