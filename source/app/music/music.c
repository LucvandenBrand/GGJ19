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

Audio loadAudio(const char* audioFileName) {
    u32 audioDataSize = 0;
    const GBFS_FILE* gbfsPackedFile =
        find_first_gbfs_file(find_first_gbfs_file);
    const u16* audioData =
        gbfs_get_obj(gbfsPackedFile, audioFileName, &audioDataSize);

    if (audioData == NULL) {
        tte_printf("No GBFS audio found.\n");
        return createEmptyAudio();
    }
    setAudioSpeed(1);
    return loadAudioFromROM(audioData);
}

void setAudioSpeed(float newSpeed) { audioSpeed = newSpeed; }
void increaseAudioSpeed(float speed) { audioSpeed += speed; }
void decreaseAudioSpeed(float speed) { audioSpeed -= speed; }

void tickAudioSystemSpeedy() {
    audioTimer += audioSpeed;
    while (audioTimer > 1) {
        tickAudioSystem();
        audioTimer -= 1;
    }
}
