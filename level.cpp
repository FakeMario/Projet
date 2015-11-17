#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768
#define TAILLE_TUILE 32
#define SPRITE_WIDTH  24
#define SPRITE_HEIGHT 62

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
  "00220000002200000022000000220000",
  "11111111111111111111111111111111",
};

void afficher_menu(SDL_Surface *screen){
  SDL_Surface *temp;
  pt_sprite choix = (pt_sprite) malloc (sizeof(s_sprite));
  pt_sprite choix1 = (pt_sprite) malloc (sizeof(s_sprite));
  pt_sprite choix2 = (pt_sprite) malloc (sizeof(s_sprite));
  pt_sprite choix3 = (pt_sprite) malloc (sizeof(s_sprite));
  pt_sprite choix4 = (pt_sprite) malloc (sizeof(s_sprite));
  
  temp = SDL_LoadBMP("sprite.bmp");
  choix1->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("sprite_1.bmp");
  choix2->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("sprite_2.bmp");
  choix3->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  temp = SDL_LoadBMP("sprite_3.bmp");
  choix4->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  choix1->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(choix1->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, choix1->colorkey);
  choix2->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(choix2->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, choix2->colorkey);
  choix3->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(choix3->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, choix3->colorkey);
  choix4->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(choix4->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, choix4->colorkey);

  choix->rc_image.x = 0;
  choix->rc_image.y = 0;
  choix->rc_image.w = SPRITE_WIDTH;
  choix->rc_image.h = SPRITE_HEIGHT;
  
  choix1->coord.x = SCREEN_WIDTH / 12;
  choix1->coord.y = SCREEN_HEIGHT - 2*TAILLE_TUILE - SPRITE_HEIGHT - 1;
  choix2->coord.x = 4*SCREEN_WIDTH / 12;
  choix2->coord.y = SCREEN_HEIGHT - 2*TAILLE_TUILE - SPRITE_HEIGHT - 1;
  choix3->coord.x = 7*SCREEN_WIDTH / 12;
  choix3->coord.y = SCREEN_HEIGHT - 2*TAILLE_TUILE - SPRITE_HEIGHT - 1;
  choix4->coord.x = 10*SCREEN_WIDTH / 12;
  choix4->coord.y = SCREEN_HEIGHT - 2*TAILLE_TUILE - SPRITE_HEIGHT - 1;

  SDL_BlitSurface(choix1->sprite, &choix->rc_image, screen, &choix1->coord);
  SDL_BlitSurface(choix2->sprite, &choix->rc_image, screen, &choix2->coord);
  SDL_BlitSurface(choix3->sprite, &choix->rc_image, screen, &choix3->coord);
  SDL_BlitSurface(choix4->sprite, &choix->rc_image, screen, &choix4->coord);

  SDL_FreeSurface(choix1->sprite);
  SDL_FreeSurface(choix2->sprite);
  SDL_FreeSurface(choix3->sprite);
  SDL_FreeSurface(choix4->sprite);
}

// LEVEL 1

char* table1[]={ //32 blocs large * 24 blocs haut (64px sur 1024*768)
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "2220000000000000000000000000000?",
  "0000000000000000000000000000000>",
  "0000000000000022222000020000000=",
  "00000200000000000000000000022221",
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "00000000022320000000000000000001",
  "00000000000000000000000000000001",
  "00000000000000000000000000000001",
  "0000002000000000000000000000000F",
  "0000000000000000002000000000000H",
  "00000000000222000000000000000001",
  "00000000000000000000000000000001",
  "00000000020000000000000002222001",
  "00000000000000000000000000000001",
  "00000000000000000000200000000001",
  "00000220000000000002220000000001",
  "0000222200000000002222200000000?",
  "0002222220000000022222200000000>",
  "0022222222000000222222200000000=",
  "11111111111111111111111111111111",
};


//LEVEL 2

