#include "stateRenderer.h"

void initializeStateRenderer(State state) {
    loadSpriteSheet();
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    renderState(state, state, 0, 0, IDLE);
    /* sprites[0] = playerToSpriteObject(state.player); */
    /* copySpriteObjectsToMemory(sprites, NUM_SPRITES); */
    setSpritesOnScreen();
}
