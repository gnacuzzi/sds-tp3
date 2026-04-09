#include "geometry.h"

#include <math.h>


double norm_sq(double x, double y) {
    return x * x + y * y;
}


double norm(double x, double y) {
    return sqrt(norm_sq(x, y));
}


double distance_between(
    double x1,
    double y1,
    double x2,
    double y2
) {
    return norm(x2 - x1, y2 - y1);
}


double dot_product(
    double ax,
    double ay,
    double bx,
    double by
) {
    return ax * bx + ay * by;
}


double particle_distance(
    const Particle *a,
    const Particle *b
) {
    return distance_between(a->x, a->y, b->x, b->y);
}


int particles_overlap(
    const Particle *a,
    const Particle *b
) {
    double min_dist = a->radius + b->radius;

    return particle_distance(a, b) < min_dist - EPS;
}


int particle_inside_system(
    const Particle *p
) {
    double dist_from_center = norm(p->x, p->y);

    return dist_from_center + p->radius <= SYSTEM_RADIUS + EPS;
}


int particle_overlaps_obstacle(
    const Particle *p
) {
    double dist_from_center = norm(p->x, p->y);

    return dist_from_center < (OBSTACLE_RADIUS + p->radius - EPS);
}


double particle_radial_distance(
    const Particle *p
) {
    return norm(p->x, p->y);
}


double annulus_area(
    double r_inner,
    double r_outer
) {
    return M_PI * (r_outer * r_outer - r_inner * r_inner);
}
