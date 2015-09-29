#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define TAILLE_TUILE 64
#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16

//Ne pas oublier de changer la résolution en 1024*768 dans le main
//Virer tout ce qui est image de fond et affichage de l'image

char * table[] = { //16 blocs large * 12 blocs haut (64px sur 1024*768)
  "0000000000000000",
  "0000000002220000",
  "0000000000000000",
  "0002220000000000",
  "0000000000000000",
  "0000000022220000",
  "0000000000000000",
  "0000022000000000",
  "0000222200000000",
  "0002222220000000",
  "0022222222000000",
  "1111111111111111",
};

void Afficher(SDL_Surface* screen, SDL_Surface* tile0, SDL_Surface* tile1, SDL_Surface* tile2, SDL_Surface* tile3, char** table, int nb_blocs_larg, int nb_blocs_haut){
  int i,j;
  SDL_Rect Rect_dest;
  SDL_Rect Rect_source;
  Rect_source.w = TAILLE_TUILE;
  Rect_source.h = TAILLE_TUILE;

  for(i=0; i<nb_blocs_larg; i++){
    for(j=0; j<nb_blocs_haut; j++){
      Rect_dest.x = i*TAILLE_TUILE;
      Rect_dest.y = j*TAILLE_TUILE;
      Rect_source.x = (table[j][i]-'0')*TAILLE_TUILE;
      Rect_source.y = 0;
      switch (table[j][i]){
      case 0:
	SDL_BlitSurface(tile0, &Rect_source, screen, &Rect_dest);
	break;
      case 1:
	SDL_BlitSurface(tile1, &Rect_source, screen, &Rect_dest);
	break;
      case 2:
	SDL_BlitSurface(tile2, &Rect_source, screen, &Rect_dest);
	break;
      case 3:
	SDL_BlitSurface(tile3, &Rect_source, screen, &Rect_dest);
	break;
      }
    }
  }
  SDL_Flip(screen);

}

