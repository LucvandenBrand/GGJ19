#include "state.h"
#include "tonc_input.h"
#include "stdlib.h"
#include "../simple_rng/simple_rng.h"

State updateStateFromKeys(State state, const Level *level) {
    State newState = state;

    for(size_t index = 0; index < newState.n_entities; ++index) {
      Entity entity = newState.entities[index];
      switch(SimpleRNG_rand() % 5) {
      case 0:
        entity.position.tileX += 1;
        break;
      case 1:
        entity.position.tileY += 1;
        break;
      case 2:
        entity.position.tileX -= 1;
        break;
      case 3:
        entity.position.tileY -= 1;
        break;
      default:
        break;
      }

      if(!isEntityColliding(entity, level)) {
        newState.entities[index] = entity;
      }
    }

    newState.player.position.tileX += key_tri_horz();
    newState.player.position.tileY += key_tri_vert();

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        return state;
    }
    return newState;
}
