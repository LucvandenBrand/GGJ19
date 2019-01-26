#ifndef STATE_RENDERER_H
#define STATE_RENDERER_H

#include "../state.h"
#include "../../rendering/sprite/sprite.h"
#include "map.h"

#define NUM_SPRITES 128
OBJ_ATTR sprites[NUM_SPRITES];

OBJ_ATTR playerToSpriteObject(ObjectPoint playerPos);
void initializeStateRenderer(State state, Map map);
void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame, StateMode stateMode, Map map);

Map loadDefaultMap();

#endif
