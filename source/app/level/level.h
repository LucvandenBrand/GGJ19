#ifndef LEVEL_H
#define LEVEL_H

#include "tonc_types.h"
#include "../mapgen/mapgen.h"
#include "map.h"

typedef unsigned short Tilemap[64 * 64];
typedef struct {
  GenMap genMap;
  Tilemap tilemap;
} Level;

//public
void generateLevel(u8 currentLevel, Level *level);


// private
void fillTilemap(Tilemap *tilemap, GenMap *genMap);

GenMapTile getLevelTile(const Level *level, u8 x, u8 y);
void setLevelTile(Level *level, Map *map, u8 x, u8 y, GenMapTile newTile);
void pickImgForPlace(Tilemap *tile, GenMap *genMap, int x, int y);

#endif //LEVEL_H
