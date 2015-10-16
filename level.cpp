#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define SCREEN_WIDTH  1024
#define TAILLE_TUILE 64

#pragma GCC diagnostic ignored "-Wwrite-strings"


char* table0[]={ //16 blocs large * 12 blocs haut (64px sur 1024*768)

  "0000000000000001",
  "0000000000000001",
  "0000000000000001",
  "0002220000000001",
  "0000000000000001",
  "0000000000222201",
  "0000000000000001",
  "0000022000000001",
  "000022220000000?",
  "000222222000000>",
  "002222222200000=",
  "1111111111111111",
};
  

char* table1[]={
  "4444444444444444",
  "4444444444444444",
  "4444445555555555",
  "4444456666666667",
  "4444566666666668",
  "4445666666666669",
  "4456666555555555",
  "5566665444444444",
  ":666654444444444",
  ";666544444444444",
  "<665444444444444",
  "5554444444444444",
};

char** table[2]={table0,table1};



int collision_hero_decor (pt_sprite hero,char** table);


void CheckLevel(pt_sprite hero, char** table, int* level, int* levelover, SDL_Surface* screen){
  if (collision_hero_decor(hero, table) == 3){ //si on touche une sortie
    if (hero->x > SCREEN_WIDTH/2){ //si il est du coté droit = si il sort par la droite
      *level++;
      hero->x = TAILLE_TUILE +1; //+1 pour pas qu'il reparte direct dans le lvl précédent
    }
    else { //si on sort par la gauche
      *level--;
      hero->x = SCREEN_WIDTH - TAILLE_TUILE - hero->rc_image.w -1;
    }
    *levelover = 1;
    SDL_Flip(screen);
  }
}
