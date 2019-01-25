#include "stateRenderer.h"

void initializeStateRenderer(State state) {
    loadSpriteSheet();
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    sprites[0] = playerToSpriteObject(state.player);
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
    setSpritesOnScreen();
}
