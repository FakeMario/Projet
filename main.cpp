
#include "SDL.h"
#include "sprite.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE     64
#define CAMERA_SPEED 5

int gameover;

/* source and destination rectangles */
SDL_Rect camera;
pt_sprite hero =(pt_sprite) malloc (sizeof(s_sprite));

void HandleEvent(SDL_Event event)
{
  switch (event.type) {
    /* close button clicked */
  case SDL_QUIT:
    gameover = 1;
    break;
			
    /* handle the keyboard */
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
    case SDLK_q:
      gameover = 1;
      break;
    case SDLK_LEFT:
      if ( hero->rc_image.x < 2*SPRITE_SIZE )
	hero->rc_image.x = 2*SPRITE_SIZE;
      if ( hero->rc_image.x == 3*SPRITE_SIZE )
	hero->rc_image.x = 2*SPRITE_SIZE;
      else
	hero->rc_image.x += SPRITE_SIZE;
      camera.x -= CAMERA_SPEED;
      if (camera.x <= 0)
	camera.x = 2000-640;
      break;
    case SDLK_RIGHT:
      if ( hero->rc_image.x > SPRITE_SIZE )
	hero->rc_image.x = 0;
      if ( hero->rc_image.x == SPRITE_SIZE )
	hero->rc_image.x = 0;
      else
	hero->rc_image.x += SPRITE_SIZE;
      camera.x += CAMERA_SPEED;
      if (camera.x >= 2000-640)
	camera.x = 0;
      break;
    case SDLK_UP:
      break;
    case SDLK_DOWN:
      break;
    }
    break;
  }
}

int main(int argc, char* argv[])
{
  SDL_Surface *screen, *temp, *background;
  SDL_Rect rcBackground;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(70, 70);

  /* load sprite */
  temp = SDL_LoadBMP("sprite.bmp");
  hero->sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* setup sprite colorkey and turn on RLE */
  hero->colorkey = SDL_MapRGB(screen->format, 0, 255, 255);
  SDL_SetColorKey(hero->sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, hero->colorkey);

  /* load background */
  temp  = SDL_LoadBMP("background.bmp");
  background = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);


  /* set sprite position */
  hero->coord.x = 300;
  hero->coord.y = 430;

  /* set animation frame */
  hero->rc_image.x = 0;
  hero->rc_image.y = 0;
  hero->rc_image.w = SPRITE_SIZE;
  hero->rc_image.h = SPRITE_SIZE;

  /* Init camera (point of view) */
  camera.h = SCREEN_HEIGHT;
  camera.w = SCREEN_WIDTH;
  camera.x = 0;
  camera.y = 0;

  gameover = 0;

  /* message pump */
  while (!gameover)
    {
      SDL_Event event;
		
      /* look for an event */
      if (SDL_PollEvent(&event)) {
	HandleEvent(event);
      }

      /* collide with edges of screen */
      if (hero->coord.x <= 0)
	hero->coord.x = 0;
      if (hero->coord.x >= SCREEN_WIDTH - SPRITE_SIZE) 
	hero->coord.x = SCREEN_WIDTH - SPRITE_SIZE;

      if (hero->coord.y <= 0)
	hero->coord.y = 0;
      if (hero->coord.y >= SCREEN_HEIGHT - SPRITE_SIZE) 
	hero->coord.y = SCREEN_HEIGHT - SPRITE_SIZE;

      
      SDL_BlitSurface(background, &camera, screen, NULL);

      /* draw the sprite */
      SDL_BlitSurface(hero->sprite, &hero->rc_image, screen, &hero->coord);

      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }

  /* clean up */
  SDL_FreeSurface(hero->sprite);
  SDL_FreeSurface(background);
  SDL_Quit();

  return 0;
}
