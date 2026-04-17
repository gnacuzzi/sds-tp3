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
    double time,
    int cfc,
    double fu
);

/* Writes one event-time entry */
void write_event_time(
    FILE *fp,
    int event_count,
    double time,
    int cfc,
    double fu
);

#endif
