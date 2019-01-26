#include "state.h"
#include "tonc_input.h"
#include "../level/level.h"

State updateStateFromKeys(State state, Level *level) {
    if (!state.player.isSliding){
        state.player.velocity.tileX = key_tri_horz();
        state.player.velocity.tileY = key_tri_vert();
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
    if (tileUnderPlayer(newState, level) == Duckie){
        newState.player.isSliding = true;
        setLevelTile(level, newState.player.position.tileX, newState.player.position.tileY, Empty);
    }
    return newState;
}
