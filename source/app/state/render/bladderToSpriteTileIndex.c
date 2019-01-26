#include "./stateRenderer.h"

u32 bladderToSpriteTile(u32 bladder) {
    u32 tileIDIndex = (u32) ((0.7 * bladder / MAX_BLADDER) * NUM_BLADDER_SPRITES);
    return BLADDER_SPRITE_FIRST_TILE + tileIDIndex * 4;
}