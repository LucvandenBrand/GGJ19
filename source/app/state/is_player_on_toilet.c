#include "state.h"

bool isPlayerOnToilet(State state, const Level *level) {
    return tileUnderPlayer(state, level) == Toilet;
}
