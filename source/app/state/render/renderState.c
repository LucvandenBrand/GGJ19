#include "stateRenderer.h"

double easeInOutQuad(double t) {
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

BackgroundPoint interpolatePlayerPos(State *oldState, State *currentState,
                                     double deltat, StateMode stateMode) {
    BackgroundPoint playerPos;
    s32 newX = currentState->player.position.tileX * 8;
    s32 newY = currentState->player.position.tileY * 8;

    if (stateMode == TRANSIT) {
        s32 oldX = oldState->player.position.tileX * 8;
        s32 oldY = oldState->player.position.tileY * 8;

        playerPos.x = (oldX + ((double)(newX - oldX) * deltat));
        playerPos.y = (oldY + ((double)(newY - oldY) * deltat));
        /* tte_printf("#{el}#{X}%d", deltat); */
    } else {
        playerPos.x = newX;
        playerPos.y = newY;
        /* tte_printf("#{el}#{X}IDLE"); */
    }
    return playerPos;
}

void renderState(State oldState, State currentState, u32 transitionFrame,
                 u32 currentFrame, StateMode stateMode, Map map) {
    /* playerPos.x = currentState.player.position.tileX * 16; */
    /* playerPos.y = currentState.player.position.tileY * 16; */
    double deltat =
        (double)(currentFrame - transitionFrame) / (double)TRANSITION_TIME;
    BackgroundPoint playerPos = interpolatePlayerPos(
        &oldState, &currentState, easeInOutQuad(deltat), stateMode);
    ObjectPoint playerFgPos = (ObjectPoint){.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2};
    /* BackgroundPoint mapPos = playerPos; */
    /* mapPos.x = -playerPos.x; */
    /* mapPos.y = -playerPos.y; */
    BackgroundPoint mapPos;
    mapPos.x = playerPos.x;
    mapPos.y = playerPos.y;
    mapPos.x -= SCREEN_WIDTH / 2 - 4;
    mapPos.y -= SCREEN_HEIGHT / 2 + 2;

    if(stateMode == TRANSIT){
      playerFgPos.y += -deltat*1;
      mapPos.y += -deltat*1.1;
    }

    sprites[0] = playerToSpriteObject(playerFgPos);
    sprites[1] = bladderToSpriteObject(currentState.player.bladder);

    shiftMap(map, mapPos);

    /* tte_printf("#{el}#{X}px: %d py: %d", currentState.player.position.tileX,
     * currentState.player.position.tileY); */
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
}
