
#include "level.h"

GenMapTile getLevelTile(const Level *level, u8 x, u8 y){
    return level->genMap.ground[x + MAP_WIDTH * y];
}

void setLevelTile(Level *level, u8 x, u8 y, GenMapTile newTile){
    level->genMap.ground[x + MAP_WIDTH * y] = newTile;
    pickImgForPlace(&(level->tilemap), &(level->genMap), x, y);
}
