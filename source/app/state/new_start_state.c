#include <stdlib.h>
#include "../simple_rng/simple_rng.h"
#include "state.h"

Entity createEntity(u8 tileX, u8 tileY) {
    EntityType type = 1 + SimpleRNG_rand() % 2;
    return (Entity){.type = type, .position = {.tileX = tileX, .tileY = tileY}};
}

State newStartState(const Level *level) {
    State state = {0};
    state.player = initializePlayer(level);

    size_t n_potential_entities = SimpleRNG_rand() % 100;
    for (size_t index = 0; index < n_potential_entities; ++index) {
        if (state.n_entities == MAX_ENTITIES) {
            break;
        }
        u8 tileX = SimpleRNG_rand() % 64;
        u8 tileY = SimpleRNG_rand() % 64;
        if (level->genMap.ground[tileY + MAP_WIDTH * tileX] != Wall) {
            state.entities[state.n_entities] = createEntity(tileX, tileY);
            ++state.n_entities;
        }
    }
    /* return (State){ */
    /*     .player = initializePlayer(level), */
    /*     .n_entities = 1, */
    /*     .entities = {(Entity){.type = RubberDuck, */
    /*                           .position = {.tileX = 10, .tileY = 10}}}}; */
    return state;
}
