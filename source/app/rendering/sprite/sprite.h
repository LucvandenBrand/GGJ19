#ifndef SPRITE_H
#define SPRITE_H

#include "mapObject.h"
#include "tonc.h"

#define PLAYER_SPRITE_TILE 0
#define NUM_BLADDER_SPRITES 5
#define BLADDER_SPRITE_FIRST_TILE 4

void loadSpriteSheet();
void initializeSpriteObjectMemory(OBJ_ATTR *spriteObjects, u32 count);
void hideSpriteObjects(OBJ_ATTR *spriteObjects, u32 count);
void copySpriteObjectsToMemory(const OBJ_ATTR *spriteObjects, u32 count);
void setSpritesOnScreen();
void setSpriteObjectAttributes(OBJ_ATTR* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2);
void setSpriteObjectPosition(OBJ_ATTR* spriteObject, ObjectPoint position);

#endif