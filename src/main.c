#include "config.h"
#include "init.h"
#include "simulation.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    int n = DEFAULT_NUM_PARTICLES;
    double tf = DEFAULT_FINAL_TIME;
    bool benchmark = false;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    if (argc > 2) {
        benchmark = atoi(argv[2]) != 0;
    }

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

    FILE *output_fp = NULL;

    if (!benchmark) {
        output_fp = fopen("output/dynamic.txt", "w");

        if (output_fp == NULL) {
            fprintf(stderr, "Could not open output file\n");
            free(particles);
            return 1;
        }
    }

    clock_t start = clock();

    run_simulation(
        particles,
        n,
        tf,
        output_fp,
        DEFAULT_SAVE_EVERY,
        benchmark
    );

    clock_t end = clock();

    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%d,%f\n", n, elapsed);

    if (output_fp != NULL) {
        fclose(output_fp);
    }

    free(particles);

    return 0;
}
