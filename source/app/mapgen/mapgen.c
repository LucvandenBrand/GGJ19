

#include "mapgen.h"
#include "../simple_rng/simple_rng.h"

#define IS_EDGE(i)                                               \
    ((i) % MAP_WIDTH == 0 || (i) % MAP_WIDTH == MAP_WIDTH - 1 || \
     (i) / MAP_WIDTH == 0 || (i) / MAP_WIDTH == MAP_HEIGHT - 1)
#define INDEX(x, y) ((x) + (y)*MAP_WIDTH)
#define RAND(n) (SimpleRNG_rand() % (n))
#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))
#define RANDOM_POS() (INDEX(1 + RAND(MAP_WIDTH - 2), 1 + RAND(MAP_HEIGHT - 2)))
#define MOVEMENT(direction)                                  \
    (((direction) % 4 == West) - ((direction) % 4 == East) + \
     MAP_WIDTH * (((direction) % 4 == South) - ((direction) % 4 == North)))
#define MOVE(pos, dir) (pos + MOVEMENT(dir))

#define MAX_WORMS 10

typedef enum { North = 0, East = 1, South = 2, West = 3 } Direction;

void fillSquare(GenMap *map, int xmin, int ymin, int xmax, int ymax, GenMapTile val) {
    for (int xx = xmin; xx < xmax; ++xx) {
        for (int yy = ymin; yy < ymax; ++yy) {
            map->ground[INDEX(xx, yy)] = val;
        }
    }
}

void makeRoom(GenMap *map, int pos, int minsize, int maxsize) {
    int x = pos % MAP_WIDTH;
    int y = pos / MAP_WIDTH;
    int xmin = x - (RAND(maxsize - minsize) + minsize) / 2;
    int ymin = y - (RAND(maxsize - minsize) + minsize) / 2;
    int xmax = x + (RAND(maxsize - minsize) + minsize) / 2;
    int ymax = y + (RAND(maxsize - minsize) + minsize) / 2;
    xmin = MAX(1, xmin);
    ymin = MAX(1, ymin);
    xmax = MIN(MAP_WIDTH - 2, xmax);
    ymax = MIN(MAP_HEIGHT - 2, ymax);
    fillSquare(map, xmin, ymin, xmax, ymax, Empty);
    //     for (int i = xmin; i < xmax; ++i) {
    //         for (int j = ymin; j < ymax; ++j) {
    //             map->ground[i + j * MAP_WIDTH] = 0;
    //         }
    //     }
    //     if (RAND(2)){
    //         int y = RAND(ymax-ymin)+ymin;
    //         if (xmin == 1 || RAND(2)){
    //             return INDEX(xmax, y);
    //         } else {
    //             return INDEX(xmin - 1, y);
    //         }
    //     } else {
    //         int x = RAND(xmax-xmin)+xmin;
    //         if (ymin == 1 || RAND(2)){
    //             return INDEX(x, ymax);
    //         } else {
    //             return INDEX(x, ymin-1);
    //         }
    //     }
}

int random_wall_pos(GenMap *map, int ntries) {
    for (int i = 0; i < ntries; ++i) {
        int pos = RANDOM_POS();
        for (int dir = 0; dir < 4; ++dir) {
            if (map->ground[MOVE(pos, dir)] != Wall) {
                return pos;
            }
        }
    }
    return -1;
}

void worm(GenMap *map, int pos, int life) {
    int bedpos = pos;
    int worms[MAX_WORMS];
    int nworms = 1;
    worms[0] = pos;
    while (life--) {
        int worm = RAND(MIN(nworms, MAX_WORMS));
        pos = worms[worm];
        // random direction
        Direction direction = RAND(4);
        int dpos;
        // if direction is already in use, find rotate until free pos found
        int ddir = RAND(2) * 2 + 1;
        int i;
        for (i = 0; i < 3; ++i) {
            dpos = MOVEMENT(direction);
            int npos = pos + dpos;
            if (map->ground[npos] == Empty || IS_EDGE(npos)) {
                direction = (direction + ddir) % 4;
            } else {
                break;
            }
        }
        // if all surrounding posisitions in use, move to random position
        if (i == 3) {
            int p = random_wall_pos(map, 100);
            if (p >= 0) {
                worms[worm] = p;
            }
            continue;
        }
        int length = 3 + RAND(10);
        while (length--) {
            int npos = pos + dpos;
            if (IS_EDGE(npos) || map->ground[MOVE(npos, direction)] != Wall ||
                map->ground[MOVE(npos, direction + 1)] != Wall ||
                map->ground[MOVE(npos, direction + 3)] != Wall) {
                break;
            }
            pos = npos;
            map->ground[pos] = Empty;
        }
        worms[worm] = pos;
        if (RAND(5) == 0) {
            worms[(nworms++)%MAX_WORMS] = pos;
        } else if (RAND(25) == 0) {
            makeRoom(map, pos, 4, 6);
            int p = random_wall_pos(map, 100);
            if (p >= 0) {
                worms[worm] = p;
            }
            //             worms[worm] = random_wall_pos(map, 100);
        }
    }
    map->ground[bedpos] = Bed;
    map->bedPos.tileX = bedpos % MAP_WIDTH;
    map->bedPos.tileY = bedpos / MAP_WIDTH;
    map->ground[worms[0]] = Toilet;
    map->toiletPos.tileX = worms[0] % MAP_WIDTH;
    map->toiletPos.tileY = worms[0] / MAP_WIDTH;

    map->ground[map->bedPos.tileY * MAP_WIDTH + map->bedPos.tileX] = Bed;
}

// int isValue(Map *map, x, y, width, height, val){
//     for (int x = xmin; x < xmax; ++x) {
//         for (int y = ymin; y < ymax; ++y) {
//             if (map->ground[INDEX(x, y)] != val){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void wallFeatures(Map *map, ntries) {
//     int start = INDEX(MAP_WIDTH / 2, MAP_HEIGHT / 2);
//     makeRoom(map, start, 4, 10);
//     for (int i=0; i<ntries; ++i){
//         int pos = RANDOM_POS();
//         int builddir = -1;
//         for (int dir=0; dir<4; ++dir){
//             if (map->ground[MOVE(pos, dir)] != WALL){
//                 builddir = (dir + 2) % 4;
//             }
//         }
//         if (builddir < 0){
//             continue;
//         }






void generateGenMap(GenMap *map) {
    for (int i = 0; i < MAP_SIZE; ++i) {
        map->ground[i] = Wall;
    }
    worm(map, RAND(MAP_SIZE), 1050);

    /* return map; */
}
