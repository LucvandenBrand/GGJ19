#include "setup.h"

#include "tonc.h"

void setupTextMode() {
    tte_init_se_default(3, BG_CBB(1) | BG_SBB(31));
    tte_init_con();
}
