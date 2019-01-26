#include "stateRenderer.h"

double easeInOutQuad(double t) {
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

ObjectPoint interpolatePlayerPos(State *oldState, State *currentState,
                                 double deltat, StateMode stateMode) {
    ObjectPoint playerPos;
    s32 newX = currentState->player.position.tileX * 16;
    s32 newY = currentState->player.position.tileY * 16;

    if (stateMode == TRANSIT) {
        s32 oldX = oldState->player.position.tileX * 16;
        s32 oldY = oldState->player.position.tileY * 16;

        playerPos.x = oldX + ((double)(newX - oldX) * deltat);
        playerPos.y = oldY + ((double)(newY - oldY) * deltat);
        /* tte_printf("#{el}#{X}%d", deltat); */
    } else {
        playerPos.x = newX;
        playerPos.y = newY;
        /* tte_printf("#{el}#{X}IDLE"); */
    }
    return playerPos;
}

void renderState(State oldState, State currentState, u32 transitionFrame,
                 u32 currentFrame, StateMode stateMode) {
    /* playerPos.x = currentState.player.position.tileX * 16; */
    /* playerPos.y = currentState.player.position.tileY * 16; */
    double deltat = easeInOutQuad((double)(currentFrame - transitionFrame) /
                                  (double)TRANSITION_TIME);
    ObjectPoint playerPos =
        interpolatePlayerPos(&oldState, &currentState, deltat, stateMode);
    sprites[0] = playerToSpriteObject(playerPos);
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
}
