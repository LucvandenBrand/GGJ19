
#include "mapgen.h"
#include "../simple_rng/simple_rng.h"

#define IS_EDGE(i) ((i) % MAP_WIDTH == 0 || (i) % MAP_WIDTH == MAP_WIDTH - 1 || (i) / MAP_WIDTH == 0 || (i) / MAP_WIDTH == MAP_HEIGHT-1)
#define INDEX(x, y) ((x) + (y) * MAP_WIDTH)

#define RAND(n) SimpleRNG_rand()%(n)
#define MAX_WORMS 10


typedef enum {
    North = 0,
    East = 1,
    South = 2,
    West = 3
} Direction;

void worm(Map *map, int pos, int life){
    int worms[MAX_WORMS];
    int nworms = 1;
    worms[0] = pos;
    while (life--){
        int worm = RAND(nworms);
        pos = worms[worm];
        Direction direction = RAND(4);
        int dpos = (direction == West) - (direction == East) + MAP_WIDTH * (direction == South) - (direction == North);
        int length = 3 + RAND(10);
        while (length--){
            int npos = pos + dpos;
//             if (map->ground[npos] == Empty){
//                 direction = RAND(4);
//                 dpos = (direction == West) - (direction == East) + MAP_WIDTH * (direction == South) - (direction == North);
//             }
            if (IS_EDGE(npos)){
                break;
            }
            pos = npos;
            map->ground[pos] = Empty;
        }
        worms[worm] = pos;
//         if (RAND(30) == 0 && nworms < MAX_WORMS){
//             worms[nworms++] = pos;
//         }
    }
}



Map generateMap(){
    Map map;
    for (int i=0; i<MAP_SIZE; i++){
        map.ground[i] = Wall;
    }
    
    worm(&map, RAND(MAP_SIZE), 10);
    
    return map;
}

