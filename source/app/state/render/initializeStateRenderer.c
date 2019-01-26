#include "stateRenderer.h"

#include "tonc.h"

//! Get the screen entry index for a tile-coord pair.
/*! This is the fast (and possibly unsafe) way.
 *   \param bgcnt    Control flags for this background (to find its size)
 */

uint se_index_fast2(uint tx, uint ty, u16 bgcnt) {
    uint n = tx + ty * 32;
    if (tx >= 32) n += 0x03E0;
    if (ty >= 32 && (bgcnt & BG_REG_64x64) == BG_REG_64x64) n += 0x0400;
    return n;
}

void createMap(unsigned short *mapdata) {
    for (unsigned int i = 0; i < 64 * 64; ++i) mapdata[i] = 3;

    mapdata[se_index_fast2(2, 3, 0)] = 2 * 20 + 3;
    mapdata[se_index_fast2(2, 2, 0)] = 1 * 20 + 3;
}

void initializeStateRenderer(State state, Map *map, Level *level) {
    /* unsigned short mapdata[64 * 64]; */
    /* createMap(mapdata); */
    /* map.tileMapLayers[0] = mapdata; */
    map->numLayers = 1;
    map->tileMapLayers[0] = level->tilemap;
    /* map.tileMapLayers[1] = NULL; */
    /* map.tileMapLayers[2] = NULL; */
    setMapOnScreen(*map);
    REG_DISPCNT |= DCNT_BG3;  // Because setMapOnScreen destroys it.
    loadSpriteSheet();
    initializeSpriteObjectMemory(sprites, NUM_SPRITES);
    renderState(state, state, 0, 0, IDLE, map);
    /* sprites[0] = playerToSpriteObject(state.player); */
    /* copySpriteObjectsToMemory(sprites, NUM_SPRITES); */
    setSpritesOnScreen();
}
