#include "stateRenderer.h"

#include "tonc.h"

void initializeStateRenderer(State state, Map *map, Level *level) {
    map->numLayers = 1;
    map->tileMapLayers[0] = level->tilemap;
    setMapOnScreen(*map);
    REG_DISPCNT |= DCNT_BG3;  // Because setMapOnScreen destroys it.
    loadSpriteSheet();
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    renderState(state, state, 0, 0, IDLE, map);
    setSpritesOnScreen();
}
