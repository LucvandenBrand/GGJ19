
#include <stdio.h>

#include "../simple_rng/simple_rng.h"
#include "mapgen.h"

#define IS_EDGE(i)                                               \
    ((i) % MAP_WIDTH == 0 || (i) % MAP_WIDTH == MAP_WIDTH - 1 || \
     (i) / MAP_WIDTH == 0 || (i) / MAP_WIDTH == MAP_HEIGHT - 1)
#define INDEX(x, y) ((x) + (y)*MAP_WIDTH)
#define RAND(n) SimpleRNG_rand() % (n)
#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))

#define MAX_WORMS 10

typedef enum { North = 0, East = 1, South = 2, West = 3 } Direction;

void makeRoom(Map *map, int pos) {
    int x = pos % MAP_WIDTH;
    int y = pos / MAP_WIDTH;
    int xmin = x - RAND(8) - 1;
    int ymin = y - RAND(8) - 1;
    int xmax = x + RAND(8) + 1;
    int ymax = y + RAND(8) + 1;
    xmin = MAX(1, xmin);
    ymin = MAX(1, ymin);
    xmax = MIN(MAP_WIDTH - 2, xmax);
    ymax = MIN(MAP_HEIGHT - 2, ymax);
    for (int i = xmin; i < xmax; ++i) {
        for (int j = ymin; j < ymax; ++j) {
            map->ground[i + j * MAP_WIDTH] = 0;
        }
    }
}

void worm(Map *map, int pos, int life) {
    map->ground[pos] = Bed;
    int worms[MAX_WORMS];
    int nworms = 1;
    worms[0] = pos;
    while (life--) {
        int worm = RAND(nworms);
        pos = worms[worm];
        Direction direction = RAND(4);
        int dpos;
        int ddir = RAND(2) * 2 + 1;
        for (int i = 0; i < 3; i++) {
            dpos = (direction == West) - (direction == East) +
                   MAP_WIDTH * ((direction == South) - (direction == North));
            int npos = pos + dpos;
            if (map->ground[npos] == Empty || IS_EDGE(npos)) {
                direction = (direction + ddir) % 4;
            }
        }
        int length = 3 + RAND(5);
        while (length--) {
            int npos = pos + dpos;
            if (IS_EDGE(npos)) {
                break;
            }
            pos = npos;
            map->ground[pos] = Empty;
        }
        worms[worm] = pos;
        if (RAND(9) == 0 && nworms < MAX_WORMS) {
            worms[nworms++] = pos;
        }
        if (RAND(7) == 0) {
            makeRoom(map, pos);
        }
    }
    map->ground[worms[0]] = Toilet;
}

Map generateMap() {
    Map map;
    for (int i = 0; i < MAP_SIZE; i++) {
        map.ground[i] = Wall;
    }
    worm(&map, RAND(MAP_SIZE), 220);

    return map;
}
