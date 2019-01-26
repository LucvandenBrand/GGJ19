#include <string.h>
#include "sprite.h"

#include "../../../assets/sprites/playerSprite.h"
#include "../../../assets/sprites/bladder/bladder01.h"

void loadSpriteSheet() {
    // Player sprite
    memcpy(MEM_PAL_OBJ, playerSpritePal, playerSpritePalLen);
    memcpy(&tile_mem[4][0], playerSpriteTiles, playerSpriteTilesLen);

    // Bladder sprite
    memcpy(&tile_mem[4][5], bladder01Tiles, bladder01TilesLen);
};