#include "level.h"

#include "tonc_tte.h"

void generateLevel(u8 currentLevel, Level *level) {
    generateGenMap(&level->genMap, 1, 1, 2 + 2 * currentLevel,
                   2 + 2 * currentLevel);
    fillTilemap(level);
    level->currentLevel = currentLevel;
}
