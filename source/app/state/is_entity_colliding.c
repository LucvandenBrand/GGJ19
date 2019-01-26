#include "state.h"

bool isEntityColliding(Entity entity, Level *level) {
    s8 posX = entity.position.tileX;
    s8 posY = entity.position.tileY;
    return level->genMap.ground[posY * MAP_WIDTH + posX] == Wall;
}
