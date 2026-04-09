#ifndef INIT_H
#define INIT_H

#include "particle.h"


/* ============================================================
 * Initialization API
 * ============================================================ */

/* Initializes N valid particles with random positions/velocities */
void init_particles(
    Particle *particles,
    int n,
    unsigned int seed
);

#endif
