#include "state.h"

State newStartState(const Level *level) {
    return (State){
        .player = initializePlayer(level),
        .n_entities = 1,
        .entities = {(Entity){.type = RubberDuck,
                              .position = {.tileX = 10, .tileY = 10}}}
    };
}
