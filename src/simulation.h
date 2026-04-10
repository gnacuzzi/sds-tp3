#ifndef SIMULATION_H
#define SIMULATION_H

#include "particle.h"

#include <stdio.h>
#include <stdbool.h>


/* ============================================================
 * Simulation API
 * ============================================================ */

void run_simulation(
    Particle *particles,
    int n,
    double tf,
    FILE *output_fp,
    int save_every,
    bool benchmark
);

#endif
