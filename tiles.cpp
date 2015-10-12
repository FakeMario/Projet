#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12

#pragma GCC diagnostic ignored "-Wwrite-strings"


char* table0[]={ //16 blocs large * 12 blocs haut (64px sur 1024*768)

  "000000000000000000000000",
  "000000000222000000000000",
  "000000000000000033000000",
  "000222000000000000000000",
  "000000000000000000000333",
  "000000000022220000000000",
  "000000000000000000000000",
  "000002200000000000000000",
  "000022220000000000000222",
  "000222222000000002000000",
  "002222222200000022200000",
  "111111111111111111111111",
};
  


char** table[1]={table0};


void Afficher(SDL_Surface* screen, SDL_Surface* tileset, char** table, int min, int max, int nb_blocs_haut){
  int i,j;
  SDL_Rect Rect_dest;
  SDL_Rect Rect_source;
  Rect_source.w = TAILLE_TUILE;
  Rect_source.h = TAILLE_TUILE;

  for(i=min; i<=max; i++){
    for(j=0; j<nb_blocs_haut; j++){
      Rect_dest.x = (i-min)*TAILLE_TUILE;
      Rect_dest.y = j*TAILLE_TUILE;
      Rect_source.x = (table[j][i]-'0')*TAILLE_TUILE;
      Rect_source.y = 0;
      SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest); 
    }
  }
}





