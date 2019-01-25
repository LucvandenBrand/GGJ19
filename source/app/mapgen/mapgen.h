

#ifndef MAPGEN
#define MAPGEN

#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define MAP_SIZE 1024 // WIDTH*HEIGHT

typedef enum {
    Empty = 0,
    Wall = 1
} Tile;

typedef struct {
    Tile ground[MAP_SIZE];
} Map;


Map generateMap();

#endif

