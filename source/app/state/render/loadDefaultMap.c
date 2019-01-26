#include "stateRenderer.h"
#include "gbfs.h"

Map loadDefaultMap() {
    u32 mapDataSize = 0;
    const GBFS_FILE* gbfsFile = find_first_gbfs_file(find_first_gbfs_file);
    const u16* mapData = gbfs_get_obj(gbfsFile, "defaultMap.bin", &mapDataSize);

    return loadMapFromROM(mapData);
}