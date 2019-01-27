#include "level.h"

#include "../simple_rng/simple_rng.h"
#include "tonc_core.h"

uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
    uint n = tx + ty * 32;
    if (tx >= 32) n += 0x03E0;
    if (ty >= 32) n += 0x0400;
    return n;
}


#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define CEILING_TILES_OFFSET 0
#define SIDE_WALL_TILES_OFFSET 1 * 20 + 1
#define FLOOR_TILES_OFFSET 2 * 20 + 1
#define FLOOR_TILES_OFFSET2 3 * 20 + 1
#define FLOOR_TILES_OFFSET3 4 * 20 + 1

#define TOP_WALL1 (CEILING_TILES_OFFSET)
#define SIDE_WALL1 (SIDE_WALL_TILES_OFFSET + 2)
//#define SIDE_WALL2 (SIDE_WALL_TILES_OFFSET + 3)
//#define SIDE_WALL3 (SIDE_WALL_TILES_OFFSET + 4)

#define SINGLE_TILE_WALL (FLOOR_TILES_OFFSET3 + 6)

#define BED_LEFT (FLOOR_TILES_OFFSET + 5)
#define BED_RIGHT (FLOOR_TILES_OFFSET + 6)
#define TOILET_LEFT (FLOOR_TILES_OFFSET2 + 7)
#define TOILET_RIGHT (FLOOR_TILES_OFFSET2 + 8)
#define DUCKIE (FLOOR_TILES_OFFSET2 + 9)
#define CROWN (FLOOR_TILES_OFFSET + 9)
#define DIAPER (FLOOR_TILES_OFFSET2 + 10)
#define SAXOPHONE (FLOOR_TILES_OFFSET2 + 11)
#define ALCOHOL (FLOOR_TILES_OFFSET + 8)
#define FLOOR1 (FLOOR_TILES_OFFSET + 2)
#define FLOOR2 (FLOOR_TILES_OFFSET + 3)
#define FLOOR3 (FLOOR_TILES_OFFSET + 4)
#define FLOOR4 (FLOOR_TILES_OFFSET2 + 2)
#define FLOOR5 (FLOOR_TILES_OFFSET2 + 3)
#define FLOOR6 (FLOOR_TILES_OFFSET2 + 4)
#define FLOOR7 (FLOOR_TILES_OFFSET + 7)

#define FLOOR_HELL_1 (FLOOR_TILES_OFFSET + 10)
#define FLOOR_HELL_2 (FLOOR_TILES_OFFSET + 11)
/* #define FLOOR_3 (FLOOR_TILES_OFFSET + 2) */

GenMapTile fetchLevelTile(const Level *level, int x, int y) {
    if (x < 0 || x > 63) return Wall;
    if (y < 0 || y > 63) return Wall;
    return getLevelTile(level, x, y);
}

uint randomCeilingTile(u8 currentLevel) {
    /* uint32_t rand = SimpleRNG_rand() % 100; */
    uint rand = SimpleRNG_rand() % 32;
    if (rand < 8) {
        return rand;
    } else if (currentLevel >= 16 && rand < 12) {
        uint rand2 = SimpleRNG_rand() % 25;
        if (rand2 < currentLevel-16) {
            return rand;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

uint randomWallTile(u8 currentLevel) {
    uint32_t rand = SimpleRNG_rand() % 25;
    if (rand < 10) {
        return SIDE_WALL_TILES_OFFSET + rand;
    } else if (currentLevel > 10 && rand < 11) {
        return SIDE_WALL_TILES_OFFSET + rand;
    } else if (currentLevel > 12 && rand < 12) {
        return SIDE_WALL_TILES_OFFSET + rand;
    } else {
        return SIDE_WALL1;
    }
}

uint randomFloorTile(u8 currentLevel) {
    uint32_t rand = SimpleRNG_rand() % 100;
    if (rand < 1) {
        return FLOOR1;
    } else if (rand < 2) {
        return FLOOR7;
    } else if (rand < 4) {
        return FLOOR6;
    } else if (rand < 7) {
        return FLOOR5;
    } else if (rand < 9) {
        return FLOOR4;
    } else if (rand < 17) {
        return FLOOR3;
    } else if (rand < 25) {
        return FLOOR2;
    } else if (currentLevel >= 5) {
        if (currentLevel >= 7 && SimpleRNG_rand() % 50 < MIN((currentLevel-7), 25)) {
            return FLOOR_HELL_2;
        } 
        if (SimpleRNG_rand() % 30 < MIN((currentLevel-5), 7)) {
            return FLOOR_HELL_1;
        }
    }

    return FLOOR1;
}

void pickImgForPlace(Level *level, int x, int y) {
    unsigned short tileImg = 0;
    switch (getLevelTile(level, x, y)) {
        case Bed:
            tileImg = BED_RIGHT;
            //                     (*tilemap)[se_index_fast(x - 1, y,
            //                     REG_BG0CNT)] = BED_LEFT;
            break;
        case BedLeft:
            tileImg = BED_LEFT;
            //                     (*tilemap)[se_index_fast(x - 1, y,
            //                     REG_BG0CNT)] = BED_LEFT;
            break;
        case Toilet:
            tileImg = TOILET_RIGHT;
            //                     (*tilemap)[se_index_fast(x - 1, y,
            //                     REG_BG0CNT)] =
            //                         TOILET_LEFT;
            break;
        case Toileft:
            tileImg = TOILET_LEFT;
            break;
        case Duckie:
            tileImg = DUCKIE;
            break;
        case Alcohol:
            tileImg = ALCOHOL;
            break;
        case Diaper:
            tileImg = DIAPER;
            break;
        case Flowers:
            tileImg = SINGLE_TILE_WALL;
            break;
    case Saxophone:
      tileImg = SAXOPHONE;
      break;
        case Empty:
            /* tileImg = FLOOR1 + (SimpleRNG_rand() % 3); */
            tileImg = randomFloorTile(level->currentLevel);
            break;
        case Wall:
            if (fetchLevelTile(level, x, y + 1) != Wall) {
                if (fetchLevelTile(level, x, y - 1) != Wall) {
                    tileImg = SINGLE_TILE_WALL;
                } else {
                    /* tileImg = SIDE_WALL1 + (SimpleRNG_rand() % 3); */
                    tileImg = randomWallTile(level->currentLevel);
                }
            } else {
                tileImg = 1 + randomCeilingTile(level->currentLevel);
            }
            break;
    }

    (level->tilemap)[se_index_fast(x, y, REG_BG0CNT)] = tileImg;
}

void fillTilemap(Level *level) {
    for (unsigned int i = 0; i < 64 * 64; ++i) {
        (level->tilemap)[i] = 2 * 20 + 3;
    }
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            pickImgForPlace(level, x, y);
        }
    }
}
