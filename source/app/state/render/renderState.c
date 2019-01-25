#include "stateRenderer.h"

void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame) {
    sprites[0] = playerToSpriteObject(currentState.player);
    copySpriteObjectsToMemory(sprites, 1);
}