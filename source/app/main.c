#include "tonc.h"

#include <stdbool.h>
#include "audio.h"
#include "simple_rng/simple_rng.h"
#include "state/render/stateRenderer.h"
#include "state/state.h"

#include "./main.h"
#include "setup/setup.h"
#include "tonc_tte.h"

#include "mapgen/mapgen.h"

void seedRNGByKeyPress() {
    /* fake seeding by just fetching numbers until key is pressed. */
    while (1) {
        vid_vsync();
        SimpleRNG_rand();
        key_poll();
        if (key_hit(KEY_ANY)) {
            break;
        }
    }
}

uint se_index_fast(uint tx, uint ty, u16 bgcnt) {
  uint n = tx + ty * 32;
  if (tx >= 32) n += 0x03E0;
  if (ty >= 32 && (bgcnt & BG_REG_64x64) == BG_REG_64x64) n += 0x0400;
  return n;
}

// Temporary implementation of level generation; will be swapped for Michiel's
// code.
/* typedef void* Level; */
typedef unsigned short Tilemap[64 * 64];
typedef struct {
    GenMap genMap;
    Tilemap tilemap;
} Level;

void fillTilemap(Tilemap *tilemap, GenMap *genMap) {
  for (unsigned int i = 0; i < 64 * 64; ++i) *tilemap[i] = 3;

  *tilemap[se_index_fast(2, 3, 0)] = 2 * 20 + 3;
  *tilemap[se_index_fast(2, 2, 0)] = 1 * 20 + 3;
}

void generateLevel(u8 currentLevel, Level *level) {
  tte_printf("Starting level gen\n");
  /* Level level = (Level){.genMap = {0}, .tilemap = {0}}; */
    /* tte_printf("Starting level generation\n"); */
    generateGenMap(&level->genMap);
    tte_printf("GenMap made\n");
    fillTilemap(&level->tilemap, &level->genMap);
    tte_printf("Tilemap filled\n");
    /* return level; */
}

void playLevel(Level level) {
    State currentState = newStartState();
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    Map map = loadDefaultMap();
    /* initializeStateRenderer(currentState, map, level); */
    initializeStateRenderer(currentState, map);
    while (true) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState);
                    stateMode = TRANSIT;
                    transitionFrame = currentFrame;
                }
                break;
            case TRANSIT:
                if (isTransitionFinished(transitionFrame, currentFrame)) {
                    stateMode = IDLE;
                }
                break;
        }
        renderState(oldState, currentState, transitionFrame, currentFrame,
                    stateMode, map);
        /* tte_printf(" %d", stateMode); */
        /* vid_vsync(); */
        /* VBlankIntrWait(); */
    };
}

void wipPrintDungeonMap(GenMap map) {
  REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
  for (int x = 0; x < MAP_WIDTH; ++x) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
      GenMapTile tile = map.ground[y * MAP_WIDTH + x];
      switch (tile) {
      case Empty:
        m3_plot(x, y, CLR_YELLOW);
        break;
      case Wall:
        m3_plot(x, y, CLR_BLACK);
        break;
      case Bed:
        m3_plot(x, y, CLR_CYAN);
        break;
      case Toilet:
        m3_plot(x, y, CLR_RED);
        break;
      }
    }
  }
  while (true) {
  };
}


void playLevels() {
    u8 currentLevel = 1;
    while (true) {
        /* Level level = generateLevel(currentLevel); */
      tte_printf("Level %d\n", currentLevel);
      /* Level level = (Level){.tilemap = {0}, .genMap = {0}}; */
      Level level = {.genMap = {.ground = {[0 ... 64*64 - 1] = 0}}, .tilemap = {[0 ... 64*64 - 1] = 3}};
      generateLevel(currentLevel, &level);
        tte_printf("Level %d generated!\n", currentLevel);
        key_wait_till_hit(KEY_ANY);
      /* wipPrintDungeonMap(level.genMap); */
        playLevel(level);
        ++currentLevel;
    }
}

int main() {
    setupGBA();
    tte_printf("Press any key\n");
    seedRNGByKeyPress();
    tte_printf("Starting...\n");
    playLevels();

    /* Map map = generateMap(); */
    /* wipPrintDungeonMap(map); */
    /* playLevels(); */
}
