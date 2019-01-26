#include "level.h"

#include "tonc_core.h"
#include "../simple_rng/simple_rng.h"

uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
    uint n = tx + ty * 32;
    if (tx >= 32) n += 0x03E0;
    if (ty >= 32) n += 0x0400;
    return n;
}

#define CEILING_TILES_OFFSET 0
#define SIDE_WALL_TILES_OFFSET 1 * 20 + 1
#define FLOOR_TILES_OFFSET 2 * 20 + 1
#define FLOOR_TILES_OFFSET2 3 * 20 + 1

#define TOP_WALL1 (CEILING_TILES_OFFSET)
#define SIDE_WALL1 (SIDE_WALL_TILES_OFFSET + 2)
#define SIDE_WALL2 (SIDE_WALL_TILES_OFFSET + 3)
#define SIDE_WALL3 (SIDE_WALL_TILES_OFFSET + 4)

#define SINGLE_TILE_WALL (FLOOR_TILES_OFFSET + 4)

#define BED_LEFT (FLOOR_TILES_OFFSET + 5)
#define BED_RIGHT (FLOOR_TILES_OFFSET + 6)
#define TOILET (FLOOR_TILES_OFFSET2 + 8)
#define FLOOR1 (FLOOR_TILES_OFFSET + 2)
#define FLOOR2 (FLOOR_TILES_OFFSET + 3)
#define FLOOR3 (FLOOR_TILES_OFFSET + 4)
#define FLOOR4 (FLOOR_TILES_OFFSET2 + 2)
#define FLOOR5 (FLOOR_TILES_OFFSET2 + 3)
#define FLOOR6 (FLOOR_TILES_OFFSET2 + 4)
#define FLOOR7 (FLOOR_TILES_OFFSET + 7)
/* #define FLOOR_3 (FLOOR_TILES_OFFSET + 2) */

GenMapTile fetchGenMapTile(int x, int y, const GenMap *genMap) {
  if(x < 0 || x > 63) return Wall;
  if(y < 0 || y > 63) return Wall;
  return genMap->ground[y * MAP_WIDTH + x];
}

uint randomCeilingTile() {
  /* uint32_t rand = SimpleRNG_rand() % 100; */
  uint rand =  SimpleRNG_rand() % 32;
  if (rand < 8) {
    return rand;
  } else {
    return 0;
  }
  /* if(rand < 80) { */
  /*   return SIDE_WALL1; */
  /* } else if (rand < 90) { */
  /*   return SIDE_WALL2; */
  /* } else { */
  /*   return SIDE_WALL3; */
  /* } */
}

uint randomWallTile() {
  uint32_t rand = SimpleRNG_rand() % 100;
  if(rand < 80) {
    return SIDE_WALL1;
  } else if (rand < 90) {
    return SIDE_WALL2;
  } else {
    return SIDE_WALL3;
  }
}

uint randomFloorTile() {
  uint32_t rand = SimpleRNG_rand() % 100;
  if(rand < 80) {
    return FLOOR1;
  }else if(rand < 85) {
    return FLOOR2;
  }else if (rand < 85) {
    return FLOOR3;
  } else if (rand < 87) {
    return FLOOR4;
  } else if (rand < 92) {
    return FLOOR5;
  } else if (rand < 96) {
    return FLOOR6;
  } else {
    return FLOOR7;
  }
}


void fillTilemap(Tilemap *tilemap, GenMap *genMap) {
    for (unsigned int i = 0; i < 64 * 64; ++i) {
        (*tilemap)[i] = 2 * 20 + 3;
    }
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            unsigned short tileImg = 0;
            switch (fetchGenMapTile(x, y, genMap)) {
            case Bed:
              tileImg = BED_LEFT;
              break;
            case Toilet:
              tileImg = TOILET;
              break;
                case Empty:
                  /* tileImg = FLOOR1 + (SimpleRNG_rand() % 3); */
                  tileImg = randomFloorTile();
                    break;
                case Wall:
                  if(fetchGenMapTile(x, y+1, genMap) != Wall) {
                    if(fetchGenMapTile(x, y - 1, genMap) != Wall) {
                      tileImg = SINGLE_TILE_WALL;
                    } else {
                      /* tileImg = SIDE_WALL1 + (SimpleRNG_rand() % 3); */
                      tileImg = randomWallTile();
                    }
                  } else {
                    tileImg = 1 + randomCeilingTile();
                  }
                    break;
            }

            (*tilemap)[se_index_fast(x, y, REG_BG0CNT)] = tileImg;
        }
    }
    /* (*tilemap)[i] = genMap->ground[i]; */

    /* *tilemap[se_index_fast(2, 3, 0)] = 2 * 20 + 3; */
    /* *tilemap[se_index_fast(2, 2, 0)] = 1 * 20 + 3; */
}
