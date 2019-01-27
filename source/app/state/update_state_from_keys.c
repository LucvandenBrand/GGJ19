#include "../level/level.h"
#include "../simple_rng/simple_rng.h"
#include "state.h"
#include "stdlib.h"
#include "tonc_input.h"
#include "../music/music.h"

State updateStateFromKeys(State state, Level *level, Map *map,
                          u8 currentLevel) {
    State newState = state;
    if (!state.player.isSliding) {
        newState.player.bladder += 1;

        for (size_t index = 0; index < newState.n_entities; ++index) {
            Entity entity = newState.entities[index];
            if(entity.type == NoEntity){
              continue;
            }
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
            --newState.player.inebriationSteps;
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
            newState.player.inebriationSteps = 20;
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

    for(size_t index = 0; index < newState.n_entities; ++index) {
      if(newState.entities[index].type == NoEntity){
        continue;
      }
      if(newState.player.position.tileX == newState.entities[index].position.tileX
         && newState.player.position.tileY == newState.entities[index].position.tileY) {
        newState.player.bladder += 30;
        newState.entities[index].type = NoEntity;
      }
    }

    increaseAudioSpeed(0.02 * (newState.player.bladder - state.player.bladder));

    return newState;
}
