#ifndef STATE_H
#define STATE_H

#include "tonc_types.h"
#include <stdbool.h>

#define INITIAL_BLADDER_FILLED_AMOUNT 25
#define MAX_BLADDER 100
#define TRANSITION_TIME 2000 // in frames

typedef u32 TimeInFrames;
typedef u32 KeyState;

typedef enum {
    IDLE,
    TRANSIT
} StateMode;

typedef struct {
    u8 tileX;
    u8 tileY;
} TilePosition;

typedef struct {
    TilePosition position;
    u16 bladder;
} Player;

typedef struct {
    Player player;
} State;

Player initializePlayer();
bool isPlayerColliding();

State newStartState();
State updateStateFromKeys(State state);
bool isTransitionFinished(TimeInFrames transitionFrame, TimeInFrames currentFrame);
void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame);

#endif
