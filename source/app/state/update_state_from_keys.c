#include "../level/level.h"
#include "state.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, Level *level, Map *map, u8 currentLevel) {
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
        newState.musicTrack = (currentLevel >= 10 ? 2 : 0);
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
      newState.player.inebriationSteps = 10;
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
