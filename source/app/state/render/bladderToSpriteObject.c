#include "./stateRenderer.h"

OBJ_ATTR bladderToSpriteObject(u32 bladder) {
    u32 tileID = BLADDER_SPRITE_TILE;
    u32 paletteBank = 0;
    OBJ_ATTR spriteObject;
    setSpriteObjectAttributes(&spriteObject, ATTR0_SQUARE, ATTR1_SIZE_16,
                              ATTR2_PALBANK(paletteBank) | tileID);
    //setSpriteObjectPosition(&spriteObject, position);
    return spriteObject;
}
