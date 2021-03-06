#include "../level/level.h"
#include "../mapgen/mapgen.h"
#include "state.h"

GenMapTile tileUnderPlayer(State state, Level *level) {
    s8 playerX = state.player.position.tileX;
    s8 playerY = state.player.position.tileY;
    return level->genMap.ground[playerY * MAP_WIDTH + playerX];
}
