#include <string.h>
#include "sprite.h"

void loadSpriteSheet(const unsigned short* spritePalette,
                     unsigned spritePaletteLength,
                     const unsigned int* spriteTileSet,
                     unsigned spriteTileSetLength) {
    memcpy(MEM_PAL_OBJ, spritePalette, spritePaletteLength);
    memcpy(&tile_mem[4][0], spriteTileSet, spriteTileSetLength);
};