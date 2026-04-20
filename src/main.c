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

    char snapshot_filename[64];
    char events_filename[64];

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

        FILE *snapshot_fp = NULL;
        FILE *events_fp = NULL;
        int snapshot_save_every = DEFAULT_SAVE_EVERY;

        if (!benchmark) {
            if (n >= 200) {
                snapshot_save_every = 100;
            } else if (n >= 500) {
                snapshot_save_every = 200;
            }

            snprintf(
                snapshot_filename,
                sizeof(snapshot_filename),
                "output/%d_dynamic%d.txt",
                n,
                i
            );
            snprintf(
                events_filename,
                sizeof(events_filename),
                "output/%d_events%d.txt",
                n,
                i
            );

            snapshot_fp = fopen(snapshot_filename, "w");
            events_fp = fopen(events_filename, "w");

            printf("%s\n", snapshot_filename);
            printf("%s\n", events_filename);

            if (snapshot_fp == NULL || events_fp == NULL) {
                fprintf(stderr, "Could not open output files\n");
                if (snapshot_fp != NULL) {
                    fclose(snapshot_fp);
                }
                if (events_fp != NULL) {
                    fclose(events_fp);
                }
                free(particles);
                return 1;
            }
        }

        clock_t start = clock();

    


        run_simulation(
            particles,
            n,
            tf,
            snapshot_fp,
            events_fp,
            snapshot_save_every,
            benchmark
        );
    
    

        clock_t end = clock();

        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d,%f\n", n, elapsed);

        if (snapshot_fp != NULL) {
            fclose(snapshot_fp);
        }

        if (events_fp != NULL) {
            fclose(events_fp);
        }

        free(particles);
        sleep(1);
    }
    return 0;
}
