#ifndef STATE_RENDERER_H
#define STATE_RENDERER_H

#include "../state.h"
#include "../../rendering/sprite/sprite.h"
#include "../../level/level.h"
#include "map.h"

#define NUM_SPRITES 128
OBJ_ATTR sprites[NUM_SPRITES];

OBJ_ATTR playerToSpriteObject(ObjectPoint playerPos, bool isInebriated);
OBJ_ATTR bladderToSpriteObject(u32 bladder);
OBJ_ATTR entityToSpriteObject(ObjectPoint position, EntityType type);
u32 bladderToSpriteTile(u32 bladder);
void initializeStateRenderer(State state, Map *map, Level *level);
void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame, StateMode stateMode, Map *map);

Map loadDefaultMap();

#endif
