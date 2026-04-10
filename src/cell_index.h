#ifndef CELL_INDEX_H
#define CELL_INDEX_H

#include "particle.h"


typedef struct {
    int *particle_indices;
    int count;
    int capacity;
} Cell;


typedef struct {
    Cell **grid;
    int M;
    double cell_size;
} CellIndex;


/* Build cell index from current particle positions */
CellIndex build_cell_index(
    Particle *particles,
    int n
);

/* Free allocated memory */
void free_cell_index(
    CellIndex *ci
);

/* Returns cell coords of particle */
void get_particle_cell(
    const CellIndex *ci,
    const Particle *p,
    int *cx,
    int *cy
);

#endif
