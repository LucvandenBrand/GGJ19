#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, const Level *level) {
    State newState = state;
    newState.player.position.tileX += key_tri_horz();
    newState.player.position.tileY += key_tri_vert();

    if (newState.player.bladder <= MAX_BLADDER)
        newState.player.bladder += 1;

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        return state;
    }
    return newState;
}
