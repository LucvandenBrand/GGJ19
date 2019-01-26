#ifndef STATE_H
#define STATE_H

#include "tonc_types.h"
#include <stdbool.h>

#define INITIAL_BLADDER_FILLED_AMOUNT 25
#define MAX_BLADDER 100
#define TRANSITION_TIME 100 // in frames

typedef u32 TimeInFrames;
typedef u32 KeyState;

typedef enum {
    IDLE,
    TRANSIT
} StateMode;

typedef struct {
    s8 tileX;
    s8 tileY;
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

#endif
