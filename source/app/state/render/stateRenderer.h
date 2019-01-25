#ifndef STATE_RENDERER_H
#define STATE_RENDERER_H

#include "../state.h"
#include "../../rendering/sprite/sprite.h"

#define NUM_SPRITES 1
OBJ_ATTR sprites[NUM_SPRITES];

OBJ_ATTR playerToSpriteObject(Player player);
void initializeStateRenderer(State state);
void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame);

#endif