#include "stateRenderer.h"
#include "../../../assets/sprites/playerSprite.h"

void initializeStateRenderer(State state) {
    Map map = loadDefaultMap();
    setMapOnScreen(map);

    loadSpriteSheet(playerSpritePal, playerSpritePalLen, playerSpriteTiles, playerSpriteTilesLen);
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    sprites[0] = playerToSpriteObject(state.player);
    copySpriteObjectsToMemory(sprites, NUM_SPRITES);
    setSpritesOnScreen();
}
