#include "level.h"

#include "tonc_tte.h"

void generateLevel(u8 currentLevel, Level *level) {
    level->currentLevel = currentLevel;
    generateGenMap(&level->genMap, currentLevel);
    fillTilemap(level);
}
