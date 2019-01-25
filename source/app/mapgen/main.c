

/* for testing out on computers */

#include <stdio.h>

#include "mapgen.h"
#include "../simple_rng/simple_rng.h"

char chars[] = ".#??????????";

void printMap(Map map){
    for (int i=0; i<MAP_SIZE; i++){
        putchar(chars[map.ground[i]]);
        if ((i+1) % MAP_WIDTH == 0){
            putchar('\n');
        }
    }
}



int main(int argc, char *argv[]){
    
    SimpleRNG_seed(101);
    
    Map map = generateMap();
    
    printMap(map);
    
    return 0;
}
