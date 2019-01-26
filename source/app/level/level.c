
#include "level.h"
#include "map.h"
#include "tonc.h"

GenMapTile getLevelTile(const Level *level, u8 x, u8 y) {
    return level->genMap.ground[x + MAP_WIDTH * y];
}

void setLevelTile(Level *level, Map *map, u8 x, u8 y, GenMapTile newTile) {
    level->genMap.ground[x + MAP_WIDTH * y] = newTile;
    pickImgForPlace(level, x, y);
    level->changed = true;
}
