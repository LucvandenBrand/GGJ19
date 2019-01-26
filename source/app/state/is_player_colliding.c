
#include "state.h"

bool isPlayerColliding(State state, Level *level) {
    return tileUnderPlayer(state, level) == Wall;
}
