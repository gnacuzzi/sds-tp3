#include "config.h"
#include "init.h"
#include "simulation.h"

#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int n = DEFAULT_NUM_PARTICLES;
    double tf = DEFAULT_FINAL_TIME;

    Particle *particles = malloc(
        n * sizeof(Particle)
    );

    if (particles == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    init_particles(
        particles,
        n,
        DEFAULT_SEED
    );

    FILE *output_fp = fopen(
        "output/dynamic.txt",
        "w"
    );

    if (output_fp == NULL) {
        fprintf(stderr, "Could not open output file\n");
        free(particles);
        return 1;
    }

    run_simulation(
        particles,
        n,
        tf,
        output_fp,
        DEFAULT_SAVE_EVERY
    );

    fclose(output_fp);

    free(particles);

    return 0;
}
