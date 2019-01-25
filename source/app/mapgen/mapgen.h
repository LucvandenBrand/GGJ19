

#ifndef MAPGEN
#define MAPGEN

#define MAP_WIDTH 64
#define MAP_HEIGHT 64
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

typedef enum {
    Empty = 0,
    Wall = 1,
    Bed = 2,
    Toilet = 3
} Tile;

typedef struct {
    Tile ground[MAP_SIZE];
} Map;


Map generateMap();

#endif

