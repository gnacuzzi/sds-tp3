#include "io.h"


void write_snapshot(
    FILE *fp,
    Particle *particles,
    int n,
    double time,
    int cfc
) {
    fprintf(fp, "%d\n", n);
    fprintf(fp, "t %.8f %d\n", time, cfc);

    for (int i = 0; i < n; i++) {
        fprintf(
            fp,
            "%d %.8f %.8f %.8f %.8f %d\n",
            particles[i].id,
            particles[i].x,
            particles[i].y,
            particles[i].vx,
            particles[i].vy,
            particles[i].state
        );
    }
}
