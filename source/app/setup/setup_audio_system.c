#include "setup.h"
#include "audio.h"
#include "tonc_irq.h"

void setupAudioSystem() {
  initAudioSystem();
  irq_add(II_VBLANK, tickAudioSystem);
}