char* table2[]={
  "44444444445555555555555555555444",
  "44444444456666666666556666666544",
  "55555555566666666666666666666544",
  ":6666666666655555556666555555444",
  ";6666666665544444445555444444444",
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

char* table3[]={
  "10000000000000000000000000000001",
  "C0000000000000000000000000000001",
  "E000000000000000000000000000000?",
  "1000000000000000000000000000000>",
  "1000000000000000000000000000000=",
  "10000002000020000200002000022221",
  "C0020000000000000000000000002111",
  "E0000000000000000000000000000211",
  "10000000000000000000000000000021",
  "10000002000000000000000000000001",
  "B000000000000000000000000000000F",
  "A000000000000000000000000000000H",
  "@0000022200000000000000000000001",
  "22220000222222222222222222222221",
  "11112000000220000220000220000221",
  "11111200000220000220000220000021",
  "1111120000000000000000000000000F",
  "0000000000000000000000000000000H",
  "12222222222223222222222222222001",
  "C0000000000000000000000000000001",
  "E0000000000000000000000000000000",
  "10000220022200022220002222000221",
  "10000220211200021120002112000211",
  "11111111111111111111111111111111",
};

char* table4[]={
  "55555555555555555555555555555555",
  "56666666666666666666666666666665",
  ":6666666666666666666666666666665",
  ";6666666666666666666666666666665",
  "<6666666666666666666666666656665",
  "55555566655555566666666666666665",
  "56666666666666666655555666666665",
  "56666666666666666666666666666665",
  "56666666666666666666666656666665",
  "56666666666666666666666666666665",
  "56666666665555666666666666655555",
  "56666666666666666666666666566665",
  "56666656666666666655555555666665",
  "56666666666666666666666666666665",
  "56666666655555566666666666666665",
  "56666666666666666666666665555555",
  "56666666666666666666666666666665",
  "56655556666666666666666666666665",
  "56666666666666666666666666666665",
  "56666666656666666666666665666667",
  "56666666666666666666666665666668",
  "56666666666666666666666555666669",
  "56666666666665666666665555555555",
  "55555555555555555555555555555555",
};

char* table5[]={
  "11111111111111111111111111111111",
  "1000000000000000000000000000000?",
  "1000000000000000000000000000000>",
  "1000000000000000000111100000000=",
  "10000000000000000000001000000111",
  "10000000000000000000001000001111",
  "10001111111111111111111111111111",
  "C0000000000000000000000000000001",
  "E0000000000000000000000000000000",
  "10000000000000000000000000000001",
  "11000000000000000000000000000001",
  "11111111111111111111111111110001",
  "1000000000000000000000000000000F",
  "0000000000000000000000000000000H",
  "10000000000000000000000000000001",
  "10000000000000000000000000000011",
  "10001111111111111111111111111111",
  "10000000000000000000000000000001",
  "11100000000000000000000000000001",
  "B0010000000000000000010000000001",
  "A0001111111111111111110000001001",
  "@0000000000000000000000010000001",
  "11000000000000000000000111000001",
  "11111111111111111111111111111111",
};


//YOU WIN

char* table6[]={
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

char* table7[]={
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
  "44444466664446444666646446444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
  "44444444444444444444444444444444",
};
char** table[8]={
table0,
table1,
table2,
table3,
table4,
table5,
table6,
table7,
};



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

/* On remplit un tableau avec les lvl déjà visités */
void add_lvl_visited(int* lvl_visited, int lvl){
  if(lvl_visited[lvl-1] != lvl)
    lvl_visited[lvl-1] = lvl;
}

/* Check si on a déjà visité un lvl */
int is_lvl_visited(int* lvl_visited, int lvl){
  return (lvl_visited[lvl-1] == lvl);
}

list_of_object lvl_gen_en(int lvl, SDL_Surface *screen, list_of_object enemy_list)
{
  object_type ghost_enemy_1, ghost_enemy_2, ghost_enemy_3, ghost_enemy_4, squarel_enemy_1, squarel_enemy_2, squarel_enemy_3, squarel_enemy_4, squarel_enemy_5, hache_1, hache_2, hache_3, hache_4, hache_5; 
  switch (lvl) {
  case 1:
    ghost_enemy_1 = create_new_object('G',screen, 200, 152, 'L');
    ghost_enemy_2 = create_new_object('G',screen, 920, 130, 'L');
    squarel_enemy_1 = create_new_object('S',screen, 350, 403, 'L');
    hache_1 = create_new_object('H',screen, 1024, 410, 'L');
    enemy_list = cons(ghost_enemy_1, enemy_list);
    enemy_list = cons(ghost_enemy_2, enemy_list);
    enemy_list = cons(squarel_enemy_1, enemy_list);
    enemy_list = cons(hache_1, enemy_list);


    break;
  case 2 : //2nd level
    ghost_enemy_1 = create_new_object('G',screen, 200, 152, 'L');
    enemy_list = cons(ghost_enemy_1, enemy_list);
    break;

  case 3:
    hache_1 = create_new_object('H',screen, 1024, 540, 'L');
    enemy_list = cons(hache_1, enemy_list);
    hache_2 = create_new_object('H',screen, 0, 635, 'R');
    enemy_list = cons(hache_2, enemy_list);
    hache_3 = create_new_object('H',screen, 0, 60, 'R');
    enemy_list = cons(hache_3, enemy_list);
    hache_4 = create_new_object('H',screen, 0, 220, 'R');
    enemy_list = cons(hache_4, enemy_list);
    hache_5 = create_new_object('H',screen, 1024, 350, 'L');
    enemy_list = cons(hache_5, enemy_list);
    break;

  case 4:
    squarel_enemy_1 = create_new_object('S',screen, 352, 115, 'L');
    squarel_enemy_2 = create_new_object('S',screen, 704, 148, 'R');
    squarel_enemy_3 = create_new_object('S',screen, 418, 403, 'L');
    squarel_enemy_4 = create_new_object('S',screen, 70, 499, 'R');
    squarel_enemy_5 = create_new_object('S',screen, 896, 467, 'L');
    ghost_enemy_1 = create_new_object('G',screen, 940, 314, 'L');
    ghost_enemy_2 = create_new_object('G',screen, 672, 378, 'L');
    ghost_enemy_3 = create_new_object('G',screen, 416, 313, 'L');
    ghost_enemy_4 = create_new_object('G',screen, 334, 696, 'L');
    enemy_list = cons(squarel_enemy_1, enemy_list);
    enemy_list = cons(squarel_enemy_2, enemy_list);
    enemy_list = cons(squarel_enemy_3, enemy_list);
    enemy_list = cons(squarel_enemy_4, enemy_list);
    enemy_list = cons(ghost_enemy_1, enemy_list);
    enemy_list = cons(ghost_enemy_2, enemy_list);
    enemy_list = cons(ghost_enemy_3, enemy_list);
    enemy_list = cons(ghost_enemy_4, enemy_list);
    break;

  case 5:
    enemy_list = cons(create_new_object('G',screen, 660, 130, 'L'), enemy_list);
    enemy_list = cons(create_new_object('H',screen, 967, 416, 'L'), enemy_list);
    enemy_list = cons(create_new_object('H',screen, 33, 256, 'R'), enemy_list);
    break;
  }
  return enemy_list;
}

list_of_object lvl_gen_co(int lvl, SDL_Surface *screen, list_of_object coins_list){
  object_type coin_1, coin_2, coin_3, coin_4, coin_5, coin_6;

 switch(lvl){
 case 1:
   coin_1 = create_new_object('P', screen, 50, 50, 'L');
   coin_2 = create_new_object('P', screen, 65, 340, 'L');
   coin_3 = create_new_object('P', screen, 340, 115, 'L');
   coin_4 = create_new_object('P', screen, 930, 345, 'L');
   coin_5 = create_new_object('P', screen, 417, 666, 'L');
   coin_6 = create_new_object('P', screen, 673, 312, 'L');
   coins_list = cons(coin_1, coins_list);
   coins_list = cons(coin_2, coins_list);
   coins_list = cons(coin_3, coins_list);
   coins_list = cons(coin_4, coins_list);
   coins_list = cons(coin_5, coins_list);
   coins_list = cons(coin_6, coins_list);
   break;
 case 2:
   coin_1 = create_new_object('P', screen, 874, 48, 'L');
   coin_2 = create_new_object('P', screen, 380, 386, 'L');
   coins_list = cons(coin_1, coins_list);
   coins_list = cons(coin_2, coins_list);
   break;
 case 3:
   coin_1 = create_new_object('P', screen, 70, 689, 'L');
   coin_2 = create_new_object('P', screen, 121, 689, 'L');
   coin_3 = create_new_object('P', screen, 927, 314, 'L');
   coins_list = cons(coin_1, coins_list);
   coins_list = cons(coin_2, coins_list);
   coins_list = cons(coin_3, coins_list);
   break;
 case 4:
   coin_1 = create_new_object('P', screen, 111, 320, 'L');
   coin_2 = create_new_object('P', screen, 78, 666, 'L');
   coin_3 = create_new_object('P', screen, 373, 256, 'L');
   coin_4 = create_new_object('P', screen, 951, 96, 'L');
   coin_5 = create_new_object('P', screen, 613, 602, 'L');
   coin_6 = create_new_object('P', screen, 924, 391, 'L');
   coins_list = cons(coin_1, coins_list);
   coins_list = cons(coin_2, coins_list);
   coins_list = cons(coin_3, coins_list);
   coins_list = cons(coin_4, coins_list);
   coins_list = cons(coin_5, coins_list);
   coins_list = cons(coin_6, coins_list);
   break;
 case 5:
   break;
 }
 return coins_list;
}
