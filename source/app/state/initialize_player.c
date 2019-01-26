#include "state.h"

Player initializePlayer() {
    return (Player){.position = {.tileX = 5, .tileY = 5},
                    .bladder = INITIAL_BLADDER_FILLED_AMOUNT};
}
