#include "audio.h"
#include "setup.h"
#include "tonc_irq.h"

#include "../music/music.h"

void setupAudioSystem() {
    initAudioSystem();
    /* irq_add(II_VBLANK, tickAudioSystem); */
    irq_add(II_VBLANK, tickAudioSystemSpeedy);
}
