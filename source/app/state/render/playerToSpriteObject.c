#include "./stateRenderer.h"

OBJ_ATTR playerToSpriteObject(Player player) {
    u32 tileID = 0;
    u32 paletteBank = 0;
    OBJ_ATTR spriteObject;
    setSpriteObjectAttributes(&spriteObject, ATTR0_SQUARE, ATTR1_SIZE_16,
                              ATTR2_PALBANK(paletteBank) | tileID);
    ObjectPoint position;
    position.x = player.position.tileX * 16;
    position.y = player.position.tileY * 16;
    setSpriteObjectPosition(&spriteObject, position);
    return spriteObject;
}
