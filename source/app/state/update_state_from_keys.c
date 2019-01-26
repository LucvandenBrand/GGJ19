#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state) {
    State newState = state;
    newState.player.position.tileX -= key_tri_horz();
    newState.player.position.tileY -= key_tri_vert();

    if (isPlayerColliding(newState)) {
        return state;
    }
    return newState;
}
