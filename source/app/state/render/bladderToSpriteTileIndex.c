#include "./stateRenderer.h"

u32 bladderToSpriteTile(u32 bladder) {
    u32 tileIDIndex =
        (u32)((1.0 * bladder / MAX_BLADDER) * NUM_BLADDER_SPRITES);
    return BLADDER_SPRITE_FIRST_TILE + tileIDIndex * 4;
}
