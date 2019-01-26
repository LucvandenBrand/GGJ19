#include "state.h"
#include "tonc_input.h"
#include "../level/level.h"


State updateStateFromKeys(State state, Level *level, Map *map) {
    if (!state.player.isSliding){
      if(state.player.inebriationSteps) {
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

    if (newState.player.bladder < MAX_BLADDER)
        newState.player.bladder += 2;

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
        setLevelTile(level, map, newState.player.position.tileX, newState.player.position.tileY, Empty);
    }
    if (tileUnderPlayer(newState, level) == Alcohol){
      newState.player.inebriationSteps = 20;
      setLevelTile(level, map, newState.player.position.tileX, newState.player.position.tileY, Empty);
    }
    return newState;
}
