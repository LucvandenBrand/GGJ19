#include "audio.h"
#include "setup.h"
#include "tonc_irq.h"

void setupAudioSystem() {
    initAudioSystem();
    irq_add(II_VBLANK, tickAudioSystem);
}
