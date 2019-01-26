#ifndef SPRITE_H
#define SPRITE_H

#include "mapObject.h"
#include "tonc.h"

void loadSpriteSheet(const unsigned short * spritePalette, unsigned spritePaletteLength,
                const unsigned int * spriteTileSet, unsigned spriteTileSetLength);
void initializeSpriteObjectMemory(OBJ_ATTR *spriteObjects, u32 count);
void hideSpriteObjects(OBJ_ATTR *spriteObjects, u32 count);
void copySpriteObjectsToMemory(const OBJ_ATTR *spriteObjects, u32 count);
void setSpritesOnScreen();
void setSpriteObjectAttributes(OBJ_ATTR* spriteObject, u16 attribute0, u16 attribute1, u16 attribute2);
void setSpriteObjectPosition(OBJ_ATTR* spriteObject, ObjectPoint position);

#endif