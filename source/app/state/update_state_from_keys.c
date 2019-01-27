#include "../level/level.h"
#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, Level *level, Map *map) {
    if (!state.player.isSliding) {
        state.player.bladder += 1;

        if (state.player.inebriationSteps) {
            --state.player.inebriationSteps;
            state.player.velocity.tileX = -key_tri_vert();
            state.player.velocity.tileY = key_tri_horz();
        } else {
            state.player.velocity.tileX = key_tri_horz();
            state.player.velocity.tileY = key_tri_vert();
        }
    }
    State newState = state;
    newState.player.position.tileX += state.player.velocity.tileX;
    newState.player.position.tileY += state.player.velocity.tileY;

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        state.player.isSliding = false;
        return state;
    }
    if (tileUnderPlayer(newState, level) == Duckie) {
        newState.player.isSliding = true;
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }
    if (tileUnderPlayer(newState, level) == Alcohol) {
        newState.player.inebriationSteps = 10;
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }

    if (tileUnderPlayer(newState, level) == Diaper) {
        if (newState.player.bladder < 50) {
            newState.player.bladder = 0;
        } else {
            newState.player.bladder -= 50;
        }
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }
    return newState;
}
