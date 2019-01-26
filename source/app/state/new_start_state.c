#include "state.h"

State newStartState(const Level *level) {
    return (State){.player = initializePlayer(level)};
}
