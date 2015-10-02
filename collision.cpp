#define NB_BLOCS_HAUTEUR 12
#define NB_BLOCS_LARGEUR 16
#define TAILLE_TUILE 64
#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 768

// bool CollisionDecor(pt_sprite sprite, char** table)
// {
//   SDL_Rect coord;
//   if (sprite->x < 0 || sprite->y <=0 || sprite->x >= SCREEN_WIDTH || sprite->y >= SCREEN_HEIGHT)
//     return true;
//   for (int i = 0; i < NB_BLOCS_HAUTEUR; i++) {
//     for (int j = 0; j < NB_BLOCS_LARGEUR; j++) {
//       if ((table[i][j]-'0') != 0) {
//       coord.x = j * TAILLE_TUILE;
//       coord.y = 768 - i * TAILLE_TUILE;
//       if (sprite->x < coord.x) { // à gauche
// 	if (sprite->x - coord.x >= -3) { // forcement < 0
// 	  return true;
// 	}
//       } else {
// 	if (sprite->x - coord.x + TAILLE_TUILE >= 3) {
// 	  return true;
// 	}
//       }
//       if (sprite->y < coord.y) { // sprite + haut
// 	if (sprite->y - coord.y <= -3) {
// 	  return true;
// 	} else {
// 	  if (sprite->y - coord.y >= 3) {
// 	    return true;
// 	  }
// 	}	  
//       }
//       }
//       return false;
//     }
//   }
// }

int Collision_H_E(pt_sprite hero, enemy_type enemy)
{

  if ((enemy->x >= hero->x + hero->rc_image.w)      // ennemi trop à droite

      || (enemy->x + enemy->rc_image.w <= hero->x) // trop à gauche

      || (enemy->y >= hero->y + hero->rc_image.h) // trop en bas

      || (enemy->y + enemy->rc_image.h <= hero->y))  // trop en haut

    return 0; 

  else

    if (enemy->y - enemy->rc_image.h > hero->y)
      return 1;
    else
      return 2; 

}
