#include "state.h"

Player initializePlayer(const Level *level) {
    return (Player){.position = level->genMap.bedPos,
                      .bladder = INITIAL_BLADDER_FILLED_AMOUNT,
                      .inebriationSteps = 20};
}
