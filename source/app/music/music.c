#include "music.h"
#include <stdio.h>
#include "gbfs.h"
#include "tonc.h"

Audio createEmptyAudio() {
    Audio audio;
    audio.numChannels = 0;
    return audio;
}

static float audioSpeed = 1.0;
static float audioTimer = 0;

Audio loadAudio() {
    u32 audioDataSize = 0;
    const GBFS_FILE* audioFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16* audioData =
        gbfs_get_obj(audioFile, "GameTheme.bin", &audioDataSize);

    if (audioData == NULL) {
        tte_printf("No GBFS audio found.\n");
        return createEmptyAudio();
    }

    return loadAudioFromROM(audioData);
}

void setAudioSpeed(float newSpeed) { audioSpeed = newSpeed; }
void increaseAudioSpeed() { ++audioSpeed; }
void decreaseAudioSpeed() { --audioSpeed; }

void tickAudioSystemSpeedy() {
    audioTimer += audioSpeed;
    while (audioTimer > 1) {
        tickAudioSystem();
        audioTimer -= 1;
    }
    /* for(int index = 0; index < audioSpeed; ++index) { */
    /*   tickAudioSystem(); */
    /* } */
}
