#ifndef MUSIC_H
#define MUSIC_H
#include "audio.h"

Audio createEmptyAudio();
Audio loadAudio();
void tickAudioSystemSpeedy();
void increaseAudioSpeed(float speed);
void setAudioSpeed(float newSpeed);
void decreaseAudioSpeed(float speed);

#endif
