#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16
#define SPRITE_WIDTH  50
#define SPRITE_HEIGHT 128

// TOAST QUI MARCHE PAS
int collision_hero_decor (pt_sprite hero,char** table){
  int i,j;
  SDL_Rect coord;
  for (i=0; i<NB_BLOCS_LARGEUR; i++){
    for (j=0; j<NB_BLOCS_HAUTEUR; j++){
      if ((table[j][i]-'0')==0){ //si on n'est pas sur une case ciel
	//si le hero est à gauche ou à droite du bloc
	coord.x = i*TAILLE_TUILE;
	coord.y = j*TAILLE_TUILE;
	if ((coord.x <= hero->x+SPRITE_WIDTH <= coord.x+TAILLE_TUILE)&&((coord.y <= hero->coord.y <= coord.y+TAILLE_TUILE)||(coord.y <= hero->y+SPRITE_HEIGHT <= coord.y+TAILLE_TUILE)))
	  return 1;
	//si le hero est au dessus ou en dessous du bloc
	if ((coord.y <= hero->y+SPRITE_WIDTH <= coord.y+TAILLE_TUILE)&&((coord.x <= hero->coord.x <= coord.x+TAILLE_TUILE)||(coord.x <= hero->x+SPRITE_WIDTH <= coord.x+TAILLE_TUILE)))
	  return 1;
      }
    }
  }
  return 0;
}
//TOAST QUI MARCHE PAS
