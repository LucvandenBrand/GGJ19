#include <string.h>
#include "sprite.h"

#include "../../../assets/sprites/playerSprite.h"
#include "../../../assets/sprites/bladder/bladder01.h"

void loadSpriteSheet() {
    // Player sprite
    memcpy(MEM_PAL_OBJ, playerSpritePal, playerSpritePalLen);
    memcpy(&tile_mem[4][PLAYER_SPRITE_TILE], playerSpriteTiles, playerSpriteTilesLen);

    // Bladder sprite
    memcpy(&tile_mem[4][BLADDER_SPRITE_TILE], bladder01Tiles, bladder01TilesLen);
};