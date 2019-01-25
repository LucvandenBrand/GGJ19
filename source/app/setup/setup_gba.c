#include "setup.h"

void setupGBA() {
  setupDisplayMode();
  setupInterrupts();
  setupTextMode();
  setupAudioSystem();
}
