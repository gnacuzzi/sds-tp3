#include "config.h"
#include "init.h"
#include "simulation.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    int n = DEFAULT_NUM_PARTICLES;
    double tf = DEFAULT_FINAL_TIME;
    bool benchmark = false;
    int num_runs = 1;

    if (argc > 1) {
        n = atoi(argv[1]);
    }

    if (argc > 2) {
        benchmark = atoi(argv[2]) != 0;
    }

    if (argc > 3){
        num_runs = atoi(argv[3]);
    }

    char filename[40];

    for (int i = 0; i < num_runs; i++){

        Particle *particles = malloc(
            n * sizeof(Particle)
        );

        if (particles == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }

        init_particles(
            particles,
            n
        );

        FILE *output_fp = NULL;

        if (!benchmark) {
            snprintf(filename, sizeof(filename), "output/%d_dynamic%d.txt", n, i);
            output_fp = fopen(filename, "w");

            printf("%s", filename);
            printf("\n");

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
        sleep(1);
    }
    return 0;
}
