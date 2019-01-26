#include "tonc.h"

#include <stdbool.h>
#include "audio.h"
#include "simple_rng/simple_rng.h"
#include "state/render/stateRenderer.h"
#include "state/state.h"

#include "./main.h"
#include "setup/setup.h"
#include "tonc_tte.h"

void seedRNGByKeyPress() {
    /* fake seeding by just fetching numbers until key is pressed. */
    while (1) {
        vid_vsync();
        SimpleRNG_rand();
        key_poll();
        if (key_hit(KEY_ANY)) {
            break;
        }
    }
}

// Temporary implementation of level generation; will be swapped for Michiel's
// code.
typedef void* Level;
Level generateLevel(u8 currentLevel) { return NULL; }

void playLevel(Level level) {
    State currentState = newStartState();
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    Map map = loadDefaultMap();
    initializeStateRenderer(currentState, map);
    while (true) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState);
                    stateMode = TRANSIT;
                    transitionFrame = currentFrame;
                }
                break;
            case TRANSIT:
                if (isTransitionFinished(transitionFrame, currentFrame)) {
                    stateMode = IDLE;
                }
                break;
        }
        renderState(oldState, currentState, transitionFrame, currentFrame,
                    stateMode, map);
        /* tte_printf(" %d", stateMode); */
        /* vid_vsync(); */
        /* VBlankIntrWait(); */
    };
}

void playLevels() {
    u8 currentLevel = 1;
    while (true) {
        Level level = generateLevel(currentLevel);
        playLevel(level);
        ++currentLevel;
    }
}

int main() {
    setupGBA();
    tte_printf("Press any key");
    seedRNGByKeyPress();
    playLevels();
}
