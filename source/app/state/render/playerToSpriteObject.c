#include "./stateRenderer.h"

OBJ_ATTR playerToSpriteObject(ObjectPoint position, bool isInebriated) {
  u32 tileID = PLAYER_SPRITE_TILE + (isInebriated ? 4 : 0);
    u32 paletteBank = 0;
    OBJ_ATTR spriteObject;
    setSpriteObjectAttributes(&spriteObject, ATTR0_SQUARE, ATTR1_SIZE_16,
                              ATTR2_PALBANK(paletteBank) | tileID);
    setSpriteObjectPosition(&spriteObject, position);
    return spriteObject;
}
