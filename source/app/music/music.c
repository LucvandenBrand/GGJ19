#include "tonc.h"
#include "music.h"
#include "gbfs.h"
#include <stdio.h>


Audio createEmptyAudio() {
    Audio audio;
    audio.numChannels = 0;
    return audio;
}

Audio loadAudio() {
    u32 audioDataSize = 0;
    const GBFS_FILE* audioFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16* audioData =
            gbfs_get_obj(audioFile, "Test00.bin", &audioDataSize);

    if (audioData == NULL) {
        tte_printf("No GBFS audio found.\n");
        return createEmptyAudio();
    }

    return loadAudioFromROM(audioData);
}