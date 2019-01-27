#include "../level/level.h"
#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, Level *level, Map *map) {
    State newState = state;
    if (!state.player.isSliding) {
        newState.player.bladder += 1;

        if (state.player.inebriationSteps) {
            --state.player.inebriationSteps;
            newState.player.velocity.tileX = -key_tri_vert();
            newState.player.velocity.tileY = key_tri_horz();
        } else {
            newState.player.velocity.tileX = key_tri_horz();
            newState.player.velocity.tileY = key_tri_vert();
        }
    }
    newState.player.position.tileX += newState.player.velocity.tileX;
    newState.player.position.tileY += newState.player.velocity.tileY;

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        newState.musicTrack = 0;
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        state.player.isSliding = false;
        return state;
    }
    bool removeTile = true;
    switch(tileUnderPlayer(newState, level)) {
    case Duckie:
      newState.player.isSliding = true;
      break;
    case Alcohol:
      newState.player.inebriationSteps = 20;
      break;
    case Saxophone:
      newState.musicTrack = 1;
    case Diaper:
      if (newState.player.bladder < 50) {
        newState.player.bladder = 0;
      } else {
        newState.player.bladder -= 50;
      }
      break;
    default:
      removeTile = false;
      break;
    }
    if(removeTile){
      setLevelTile(level, map, newState.player.position.tileX,
                   newState.player.position.tileY, Empty);
    }

    return newState;
}
