#include "./stateRenderer.h"

OBJ_ATTR playerToSpriteObject(Player player) {
    u32 tileID = 0;
    u32 paletteBank = 0;
    OBJ_ATTR spriteObject;
    setSpriteObjectAttributes(&spriteObject,
                              ATTR0_SQUARE,
                              ATTR1_SIZE_16,
                              ATTR2_PALBANK(paletteBank) | tileID);
    ObjectPoint position;
    position.x = player.position.tileX * 16;
    position.y = player.position.tileY * 16;
    setSpriteObjectPosition(&spriteObject, position);
}

void initializeStateRenderer(State state) {
    loadSpriteSheet();
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    sprites[0] = playerToSpriteObject(state.player);
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
    setSpritesOnScreen();
}

void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame) {

}