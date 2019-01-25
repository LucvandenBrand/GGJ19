#include "stateRenderer.h"
#include "playerSprite.h"

void initializeStateRenderer(State state) {
    loadSpriteSheet(playerSpritePalette, PLAYER_PAL_LEN, playerSpriteTileSet, PLAYER_TILE_LEN);
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    sprites[0] = playerToSpriteObject(state.player);
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
    setSpritesOnScreen();
}
