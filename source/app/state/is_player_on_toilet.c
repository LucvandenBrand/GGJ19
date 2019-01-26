#include "state.h"

bool isPlayerOnToilet(State state, const Level *level) {
  return state.player.position.tileX == level->genMap.toiletPos.tileX
    && state.player.position.tileY == level->genMap.toiletPos.tileY;
}
