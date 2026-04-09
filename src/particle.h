#ifndef PARTICLE_H
#define PARTICLE_H

#include "config.h"

/* ============================================================
 * Particle State
 * ============================================================ */

typedef enum {
    PARTICLE_FRESH = 0,
    PARTICLE_USED = 1
} ParticleState;


/* ============================================================
 * Particle Structure
 * ============================================================ */

typedef struct {
    int id;

    double x;
    double y;

    double vx;
    double vy;

    double radius;
    double mass;

    ParticleState state;
} Particle;


/* ============================================================
 * Particle API
 * ============================================================ */

/* Initializes a particle with the given properties */
void particle_init(
    Particle *p,
    int id,
    double x,
    double y,
    double vx,
    double vy,
    double radius,
    double mass,
    ParticleState state
);

/* Advances particle position using straight-line motion */
void particle_advance(Particle *p, double dt);

/* Returns squared speed: vx^2 + vy^2 */
double particle_speed_sq(const Particle *p);

/* Returns speed magnitude */
double particle_speed(const Particle *p);

/* Changes particle state */
void particle_set_state(Particle *p, ParticleState state);

/* Returns 1 if particle is fresh, 0 otherwise */
int particle_is_fresh(const Particle *p);

/* Returns 1 if particle is used, 0 otherwise */
int particle_is_used(const Particle *p);

#endif
