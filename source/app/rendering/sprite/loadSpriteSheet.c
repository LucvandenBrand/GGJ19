#include <string.h>
#include "sprite.h"

#include "../../../assets/sprites/bladder/bladder01.h"
#include "../../../assets/sprites/bladder/bladder02.h"
#include "../../../assets/sprites/bladder/bladder03.h"
#include "../../../assets/sprites/bladder/bladder04.h"
#include "../../../assets/sprites/bladder/bladder05.h"
#include "../../../assets/sprites/playerSprite.h"
#include "../../../assets/sprites/playerSpriteInebriated.h"
#include "../../../assets/sprites/enemies/snake.h"

void loadSpriteSheet() {
    // Player sprite
    memcpy(MEM_PAL_OBJ, snakePal, snakePalLen);
    memcpy(&tile_mem[4][PLAYER_SPRITE_TILE], playerSpriteTiles,
           playerSpriteTilesLen);

    // Player Sprite Inebriated
    memcpy(&tile_mem[4][PLAYER_SPRITE_TILE + 8], playerSpriteInebriatedTiles,
           playerSpriteInebriatedTilesLen);

    // Enemies
    memcpy(&tile_mem[4][PLAYER_SPRITE_TILE + 16], snakeTiles,
           snakeTilesLen);

    // Bladder sprite
    memcpy(&tile_mem[4][BLADDER_SPRITE_FIRST_TILE], bladder01Tiles,
           bladder01TilesLen);
    memcpy(&tile_mem[4][BLADDER_SPRITE_FIRST_TILE + 8], bladder02Tiles,
           bladder02TilesLen);
    memcpy(&tile_mem[4][BLADDER_SPRITE_FIRST_TILE + 16], bladder03Tiles,
           bladder03TilesLen);
    memcpy(&tile_mem[4][BLADDER_SPRITE_FIRST_TILE + 24], bladder04Tiles,
           bladder04TilesLen);
    memcpy(&tile_mem[4][BLADDER_SPRITE_FIRST_TILE + 32], bladder05Tiles,
           bladder05TilesLen);

};
