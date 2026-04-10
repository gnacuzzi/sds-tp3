#include "simulation.h"

#include "collision.h"
#include "event.h"
#include "particle.h"
#include "io.h"
#include "cell_index.h"

#include <stdio.h>
#include <stdbool.h>

static int cfc;


static Event find_next_event(
    Particle *particles,
    int n
) {
    Event best = event_none();
    CellIndex ci = build_cell_index(particles, n);

    for (int i = 0; i < n; i++) {

        double wall_t = time_to_wall_collision(&particles[i]);
        if (wall_t < best.time) {
            best = event_create(EVENT_PARTICLE_WALL, wall_t, i, -1);
        }

        double obs_t = time_to_obstacle_collision(&particles[i]);
        if (obs_t < best.time) {
            best = event_create(EVENT_PARTICLE_OBSTACLE, obs_t, i, -1);
        }

        int cx, cy;
        get_particle_cell(&ci, &particles[i], &cx, &cy);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {

                int nx = cx + dx;
                int ny = cy + dy;

                if (nx < 0 || nx >= ci.M || ny < 0 || ny >= ci.M) {
                    continue;
                }

                Cell cell = ci.grid[nx][ny];

                for (int k = 0; k < cell.count; k++) {
                    int j = cell.particle_indices[k];

                    if (j <= i) {
                        continue;
                    }

                    double pair_t = time_to_particle_collision(
                        &particles[i],
                        &particles[j]
                    );

                    if (pair_t < best.time) {
                        best = event_create(
                            EVENT_PARTICLE_PARTICLE,
                            pair_t,
                            i,
                            j
                        );
                    }
                }
            }
        }
    }

    free_cell_index(&ci);
    return best;
}


static void advance_all_particles(
    Particle *particles,
    int n,
    double dt
) {
    for (int i = 0; i < n; i++) {
        particle_advance(&particles[i], dt);
    }
}


static void process_event(
    Particle *particles,
    Event e
) {
    switch (e.type) {

        case EVENT_PARTICLE_PARTICLE:
            resolve_particle_collision(
                &particles[e.i],
                &particles[e.j]
            );
            break;

        case EVENT_PARTICLE_WALL:
            resolve_wall_collision(
                &particles[e.i]
            );
            break;

        case EVENT_PARTICLE_OBSTACLE:
            resolve_obstacle_collision(
                &particles[e.i]
            );
            cfc++;
            break;

        default:
            break;
    }
}


void run_simulation(
    Particle *particles,
    int n,
    double tf,
    FILE *output_fp,
    int save_every,
    bool benchmark
) {
    double t = 0.0;
    int event_count = 0;
    cfc = 0;

    if (!benchmark){
        write_snapshot(output_fp, particles, n, t, cfc);
    }
    

    while (t < tf) {

        Event next = find_next_event(
            particles,
            n
        );

        if (!event_is_valid(&next)) {
            break;
        }

        if (t + next.time > tf) {
            advance_all_particles(
                particles,
                n,
                tf - t
            );

            if (!benchmark) {
                write_snapshot(
                    output_fp,
                    particles,
                    n,
                    tf,
                    cfc
                );
            }

            break;
        }

        advance_all_particles(
            particles,
            n,
            next.time
        );

        t += next.time;

        process_event(
            particles,
            next
        );

        event_count++;

        if (event_count % save_every == 0 && !benchmark) {
            write_snapshot(
                output_fp,
                particles,
                n,
                t,
                cfc
            );
        }
    }
}
