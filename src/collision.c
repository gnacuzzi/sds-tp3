#include "collision.h"

#include "config.h"
#include "geometry.h"

#include <math.h>


double time_to_particle_collision(
    const Particle *a,
    const Particle *b
) {
    double dx = b->x - a->x;
    double dy = b->y - a->y;

    double dvx = b->vx - a->vx;
    double dvy = b->vy - a->vy;

    double sigma = a->radius + b->radius;

    double dvdr = dx * dvx + dy * dvy;

    if (dvdr >= 0.0) {
        return INF;
    }

    double dvdv = dvx * dvx + dvy * dvy;
    double drdr = dx * dx + dy * dy;

    double discriminant = dvdr * dvdr - dvdv * (drdr - sigma * sigma);

    if (discriminant < 0.0) {
        return INF;
    }

    return -(dvdr + sqrt(discriminant)) / dvdv;
}


double time_to_wall_collision(
    const Particle *p
) {
    double effective_radius = SYSTEM_RADIUS - p->radius;

    double a = p->vx * p->vx + p->vy * p->vy;
    double b = 2.0 * (p->x * p->vx + p->y * p->vy);
    double c = p->x * p->x + p->y * p->y - effective_radius * effective_radius;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return INF;
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > EPS) return t1;
    if (t2 > EPS) return t2;

    return INF;
}


double time_to_obstacle_collision(
    const Particle *p
) {
    double effective_radius = OBSTACLE_RADIUS + p->radius;

    double a = p->vx * p->vx + p->vy * p->vy;
    double b = 2.0 * (p->x * p->vx + p->y * p->vy);
    double c = p->x * p->x + p->y * p->y - effective_radius * effective_radius;

    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return INF;
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 > EPS) return t1;
    if (t2 > EPS) return t2;

    return INF;
}


void resolve_particle_collision(
    Particle *a,
    Particle *b
) {
    double dx = b->x - a->x;
    double dy = b->y - a->y;

    double dist = sqrt(dx * dx + dy * dy);

    double nx = dx / dist;
    double ny = dy / dist;

    double dvx = a->vx - b->vx;
    double dvy = a->vy - b->vy;

    double rel_vel_normal = dvx * nx + dvy * ny;

    if (rel_vel_normal <= 0.0) {
        return;
    }

    double impulse = 2.0 * rel_vel_normal / (a->mass + b->mass);

    a->vx -= impulse * b->mass * nx;
    a->vy -= impulse * b->mass * ny;

    b->vx += impulse * a->mass * nx;
    b->vy += impulse * a->mass * ny;
}


void resolve_wall_collision(
    Particle *p
) {
    double dist = sqrt(p->x * p->x + p->y * p->y);

    double nx = p->x / dist;
    double ny = p->y / dist;

    double dot = p->vx * nx + p->vy * ny;

    p->vx -= 2.0 * dot * nx;
    p->vy -= 2.0 * dot * ny;

    p->state = PARTICLE_FRESH;
}


void resolve_obstacle_collision(
    Particle *p
) {
    double dist = sqrt(p->x * p->x + p->y * p->y);

    double nx = p->x / dist;
    double ny = p->y / dist;

    double dot = p->vx * nx + p->vy * ny;

    p->vx -= 2.0 * dot * nx;
    p->vy -= 2.0 * dot * ny;

    p->state = PARTICLE_USED;
}
