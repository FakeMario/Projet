#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <stdbool.h>
#include "math.h"
#include <unistd.h>
#include "SDL.h"
#include <time.h>


 struct s_sprite {
   SDL_Surface *sprite; 
   int colorkey; /* color which has to be invisible on the background */
   SDL_Rect rc_image; /*coords on the bmp */
   SDL_Rect coord; /* coords on the screen */
   float x,y;
   const int size; /* sprite size */
};
typedef struct s_sprite *pt_sprite;

void jump(pt_sprite hero, unsigned int time, unsigned int oldtime);
#endif
