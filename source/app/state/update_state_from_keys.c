#include "../level/level.h"
#include "../simple_rng/simple_rng.h"
#include "state.h"
#include "stdlib.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, Level *level, Map *map) {
    State newState = state;
    if (!state.player.isSliding) {
        newState.player.bladder += 1;

        for (size_t index = 0; index < newState.n_entities; ++index) {
            Entity entity = newState.entities[index];
            switch (SimpleRNG_rand() % 5) {
                case 0:
                    entity.position.tileX += 1;
                    break;
                case 1:
                    entity.position.tileY += 1;
                    break;
                case 2:
                    entity.position.tileX -= 1;
                    break;
                case 3:
                    entity.position.tileY -= 1;
                    break;
                default:
                    break;
            }

            if (!isEntityColliding(entity, level)) {
                newState.entities[index] = entity;
            }
        }

        if (state.player.inebriationSteps) {
            --state.player.inebriationSteps;
            newState.player.velocity.tileX = -key_tri_vert();
            newState.player.velocity.tileY = key_tri_horz();
        } else {
            newState.player.velocity.tileX = key_tri_horz();
            newState.player.velocity.tileY = key_tri_vert();
        }
    }
    newState.player.position.tileX += newState.player.velocity.tileX;
    newState.player.position.tileY += newState.player.velocity.tileY;

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        state.player.isSliding = false;
        return state;
    }
    if (tileUnderPlayer(newState, level) == Duckie) {
        newState.player.isSliding = true;
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }
    if (tileUnderPlayer(newState, level) == Alcohol) {
        newState.player.inebriationSteps = 20;
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }

    if (tileUnderPlayer(newState, level) == Diaper) {
        if (newState.player.bladder < 50) {
            newState.player.bladder = 0;
        } else {
            newState.player.bladder -= 50;
        }
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }
    return newState;
}
