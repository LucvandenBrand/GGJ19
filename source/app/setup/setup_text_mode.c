#include "setup.h"

#include "tonc.h"

void setupTextMode() {
  tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
  tte_init_con();
}
