#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player
{
  int x;
  int y;
  int width;
  int height;
  int left;
  int right;
  int top;
  int bottom;
  int debug_draw;
} Player;

void create_player(Player* player, int x, int y);
void move_player(Player* player, int x, int y);

#endif // !PLAYER_H

