#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define SCREEN_WIDTH  1024
#define TAILLE_TUILE 32

#pragma GCC diagnostic ignored "-Wwrite-strings"

// MENU

char* table0[]={
  "00000000000000000000000000000000",
  "01111010010111101111011110111100",
  "01000010010100101001010000100000",
  "01000011110100101001011110111000",
  "01000010010100101001000010100000",
  "01111010010111101111011110111100",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00001000001100000111000001001000",
  "00011000010010000000100001001000",
  "00101000000010000000100001001000",
  "01001000000100000011000001111000",
  "00001000001000000000100000001000",
  "00001000010000000000100000001000",
  "00001000011110000111000000001000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "00000000000000000000000000000000",
  "11111111111111111111111111111111",
};

// LEVEL 1

char* table1[]={ //32 blocs large * 24 blocs haut (64px sur 1024*768)
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "0000000000000000000000000000000?",
  "0000000222200000000000000000000>",
  "0000000000000022222000000000000=",
  "00000000000000000000000000022221",
  "00000000000000000000222200000001",
  "00000000000000222000000000000001",
  "00000000000000000000000000000001",
  "00000000023320000000002200022001",
  "00002220000000000000002200022001",
  "0000000000000000000000000000000F",
  "0000000000000000000000000000000H",
  "00000000000222222000000000000001",
  "00022222000000000000000000000001",
  "00000000000000000000002222222001",
  "00000000002222000000020000000001",
  "00000000000000000000200000000001",
  "00000220000000000002200000000001",
  "0000222200000000002220000000000?",
  "0002222220000000022220000000000>",
  "0022222222000000222220000000000=",
  "11111111111111111111111111111111",
};


//LEVEL 2

char* table2[]={
  "44444444445555555555555555555444",
  "44444444456666666666666666666544",
  "55555555566666666666666666666544",
  ":6666666666655555555555555555444",
  ";6666666665544444444444444444444",
  "<6666666654444444444444444444444",
  "55555566654444444444444444444444",
  "44444456665444444444444444444444",
  "44444445666544444444444444444444",
  "44444444566655555555555555555555",
  "44444444456666666666666666666667",
  "44444444445666666666666666666668",
  "44444444445666666666666666666669",
  "44444444445666655555555555555555",
  "44444444456666544444444444444444",
  "44444444566665444444444444444444",
  "44444445666654444444444444444444",
  "44444456666544444444444444444444",
  "44444566665444444444444444444444",
  "55555666654444444444444444444444",
  ":6666666544444444444444444444444",
  ";6666665444444444444444444444444",
  "<6666654444444444444444444444444",
  "55555544444444444444444444444444",
  };

//YOU WIN

char* table3[]={
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444424442422224244244444444",
  "44444444442424424424244244444444",
  "44444444444244424424244244444444",
  "44444444444244424424244244444444",
  "44444444444244422224222244444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444244444442422242444244424444",
  "44444244424442442442244244424444",
  "44444424242424442442424244424444",
  "44444424242424442442442244444444",
  "44444442444244422242444244424444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
};

//GAME OVER

char* table4[]={
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444666646666466444664666644444",
  "44444644446446464646464644444444",
  "44444646646666464464464664444444",
  "44444644646446464444464644444444",
  "44444666646446464444464666644444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444466664644464666646666444444",
  "44444464464644464644446446444444",
  "44444464464464644664446666444444",
  "44444464464464644644446464444444",
  "44444466664446444666646464444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
};
char** table[5]={table0,table1,table2,table3,table4};



int collision_hero_decor (pt_sprite hero,char** table);


void CheckLevel(pt_sprite hero, char** table, int* level, int* levelover, SDL_Surface* screen){
  if (collision_hero_decor(hero, table) == 3){ //si on touche une sortie
    if (hero->x > SCREEN_WIDTH/2){ //si il est du coté droit = si il sort par la droite
      *level+=1;
      hero->x = TAILLE_TUILE +1; //+1 pour pas qu'il reparte direct dans le lvl précédent
    }
    else { //si on sort par la gauche
      *level-=1;
      hero->x = SCREEN_WIDTH - TAILLE_TUILE - hero->rc_image.w -1;
    }
    *levelover = 1;
    SDL_Flip(screen);
  }
}
