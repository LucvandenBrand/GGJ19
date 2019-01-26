#include "tonc.h"

#include <stdbool.h>
#include "audio.h"
#include "level/level.h"
#include "simple_rng/simple_rng.h"
#include "state/render/stateRenderer.h"
#include "state/state.h"

#include "./main.h"
#include "setup/setup.h"
#include "tonc_tte.h"

u16 g_winh[SCREEN_HEIGHT + 1];

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

// FROM TONC DMA_DEMO.C
//! Create an array of horizontal offsets for a circular window.
/*!	The offsets are to be copied to REG_WINxH each HBlank, either
 *	  by HDMA or HBlank isr. Offsets provided by modified
 *	  Bresenham's circle routine (of course); the clipping code is not
 *	  optional.
 *	\param winh	Pointer to array to receive the offsets.
 *	\param x0	X-coord of circle center.
 *	\param y0	Y-coord of circle center.
 *	\param rr	Circle radius.
 */
void win_circle(u16 winh[], int x0, int y0, int rr) {
    int x = 0, y = rr, d = 1 - rr;
    u32 tmp;

    // clear the whole array first.
    memset16(winh, 0, SCREEN_HEIGHT + 1);

    while (y >= x) {
        // Side octs
        tmp = clamp(x0 + y, 0, SCREEN_WIDTH + 1);
        tmp += clamp(x0 - y, 0, SCREEN_WIDTH + 1) << 8;

        if (IN_RANGE(y0 - x, 0, SCREEN_HEIGHT))  // o4, o7
            winh[y0 - x] = tmp;
        if (IN_RANGE(y0 + x, 0, SCREEN_HEIGHT))  // o0, o3
            winh[y0 + x] = tmp;

        // Change in y: top/bottom octs
        if (d >= 0) {
            tmp = clamp(x0 + x, 0, SCREEN_WIDTH + 1);
            tmp += clamp(x0 - x, 0, SCREEN_WIDTH + 1) << 8;

            if (IN_RANGE(y0 - y, 0, SCREEN_HEIGHT))  // o5, o6
                winh[y0 - y] = tmp;
            if (IN_RANGE(y0 + y, 0, SCREEN_HEIGHT))  // o1, o2
                winh[y0 + y] = tmp;

            d -= 2 * (--y);
        }
        d += 2 * (x++) + 3;
    }
    winh[SCREEN_HEIGHT] = winh[0];
}

void init_main() {
    // --- Init BG 2 (main bg) ---
    // dma3_cpy(pal_bg_mem, brinPal, brinPalLen);
    // dma3_cpy(tile_mem[0], brinTiles, brinTilesLen);
    // dma3_cpy(se_mem[30], brinMap, brinMapLen);

    // memcpy32(pal_bg_mem, brinPal, brinPalLen/4);
    // memcpy32(tile_mem[0], brinTiles, brinTilesLen/4);
    // memcpy32(se_mem[30], brinMap, brinMapLen/4);

    REG_BG2CNT = BG_CBB(0) | BG_SBB(30) | BG_REG_64x32;
    REG_BG2HOFS = 120;
    REG_BG2VOFS = 64;

    // --- Init BG 1 (mask) ---
    const TILE tile = {{0xF2F3F2F3, 0x3F2F3F2F, 0xF3F2F3F2, 0x2F3F2F3F,
                        0xF2F3F2F3, 0x3F2F3F2F, 0xF3F2F3F2, 0x2F3F2F3F}};
    tile_mem[0][32] = tile;
    pal_bg_bank[4][2] = RGB15(12, 12, 12);
    pal_bg_bank[4][3] = RGB15(8, 8, 8);
    pal_bg_bank[4][15] = RGB15(0, 0, 0);
    se_fill(se_mem[29], 0x4020);

    REG_BG1CNT = BG_CBB(0) | BG_SBB(29);

    // --- Init BG 0 (text) ---
    tte_init_chr4c_b4_default(0, BG_CBB(2) | BG_SBB(28));
    tte_init_con();
    tte_set_margins(8, 8, 232, 40);

    // --- Init window ---
    REG_WIN0H = 0;
    REG_WIN0V = SCREEN_HEIGHT;

    // --- Enable stuff ---
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_WIN0;
    REG_WININ = WIN_BUILD(WIN_BG0 | WIN_BG2, 0);
    REG_WINOUT = WIN_BUILD(WIN_BG0 | WIN_BG1, 0);
}

// Temporary implementation of level generation; will be swapped for Michiel's
// code.
/* typedef void* Level; */

void playLevel(Level *level) {
    State currentState = newStartState(level);
    State oldState = currentState;
    StateMode stateMode = IDLE;
    TimeInFrames currentFrame = 0;
    TimeInFrames transitionFrame = 0;
    Map map = loadDefaultMap();
    /* initializeStateRenderer(currentState, map, level); */
    initializeStateRenderer(currentState, map, level);
    while (true) {
        ++currentFrame;
        switch (stateMode) {
            case IDLE:
                key_poll();
                KeyState keys = key_curr_state();
                if (keys) {
                    oldState = currentState;
                    currentState = updateStateFromKeys(currentState, level);
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

void fade_out_till_end() {
    init_main(); // WARNING: This may break some other backgrounds
    int rr = 0, x0 = 120, y0 = 80;

    while (rr < 145) {
        vid_vsync();
        key_poll();

        rr += 1;
        win_circle(g_winh, x0, y0, rr);

        // Init win-circle HDMA
        DMA_TRANSFER(&REG_WIN0H, &g_winh[1], 1, 3, DMA_HDMA);
    }
}

void playLevels() {
    u8 currentLevel = 1;
    while (true) {
        /* Level level = generateLevel(currentLevel); */
        tte_printf("Level %d\n", currentLevel);
        /* Level level = (Level){.tilemap = {0}, .genMap = {0}}; */
        /* Level level = {.genMap = {.ground = {[0 ... 64*64 - 1] = 0}},
         * .tilemap = {[0 ... 64*64 - 1] = 3}}; */
        Level level;
        generateLevel(currentLevel, &level);
        tte_printf("Level %d generated!\n", currentLevel);
        key_wait_till_hit(KEY_ANY);
        /* wipPrintDungeonMap(level.genMap); */
        fade_out_till_end();
        playLevel(&level);
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
