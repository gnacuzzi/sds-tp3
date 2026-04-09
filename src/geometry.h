#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "particle.h"


/* ============================================================
 * Basic Vector / Distance Operations
 * ============================================================ */

/* Returns x² + y² */
double norm_sq(double x, double y);

/* Returns sqrt(x² + y²) */
double norm(double x, double y);

/* Euclidean distance between two points */
double distance_between(
    double x1,
    double y1,
    double x2,
    double y2
);

/* Dot product of two 2D vectors */
double dot_product(
    double ax,
    double ay,
    double bx,
    double by
);


/* ============================================================
 * Particle Geometry Helpers
 * ============================================================ */

/* Distance between centers of two particles */
double particle_distance(
    const Particle *a,
    const Particle *b
);

/* Returns 1 if particles overlap, 0 otherwise */
int particles_overlap(
    const Particle *a,
    const Particle *b
);


/* ============================================================
 * Domain Validation
 * ============================================================ */

/* Returns 1 if particle is fully inside outer circular boundary */
int particle_inside_system(
    const Particle *p
);

/* Returns 1 if particle overlaps central obstacle */
int particle_overlaps_obstacle(
    const Particle *p
);


/* ============================================================
 * Radial Profile Utilities
 * ============================================================ */

/* Distance from particle center to system center (0,0) */
double particle_radial_distance(
    const Particle *p
);

/* Area of annulus between radii r_inner and r_outer */
double annulus_area(
    double r_inner,
    double r_outer
);

#endif
