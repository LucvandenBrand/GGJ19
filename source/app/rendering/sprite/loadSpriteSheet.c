#include "sprite.h"
#include <string.h>

void loadSpriteSheet(const unsigned short * spritePalette, unsigned spritePaletteLength,
                     const unsigned int * spriteTileSet, unsigned spriteTileSetLength)
{
    memcpy(MEM_PAL_OBJ, spritePalette, spritePaletteLength * 2);
    memcpy(&tile_mem[4][0], spriteTileSet, spriteTileSetLength * 2);
};