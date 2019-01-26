#ifndef LEVEL_H
#define LEVEL_H

#include "tonc_types.h"
#include "../mapgen/mapgen.h"

typedef unsigned short Tilemap[64 * 64];
typedef struct {
  GenMap genMap;
  Tilemap tilemap;
} Level;

//public
void generateLevel(u8 currentLevel, Level *level);


// private
void fillTilemap(u8 currentLevel, Tilemap *tilemap, GenMap *genMap);

#endif //LEVEL_H
