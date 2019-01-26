#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, const Level *level) {
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
    newState.player.isSliding = true;
    return newState;
}
