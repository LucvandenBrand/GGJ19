#ifndef MAPGEN
#define MAPGEN

#include "tonc_types.h"

typedef struct {
  s8 tileX;
  s8 tileY;
} TilePosition;

#define MAP_WIDTH 64
#define MAP_HEIGHT 64
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

typedef enum {
    Empty = 0,
    Wall = 1,
    Bed = 2,
    Toilet = 3
} GenMapTile;

typedef struct {
    GenMapTile ground[MAP_SIZE];
    TilePosition bedPos;
    TilePosition toiletPos;
} GenMap;


void generateGenMap(GenMap *map);

#endif

