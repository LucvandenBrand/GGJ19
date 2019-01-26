#include "tonc.h"

#include <stdbool.h>
#include "level/level.h"
#include "music/music.h"
#include "simple_rng/simple_rng.h"
#include "state/render/stateRenderer.h"
#include "state/state.h"

#include "./main.h"
#include "music/music.h"
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

void playLevel(Level *level) {
    State currentState = newStartState(level);
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    Map map = loadDefaultMap();
    initializeStateRenderer(currentState, map, level);
    while (true) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys || currentState.player.isSliding) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState, level);
                    stateMode = TRANSIT;
                    transitionFrame = currentFrame;
                }
                break;
            case TRANSIT:
                if (isTransitionFinished(transitionFrame, currentFrame)) {
                    stateMode = IDLE;
                    if (currentState.hasPlayerWon) {
                        return;
                    }
                }
                break;
        }
        renderState(oldState, currentState, transitionFrame, currentFrame,
                    stateMode, map);
    };
}

void playLevels() {
    Audio audio = loadAudio();
    setCurrentAudio(&audio);

    u8 currentLevel = 1;
    while (true) {
        Level level;
        generateLevel(currentLevel, &level);
        playLevel(&level);
        increaseAudioSpeed();
        ++currentLevel;
    }
}

int main() {
    setupGBA();
    tte_printf("Toilet Boy Alpha\n\nPress any key!\n");
    seedRNGByKeyPress();
    tte_printf("#{es}");
    playLevels();
}
