#ifndef COLLISION_H
#define COLLISION_H

#include "particle.h"


/* ============================================================
 * Collision Time Computation
 * ============================================================ */

/* Time until collision between two moving particles */
double time_to_particle_collision(
    const Particle *a,
    const Particle *b
);

/* Time until collision with outer circular wall */
double time_to_wall_collision(
    const Particle *p
);

/* Time until collision with fixed central obstacle */
double time_to_obstacle_collision(
    const Particle *p
);


/* ============================================================
 * Collision Resolution
 * ============================================================ */

/* Resolves elastic collision between two particles */
void resolve_particle_collision(
    Particle *a,
    Particle *b
);

/* Reflects velocity against outer circular wall */
void resolve_wall_collision(
    Particle *p
);

/* Reflects velocity against central obstacle */
void resolve_obstacle_collision(
    Particle *p
);

#endif
