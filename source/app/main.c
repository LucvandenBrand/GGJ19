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
    u32 currentFrame = 0;
    u32 transitionFrame = 0;
    while (1) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                u32 keyState = key_curr_state();
                if (keyState) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState, keyState);
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

int main() {
    playLevel();
}
