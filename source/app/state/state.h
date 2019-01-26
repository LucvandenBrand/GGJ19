#ifndef STATE_H
#define STATE_H

#include "tonc_types.h"
#include <stdbool.h>
#include "../level/level.h"

#define INITIAL_BLADDER_FILLED_AMOUNT 25
#define MAX_BLADDER 100
#define TRANSITION_TIME 50 // in frames

typedef u32 TimeInFrames;
typedef u32 KeyState;

typedef enum {
    IDLE,
    TRANSIT
} StateMode;


typedef struct {
    TilePosition position;
    u16 bladder;
} Player;

typedef struct {
    Player player;
} State;

Player initializePlayer(const Level *level);
bool isPlayerColliding();

State newStartState(const Level *level);
State updateStateFromKeys(State state, Level *level);
bool isTransitionFinished(TimeInFrames transitionFrame, TimeInFrames currentFrame);

#endif
