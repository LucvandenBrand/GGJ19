
#include "state.h"

bool isPlayerColliding(State state, Level *level) {
    int tile = tileUnderPlayer(state, level);
    return tile == Wall || tile == Flowers;
}
