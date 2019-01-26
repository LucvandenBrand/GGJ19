#include "level.h"

#include "tonc_tte.h"

void generateLevel(u8 currentLevel, Level *level) {
    tte_printf("Starting level gen\n");
    /* Level level = (Level){.genMap = {0}, .tilemap = {0}}; */
    /* tte_printf("Starting level generation\n"); */
    generateGenMap(&level->genMap, 1, 1, 2 + 2 * currentLevel,
                   2 + 2 * currentLevel);
    tte_printf("GenMap made\n");
    fillTilemap(&level->tilemap, &level->genMap);
    tte_printf("Tilemap filled\n");
    /* return level; */
}
