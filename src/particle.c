#include "particle.h"

#include <math.h>


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
) {
    p->id = id;

    p->x = x;
    p->y = y;

    p->vx = vx;
    p->vy = vy;

    p->radius = radius;
    p->mass = mass;

    p->state = state;
}


void particle_advance(Particle *p, double dt) {
    p->x += p->vx * dt;
    p->y += p->vy * dt;
}


double particle_speed_sq(const Particle *p) {
    return p->vx * p->vx + p->vy * p->vy;
}


double particle_speed(const Particle *p) {
    return sqrt(particle_speed_sq(p));
}


void particle_set_state(Particle *p, ParticleState state) {
    p->state = state;
}


int particle_is_fresh(const Particle *p) {
    return p->state == PARTICLE_FRESH;
}


int particle_is_used(const Particle *p) {
    return p->state == PARTICLE_USED;
}
