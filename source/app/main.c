#include "tonc.h"

#include <stdbool.h>
#include "simple_rng/simple_rng.h"
#include "state/state.h"

#include "./main.h"

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

void playLevel() {
    State currentState = newStartState();
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    while (true) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState, keys);
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
    };
}

int main() { playLevel(); }
