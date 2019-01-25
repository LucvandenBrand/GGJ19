#ifndef STATE_H
#define STATE_H

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

State newStartState();
State updateStateFromKeys(State state, u32 keyState);
u32 isTransitionFinished(u32 transitionFrame, u32 currentFrame);
void renderState(State oldState, State currentState, u32 transitionFrame, u32 currentFrame);

#endif