#ifndef SIMPLE_RNG_H
#define SIMPLE_RNG_H

/**
  Implementation of a 32-bit 'Xorshift' Random Number Generator,
  based on the work of George Marsaglia (www.jstatsoft.org/v08/i14/paper , doi:10.18637/jss.v008.i14)

  NOTE: This is _not_ a cryptographically secure random number generator.
  Also, be aware that '0' should not be used as a seed, because in this case, the output of the RNG will always be '0'.

  Author: Wiebe-Marten Wijnja (Qqwy)
  Date: 2018-09-15

  Usage instructions:

  1. use SimpleRNG_seed(your_lucky_number) to seed the RNG to a desired 32-bit unsigned integer.
  2. Call SimpleRNG_rand() to get a new random 32-bit unsigned integer.
  3. Repeat step (2) as often as you'd like.

  If you want to keep track of multiple RNGs side-by-side, use `SimpleRNG_rand_r(rng_state)` instead, which will take the passed argument as RNG state (and mutate it in place to become the new state).
 */

#include <stdint.h>

uint32_t SimpleRNG_rand();

void SimpleRNG_seed(uint32_t seed);

uint32_t SimpleRNG_rand_r(uint32_t *rng_state);

#endif
