#include "tonc.h"

#include <stdbool.h>
#include "audio.h"
#include "simple_rng/simple_rng.h"
#include "state/render/stateRenderer.h"
#include "state/state.h"

#include "./main.h"
#include "setup/setup.h"
#include "tonc_tte.h"

#include "mapgen/mapgen.h"

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
    initializeStateRenderer(currentState);
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
        renderState(oldState, currentState, transitionFrame, currentFrame);
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

void wipPrintDungeonMap(Map map) {
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            Tile tile = map.ground[y * MAP_WIDTH + x];
            switch(tile) {
            case Empty:
              m3_plot(x, y, CLR_YELLOW);
              break;
            case Wall:
              m3_plot(x, y, CLR_BLACK);
              break;
            case Bed:
              m3_plot(x, y, CLR_CYAN);
              break;
            case Toilet:
              m3_plot(x, y, CLR_RED);
              break;
            }
        }
    }
    while(true) {};
}

int main() {
    setupGBA();
    tte_printf("Press any key");
    seedRNGByKeyPress();

    Map map = generateMap();
    wipPrintDungeonMap(map);
    /* playLevels(); */
}
