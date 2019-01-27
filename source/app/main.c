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

#include "stdlib.h"

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

bool playLevel(Level *level,Audio *music) {
    State currentState = newStartState(level);
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    Map map = loadDefaultMap();
    initializeStateRenderer(currentState, &map, level);
    while (true) {
        ++currentFrame;
        if (currentState.player.bladder >= MAX_BLADDER) {
            return false;
        }
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys || currentState.player.isSliding) {
                    oldState = currentState;
                    currentState =
                      updateStateFromKeys(currentState, level, &map);
                    stateMode = TRANSIT;
                    transitionFrame = currentFrame;
                    if(currentState.musicTrack != oldState.musicTrack){
                      setCurrentAudio(&music[currentState.musicTrack]);
                    }
                }
                break;
            case TRANSIT:
                if (isTransitionFinished(transitionFrame, currentFrame)) {
                    stateMode = IDLE;
                    if (currentState.hasPlayerWon) {
                        return true;
                    }
                }
                break;
        }
        renderState(oldState, currentState, transitionFrame, currentFrame,
                    stateMode, &map);
    };
}

void playLevels() {
  Audio music[2] = {loadAudio("GameTheme.bin"), loadAudio("numberthree.bin")};
  /* Audio audio = loadAudio("GameTheme.bin"); */
  /* Audio audio = loadAudio("numberthree.bin"); */
    setCurrentAudio(&music[0]);

    u8 currentLevel = 1;
    while (true) {
        Level level;
        generateLevel(currentLevel, &level);
        bool playerBeatLevel = playLevel(&level, music);
        if (!playerBeatLevel) {
            break;
        }
        increaseAudioSpeed(0.05);
        ++currentLevel;
    }
    setupGBA();
    tte_printf("You reached level %d\n", currentLevel);
    setAudioSpeed(0);
    key_wait_till_hit(KEY_ANY);
}

int main() {
    setupGBA();
    while (true) {
/*                  tte_printf( */
/*  "|__   __|  (_) |    | |  \n" */
/*   "   | | ___  _| | ___| |_ \n" */
/*  "   | |/ _ \\| | |/ _ \\ __|\n" */
/*  "   | | (_) | | |  __/ |_ \n" */
/*  "   |_|\\___/|_|_|\\___|\\__|\n" */
/* ); */
        tte_printf("Toilet Boy Alpha\n\nPress any key!\n");
        seedRNGByKeyPress();
        tte_printf("#{es}");
        playLevels();
    }
}
