#include "./stateRenderer.h"

OBJ_ATTR entityToSpriteObject(ObjectPoint position, EntityType type) {
    /* u32 tileID = PLAYER_SPRITE_TILE + (isInebriated ? 8 : 0); */
  u32 tileID;
  switch(type) {
  case Snake:
    tileID = PLAYER_SPRITE_TILE + 1 * 16;
    break;
  case Plunger:
    tileID = PLAYER_SPRITE_TILE + 2 * 16;
    break;
  default:
    tileID = PLAYER_SPRITE_TILE + 3 * 16;
    break;
  }

    u32 paletteBank = 0;
    OBJ_ATTR spriteObject;
    setSpriteObjectAttributes(&spriteObject, ATTR0_SQUARE, ATTR1_SIZE_16,
                              ATTR2_PALBANK(paletteBank) | tileID);
    setSpriteObjectPosition(&spriteObject, position);
    return spriteObject;
}
