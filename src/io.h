#ifndef IO_H
#define IO_H

#include "particle.h"

#include <stdio.h>


/* ============================================================
 * Output API
 * ============================================================ */

/* Writes one snapshot of the system */
void write_snapshot(
    FILE *fp,
    Particle *particles,
    int n,
    double time
);

#endif
