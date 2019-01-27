#include "stateRenderer.h"

double easeInOutQuad(double t) {
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

ObjectPoint interpolatePos(TilePosition *oldPos, TilePosition *newPos,
                           double deltat, StateMode stateMode) {
    ObjectPoint screenPos;
    s32 newX = newPos->tileX * 8;
    s32 newY = newPos->tileY * 8;

    if (stateMode == TRANSIT) {
        s32 oldX = oldPos->tileX * 8;
        s32 oldY = oldPos->tileY * 8;

        screenPos.x = (oldX + ((double)(newX - oldX) * deltat));
        screenPos.y = (oldY + ((double)(newY - oldY) * deltat));
        /* tte_printf("#{el}#{X}%d", deltat); */
    } else {
        screenPos.x = newX;
        screenPos.y = newY;
        /* tte_printf("#{el}#{X}IDLE"); */
    }
    return screenPos;
}

BackgroundPoint interpolatePlayerPos(State *oldState, State *currentState,
                                     double deltat, StateMode stateMode) {
    /* BackgroundPoint playerPos; */
    /* s32 newX = currentState->player.position.tileX * 8; */
    /* s32 newY = currentState->player.position.tileY * 8; */

    /* if (stateMode == TRANSIT) { */
    /*   s32 oldX = oldState->player.position.tileX * 8; */
    /*   s32 oldY = oldState->player.position.tileY * 8; */

    /*   playerPos.x = (oldX + ((double)(newX - oldX) * deltat)); */
    /*   playerPos.y = (oldY + ((double)(newY - oldY) * deltat)); */
    /*   /\* tte_printf("#{el}#{X}%d", deltat); *\/ */
    /* } else { */
    /*   playerPos.x = newX; */
    /*   playerPos.y = newY; */
    /*   /\* tte_printf("#{el}#{X}IDLE"); *\/ */
    /* } */
    /* return playerPos; */
    ObjectPoint objectPos =
        interpolatePos(&oldState->player.position,
                       &currentState->player.position, deltat, stateMode);
    return (BackgroundPoint){.x = objectPos.x, .y = objectPos.y};
}

void renderState(State oldState, State currentState, u32 transitionFrame,
                 u32 currentFrame, StateMode stateMode, Map *map) {
    /* playerPos.x = currentState.player.position.tileX * 16; */
    /* playerPos.y = currentState.player.position.tileY * 16; */
    double deltat =
        (double)(currentFrame - transitionFrame) / (double)TRANSITION_TIME;
    BackgroundPoint playerPos = interpolatePlayerPos(
        &oldState, &currentState, easeInOutQuad(deltat), stateMode);
    ObjectPoint playerFgPos =
        (ObjectPoint){.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2};
    /* BackgroundPoint mapPos = playerPos; */
    /* mapPos.x = -playerPos.x; */
    /* mapPos.y = -playerPos.y; */
    BackgroundPoint mapPos;
    mapPos.x = playerPos.x;
    mapPos.y = playerPos.y;
    mapPos.x -= SCREEN_WIDTH / 2 - 4;
    mapPos.y -= SCREEN_HEIGHT / 2 + 2;

    if (stateMode == TRANSIT) {
        playerFgPos.y += -deltat * 1;
        /* mapPos.y += -deltat * 1.1; */
    }

    sprites[0] = playerToSpriteObject(
        playerFgPos, (bool)currentState.player.inebriationSteps);
    sprites[1] = bladderToSpriteObject(currentState.player.bladder);

    for (size_t index = 0; index < currentState.n_entities; ++index) {
      if(currentState.entities[index].type == NoEntity){
        setSpriteObjectAttributes(&sprites[index + 2], ATTR0_HIDE, 0, 0);
        continue;
      }
        /* TilePosition entityPos = currentState.entities[index].position; */
        /* ObjectPoint entityObjPos; */
        /* entityObjPos.x = entityPos.tileX * 8 - mapPos.x; */
        /* entityObjPos.y = entityPos.tileY * 8 - mapPos.y; */
        ObjectPoint entityObjPos = interpolatePos(
            &oldState.entities[index].position,
            &currentState.entities[index].position, deltat, stateMode);
        entityObjPos.x -= mapPos.x;
        entityObjPos.y -= mapPos.y;
        entityObjPos.x += 4;
        entityObjPos.y -= 4;
        sprites[index + 2] = playerToSpriteObject(entityObjPos, false);
    }

    shiftMap(*map, mapPos);

    /* tte_printf("#{el}#{X}px: %d py: %d", currentState.player.position.tileX,
     * currentState.player.position.tileY); */
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
}
