#include "player.h"

void create_player(Player *player, int x, int y) {
  player->x = x;
  player->y = y;
  player->vel = 2;
  player->width = 8;
  player->height = 8;
  player->left = player->x;
  player->right = player->x + player->width;
  player->top = player->y;
  player->bottom = player->y + player->height;
  player->debug_draw = 0;
}

void move_player(Player *player, int x, int y) {
  /*
  player->x += x + player->vel;
  player->y += y + player->vel;
  */

  if (x < 0) {
    player->x -= player->vel;
  } else if (x > 0) {
    player->x += player->vel;
  }

  if (y < 0) {
    player->y -= player->vel;
  } else if (y > 0) {
    player->y += player->vel;
  }

  player->left = player->x;
  player->right = player->x + player->width;
  player->top = player->y;
  player->bottom = player->y + player->height;
}
