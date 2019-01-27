#ifndef STATE_H
#define STATE_H

#include "tonc_types.h"
#include <stdbool.h>
#include "../level/level.h"
#include "../mapgen/mapgen.h"
#include "map.h"

#define INITIAL_BLADDER_FILLED_AMOUNT 0
#define MAX_BLADDER 100
#define TRANSITION_TIME 30 // in frames

typedef u32 TimeInFrames;
typedef u32 KeyState;

typedef enum {
    IDLE,
    TRANSIT
} StateMode;


typedef struct {
    TilePosition position;
    u16 bladder;
    TilePosition velocity;
    bool isSliding;
  u8 inebriationSteps;
} Player;

typedef struct {
    Player player;
    bool hasPlayerWon;
  u8 musicTrack;
} State;

Player initializePlayer(const Level *level);
GenMapTile tileUnderPlayer();
bool isPlayerColliding();
bool isPlayerOnToilet(State state, const Level *level);

State newStartState(const Level *level);
State updateStateFromKeys(State state, Level *level, Map *map, u8 currentLevel);
bool isTransitionFinished(TimeInFrames transitionFrame, TimeInFrames currentFrame);

#endif
