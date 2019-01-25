#include "state.h"

Player initializePlayer() {
    return (Player){.position = {.tileX = 0, .tileY = 0},
                    .bladder = INITIAL_BLADDER_FILLED_AMOUNT};
}
