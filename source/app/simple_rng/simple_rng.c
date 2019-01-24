#include "simple_rng.h"

uint32_t SimpleRNG_rand_r(uint32_t *rng_state) {
  uint32_t num = *rng_state;
  num ^= num << 13;
  num ^= num >> 17;
  num ^= num << 5;
  *rng_state = num;
  return num;
}


static uint32_t global_rng_state = 42;

uint32_t SimpleRNG_rand() {
  return SimpleRNG_rand_r(&global_rng_state);
}

void SimpleRNG_seed(uint32_t seed) {
  global_rng_state = seed;
}
