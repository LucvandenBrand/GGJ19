#include "level.h"

#include "tonc_core.h"

uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
  uint n = tx + ty * 32;
  if (tx >= 32) n += 0x03E0;
  if (ty >= 32 && (bgcnt & BG_REG_64x64) == BG_REG_64x64) n += 0x0400;
  return n;
}

void fillTilemap(Tilemap *tilemap, GenMap *genMap) {
  /* for (unsigned int i = 0; i < 64 * 64; ++i) { */
  for(int x = 0; x < MAP_WIDTH; ++x) {
    for(int y = 0; y < MAP_HEIGHT; ++y) {
      unsigned short tileImg = 0;
      switch(genMap->ground[y * MAP_WIDTH + x]) {
        case Empty:
          tileImg = 2 * 20 + 3;
          break;
        case Wall:
          tileImg = 1 * 20 + 3;
          break;
        default:
          tileImg = 3;
          break;
      }

        *tilemap[se_index_fast(x, y, 0)] = tileImg;
    }
  }
    /* (*tilemap)[i] = genMap->ground[i]; */

  /* *tilemap[se_index_fast(2, 3, 0)] = 2 * 20 + 3; */
  /* *tilemap[se_index_fast(2, 2, 0)] = 1 * 20 + 3; */
}
