

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
#define GET(map, x, y) (map->ground[INDEX(x, y)])

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
    map->bedPos.tileX = pos % MAP_WIDTH;
    map->bedPos.tileY = pos / MAP_WIDTH;
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
    map->toiletPos.tileX = worms[0] % MAP_WIDTH;
    map->toiletPos.tileY = worms[0] / MAP_WIDTH;

    map->ground[map->bedPos.tileY * MAP_WIDTH + map->bedPos.tileX] = Bed;
    map->ground[map->toiletPos.tileY * MAP_WIDTH + map->toiletPos.tileX] =
        Toilet;
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



void bsp(GenMap *map, int xmin, int ymin, int xmax, int ymax, int d){
    if (d == 0 || RAND(9) == 0){
        if (RAND(5) == 0 && map->bedPos.tileX < 0){
            map->bedPos.tileX = xmax-1;
            map->bedPos.tileY = ymax-1;
        } else if (RAND(5) == 0){
            map->toiletPos.tileX = xmax-1;
            map->toiletPos.tileY = ymax-1;
        }
        return;
    }
    if (ymax - ymin >= 5 && (xmax - xmin < 5 || RAND(2))){
        // horizontal wall
        
        int sepmin = ymin + 1 + RAND(ymax - ymin - 3);
        int sepmax = sepmin + 2 + RAND(2);
        sepmax = MIN(ymax-1, sepmax);
        for (int x=xmin; x<xmax; ++x){
            for (int y=sepmin; y<sepmax; ++y){
                map->ground[INDEX(x, y)] = Wall;
            }
        }
        bsp(map, xmin, ymin, xmax, sepmin, d-1);
        bsp(map, xmin, sepmax, xmax, ymax, d-1);
        int l = xmax - xmin;
        int dp = RAND(l);
        for (int i=0; i<l; ++i){
            
            int doorposmin = INDEX(xmin + (i + dp) % l, sepmin);
            int doorposmax = INDEX(xmin + (i + dp) % l, sepmax);
            if (map->ground[doorposmax] == Empty && map->ground[doorposmin - MAP_WIDTH] == Empty){
                for (int p=doorposmin; p<doorposmax; p+=MAP_WIDTH){
                    map->ground[p] = Empty;
                }
                break;
            }
           
        }
    } else if (xmax - xmin >=5){
        // vertical wall
        int sepmin = xmin + 1 + RAND(xmax - xmin - 3);
        int sepmax = sepmin + 2 + RAND(2);
        sepmax = MIN(xmax-1, sepmax);
        
        for (int y=ymin; y<ymax; ++y){
            for (int x=sepmin; x<sepmax; ++x){
                map->ground[INDEX(x, y)] = Wall;
            }
        }
        bsp(map, xmin, ymin, sepmin, ymax, d-1);
        bsp(map, sepmax, ymin, xmax, ymax, d-1);
        int l = ymax - ymin;
        int dp = RAND(l);
        for (int i=0; i<l; ++i){
            int doorposmin = INDEX(sepmin, ymin + (i + dp) % l);
            int doorposmax = INDEX(sepmax, ymin + (i + dp) % l);
            if (
                    map->ground[doorposmax] == Empty &&
                    map->ground[doorposmin - 1] == Empty){
                for (int p=doorposmin; p<doorposmax; ++p){
                    map->ground[p] = Empty;
                }
                break;
            }
        }
    } 
}



void generateGenMap(GenMap *map, int xmin, int ymin, int xmax, int ymax) {
    for (int x=0; x<MAP_WIDTH; x++){
        for (int y=0; y<MAP_HEIGHT; y++){
            map->ground[INDEX(x, y)] = (x<xmin || y<ymin || x>=xmax || y>=ymax) ? Wall : Empty;
        }
    }
    map->bedPos.tileX = -1;
    map->bedPos.tileY = -1;
    map->toiletPos.tileX = -1;
    map->toiletPos.tileY = -1;
    bsp(map, xmin, ymin, xmax, ymax, 8);
    if (map->bedPos.tileX < 0){
        map->bedPos.tileX = xmin;
        map->bedPos.tileY = ymin;
    }
    if (map->toiletPos.tileX < 0){
        map->toiletPos.tileX = xmax-1;
        map->toiletPos.tileY = ymax-1;
    }
    map->ground[INDEX(map->bedPos.tileX, map->bedPos.tileY)] = Bed;
    map->ground[INDEX(map->toiletPos.tileX, map->toiletPos.tileY)] = Toilet;
//     worm(map, RAND(MAP_SIZE), 1050);

}
