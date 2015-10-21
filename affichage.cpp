#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define TAILLE_TUILE 32
#define NB_BLOCS_HAUTEUR 24
#define NB_BLOCS_LARGEUR 32


void Afficher(SDL_Surface* screen, SDL_Surface* tileset, char** table, int nb_blocs_haut, int nb_blocs_large){
  int i,j;
  SDL_Rect Rect_dest;
  SDL_Rect Rect_source;
  Rect_source.w = TAILLE_TUILE;
  Rect_source.h = TAILLE_TUILE;

  for(i=0; i<=nb_blocs_large; i++){
    for(j=0; j<nb_blocs_haut; j++){
      Rect_dest.x = i*TAILLE_TUILE;
      Rect_dest.y = j*TAILLE_TUILE;
      Rect_source.x = (table[j][i]-'0')*TAILLE_TUILE;
      Rect_source.y = 0;
      SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest); 
    }
  }
}





