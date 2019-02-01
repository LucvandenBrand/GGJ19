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
    } else {
        screenPos.x = newX;
        screenPos.y = newY;
    }
    return screenPos;
}

BackgroundPoint interpolatePlayerPos(State *oldState, State *currentState,
                                     double deltat, StateMode stateMode) {
    ObjectPoint objectPos =
        interpolatePos(&oldState->player.position,
                       &currentState->player.position, deltat, stateMode);
    return (BackgroundPoint){.x = objectPos.x, .y = objectPos.y};
}

void renderState(State oldState, State currentState, u32 transitionFrame,
                 u32 currentFrame, StateMode stateMode, Map *map) {
    double deltat =
        (double)(currentFrame - transitionFrame) / (double)TRANSITION_TIME;
    BackgroundPoint playerPos = interpolatePlayerPos(
        &oldState, &currentState, easeInOutQuad(deltat), stateMode);
    ObjectPoint playerFgPos =
        (ObjectPoint){.x = SCREEN_WIDTH / 2, .y = SCREEN_HEIGHT / 2};
    BackgroundPoint mapPos;
    mapPos.x = playerPos.x;
    mapPos.y = playerPos.y;
    mapPos.x -= SCREEN_WIDTH / 2 - 4;
    mapPos.y -= SCREEN_HEIGHT / 2 + 2;

    if (stateMode == TRANSIT) {
        playerFgPos.y += -deltat * 1;
    }

    sprites[0] = playerToSpriteObject(
        playerFgPos, (bool)currentState.player.inebriationSteps);
    sprites[1] = bladderToSpriteObject(currentState.player.bladder);

    for (size_t index = 0; index < currentState.n_entities; ++index) {
        if (currentState.entities[index].type == NoEntity) {
            setSpriteObjectAttributes(&sprites[index + 2], ATTR0_HIDE, 0, 0);
            continue;
        }
        ObjectPoint entityObjPos = interpolatePos(
            &oldState.entities[index].position,
            &currentState.entities[index].position, deltat, stateMode);
        entityObjPos.x -= mapPos.x;
        entityObjPos.y -= mapPos.y;
        entityObjPos.x += 4;
        entityObjPos.y -= 4;
        sprites[index + 2] = entityToSpriteObject(
            entityObjPos, currentState.entities[index].type);
    }

    shiftMap(*map, mapPos);

    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
}
