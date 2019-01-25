#include "tonc.h"

#include "simple_rng/simple_rng.h"
#include "music/music.h"

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

int main() {
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
    tte_init_con();

    initAudioSystem();
    irq_init(NULL);
    irq_add(II_VBLANK, tickAudioSystem);

    tte_printf("Press any key\n");
    seedRNGByKeyPress();
    tte_printf("Using seed: %lu\n", SimpleRNG_rand());

    tte_printf("Now playing audio.\n");
    Audio audio = loadAudio();
    setCurrentAudio(&audio);

    tte_printf("\nKind regards,\nSnappy Cobra");

    while (1) {
    };
}
