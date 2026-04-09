#ifndef RANDOM_UTILS_H
#define RANDOM_UTILS_H

/* ============================================================
 * Random Initialization
 * ============================================================ */

/* Initializes RNG with given seed */
void random_seed(unsigned int seed);

/* Uniform random in [0,1) */
double random_uniform(void);

/* Uniform random in [min,max) */
double random_uniform_range(double min, double max);

/* Uniform random angle in [0, 2pi) */
double random_angle(void);

#endif
