#include "init.h"

#include "config.h"
#include "geometry.h"
#include "random_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static int valid_position(
    Particle *particles,
    int count,
    double x,
    double y
) {
    Particle candidate;

    particle_init(
        &candidate,
        -1,
        x,
        y,
        0.0,
        0.0,
        PARTICLE_RADIUS,
        PARTICLE_MASS,
        PARTICLE_FRESH
    );

    if (!particle_inside_system(&candidate)) {
        return 0;
    }

    if (particle_overlaps_obstacle(&candidate)) {
        return 0;
    }

    for (int i = 0; i < count; i++) {
        if (particles_overlap(&candidate, &particles[i])) {
            return 0;
        }
    }

    return 1;
}


void init_particles(
    Particle *particles,
    int n
) {
    random_seed();

    for (int i = 0; i < n; i++) {
        double x, y;

        do {
            double r = random_uniform_range(
                OBSTACLE_RADIUS + PARTICLE_RADIUS,
                SYSTEM_RADIUS - PARTICLE_RADIUS
            );

            double theta = random_angle();

            x = r * cos(theta);
            y = r * sin(theta);

        } while (!valid_position(particles, i, x, y));

        double angle = random_angle();

        double vx = PARTICLE_SPEED * cos(angle);
        double vy = PARTICLE_SPEED * sin(angle);

        particle_init(
            &particles[i],
            i,
            x,
            y,
            vx,
            vy,
            PARTICLE_RADIUS,
            PARTICLE_MASS,
            PARTICLE_FRESH
        );
    }
}
