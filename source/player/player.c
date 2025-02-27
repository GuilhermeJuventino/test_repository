#include "player.h"

void create_player(Player *player, int x, int y) {
  player->x = x;
  player->y = y;
  player->width = 8;
  player->height = 8;
  player->left = player->x;
  player->right = player->x + player->width;
  player->top = player->y;
  player->bottom = player->y + player->height;
  player->debug_draw = 0;
}

void move_player(Player *player, int x, int y) {
  player->x += x;
  player->y += y;
  player->left = player->x;
  player->right = player->x + player->width;
  player->top = player->y;
  player->bottom = player->y + player->height;
}
