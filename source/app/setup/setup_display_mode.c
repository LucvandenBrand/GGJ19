#include "setup.h"
#include "tonc_core.h"

void setupDisplayMode() { REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG3; }
