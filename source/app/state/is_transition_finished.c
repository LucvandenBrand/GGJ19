#include "state.h"

bool isTransitionFinished(TimeInFrames transitionFrame, TimeInFrames currentFrame) {
  return currentFrame - transitionFrame == TRANSITION_TIME;
}
