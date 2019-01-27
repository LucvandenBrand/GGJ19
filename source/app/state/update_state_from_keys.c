#include "../level/level.h"
#include "../music/music.h"
#include "../simple_rng/simple_rng.h"
#include "state.h"
#include "stdlib.h"
#include "tonc_input.h"

State updateStateFromKeys(State state, Level *level, Map *map,
                          u8 currentLevel) {
    if (!state.player.isSliding) {
        if (state.player.inebriationSteps) {
            --state.player.inebriationSteps;
            state.player.velocity.tileX = -key_tri_vert();
            state.player.velocity.tileY = key_tri_horz();
        } else {
            state.player.velocity.tileX = key_tri_horz();
            state.player.velocity.tileY = key_tri_vert();
        }
    }
    State newState = state;
    newState.player.position.tileX += state.player.velocity.tileX;
    newState.player.position.tileY += state.player.velocity.tileY;

    if (!state.player.isSliding) {
        newState.player.bladder += 1;
        for (size_t index = 0; index < newState.n_entities; ++index) {
            Entity entity = newState.entities[index];
            if (entity.type == NoEntity) {
                continue;
            }
            switch (SimpleRNG_rand() % 6) {
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
    }

    if (isPlayerOnToilet(newState, level)) {
        newState.hasPlayerWon = true;
        newState.musicTrack = (currentLevel >= 10 ? 2 : 0);
        return newState;
    }

    if (isPlayerColliding(newState, level)) {
        state.player.isSliding = false;
        return state;
    }
    bool removeTile = true;
    switch (tileUnderPlayer(newState, level)) {
        case Duckie:
            newState.player.isSliding = true;
            break;
        case Alcohol:
            newState.player.inebriationSteps = 10;
            break;
        case Saxophone:
            newState.musicTrack = 1;
        case Diaper:
            if (newState.player.bladder < 50) {
                newState.player.bladder = 0;
            } else {
                newState.player.bladder -= 50;
            }
            break;
        default:
            removeTile = false;
            break;
    }
    if (removeTile) {
        setLevelTile(level, map, newState.player.position.tileX,
                     newState.player.position.tileY, Empty);
    }

    for (size_t index = 0; index < newState.n_entities; ++index) {
        Entity *entity = &newState.entities[index];
        if (entity->type == NoEntity) {
            continue;
        }
        if (newState.player.position.tileX == entity->position.tileX &&
            newState.player.position.tileY == entity->position.tileY) {
            switch (entity->type) {
                case Snake:
                    newState.player.bladder += 30;
                    break;
                case Plunger:
                    newState.player.bladder -= 30;
                    break;
                default:
                    break;
            }
            entity->type = NoEntity;
        }
    }

    increaseAudioSpeed(0.02 * (newState.player.bladder - state.player.bladder));

    return newState;
}
