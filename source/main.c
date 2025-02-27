#include <filesystem.h>
#include <nds.h>
#include <nf_lib.h>
#include <stdio.h>

#include "player/player.h"

Player player;

int main(int argc, char **argv) {
  // Prepare a NitroFS initialization screen
  NF_Set2D(0, 0);
  NF_Set2D(1, 0);
  consoleDemoInit();
  printf("\nNitro FS init. Please Wait.\n\n");
  swiWaitForVBlank();

  // Initialize NitroFS and set it as root folder of the file system
  nitroFSInit(NULL);
  NF_SetRootFolder("NITROFS");

  // Initialize 2D engine on both screens in mode 0
  NF_Set2D(0, 0);
  NF_Set2D(1, 0);

  // Initializing tiled backgrounds system
  NF_InitTiledBgBuffers();
  NF_InitTiledBgSys(0);
  NF_InitTiledBgSys(1);

  // Initializing sprite buffers
  NF_InitSpriteBuffers();
  NF_InitSpriteSys(0);
  NF_InitSpriteSys(1);

  // Initializing collision map buffers
  NF_InitCmapBuffers();

  // Initializing text system
  NF_InitTextSys(1);

  // creating player
  Player *p_pointer = &player;

  create_player(p_pointer, 60, 60);

  // Load sprite files from NitroFS
  NF_LoadSpriteGfx("sprite/DSSprite", 0, player.width, player.height);
  NF_LoadSpritePal("sprite/DSSprite", 0);

  // Load tiled background
  NF_LoadTiledBg("sprite/DSTileset", "Tilemap", 256, 256);

  NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);
  // NF_SetTextColor(0, 0, 0);

  // Load collision map
  NF_LoadCollisionMap("maps/DSCmap", 0, 256, 256);

  // Create top screen tiled background
  NF_CreateTiledBg(0, 3, "Tilemap");

  NF_CreateTextLayer(1, 2, 0, "normal");

  // Transfer character sprites to VRAM
  NF_VramSpriteGfx(0, 0, 0, false);
  NF_VramSpritePal(0, 0, 0);

  NF_SetTextColor(1, 2, 0);

  // Spawn sprite
  NF_CreateSprite(0, 0, 0, 0, player.x, player.y);

  // Text buffer
  char MyText[32];

  while (1) {
    scanKeys();
    u8 keys = keysHeld();

    if (keys & KEY_UP) {
      move_player(p_pointer, 0, -1);
    } else if (keys & KEY_DOWN) {
      move_player(p_pointer, 0, 1);
    }

    if (keys & KEY_LEFT) {
      move_player(p_pointer, -1, 0);
    } else if (keys & KEY_RIGHT) {
      move_player(p_pointer, 1, 0);
    }

    // u32 tile_id = NF_GetTile(0, player.x, player.y);
    // sprintf(MyText, "%li", tile_id);

    switch (NF_GetTile(0, player.x + player.right / player.width,
                       player.y + player.bottom / player.height)) {
    case 4:
      sprintf(MyText, "Collided with tile 4");
      break;
    case 5:
      sprintf(MyText, "Collided with tile 5");
      break;
    case 3:
      sprintf(MyText, "Collided with tile 3");
      break;
    }

    NF_WriteText(1, 2, 5, 5, MyText);
    NF_MoveSprite(0, 0, player.x, player.y);

    NF_UpdateTextLayers();

    // Update OAM array
    NF_SpriteOamSet(0);
    NF_SpriteOamSet(1);

    // Wait for the screen refresh
    swiWaitForVBlank();

    // Update OAM
    oamUpdate(&oamMain);
    oamUpdate(&oamSub);
  }

  // If this is reached, the program will return to the loader if the loader
  // supports it.
  return 0;
}
