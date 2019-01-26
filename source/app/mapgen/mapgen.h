#ifndef MAPGEN
#define MAPGEN

#include "tonc_types.h"

typedef struct {
  int tileX;
  int tileY;
} TilePosition;

#define MAP_WIDTH 64
#define MAP_HEIGHT 64
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

typedef enum {
    Empty,
    Wall,
    Bed,
    BedLeft,
    Toilet,
    Toileft,
    Duckie,
    Alcohol
} GenMapTile;

typedef struct {
    GenMapTile ground[MAP_SIZE];
    TilePosition bedPos;
    TilePosition toiletPos;
    int xmin;
    int ymin;
    int xmax;
    int ymax;
} GenMap;


void generateGenMap(GenMap *map, u8 currentLevel);

#endif

