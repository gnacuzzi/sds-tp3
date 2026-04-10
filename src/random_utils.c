#include "random_utils.h"
#include "config.h"

#include <stdlib.h>
#include <time.h>

void random_seed(unsigned int seed) { srand(time(NULL)); }

double random_uniform(void) {
  return (double)rand() / ((double)RAND_MAX + 1.0);
}

double random_uniform_range(double min, double max) {
  return min + (max - min) * random_uniform();
}

double random_angle(void) { return random_uniform_range(0.0, 2.0 * M_PI); }
