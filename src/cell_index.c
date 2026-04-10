#include "cell_index.h"
#include "config.h"

#include <stdlib.h>
#include <stdio.h>


static int append_to_cell(Cell *cell, int particle_index) {
    if (cell->count == cell->capacity) {
        int new_capacity = cell->capacity == 0 ? 4 : cell->capacity * 2;

        int *new_data = realloc(
            cell->particle_indices,
            new_capacity * sizeof(int)
        );

        if (!new_data) return 0;

        cell->particle_indices = new_data;
        cell->capacity = new_capacity;
    }

    cell->particle_indices[cell->count++] = particle_index;

    return 1;
}


void get_particle_cell(
    const CellIndex *ci,
    const Particle *p,
    int *cx,
    int *cy
) {
    *cx = (int)((p->x + SYSTEM_RADIUS) / ci->cell_size);
    *cy = (int)((p->y + SYSTEM_RADIUS) / ci->cell_size);

    if (*cx < 0) *cx = 0;
    if (*cy < 0) *cy = 0;

    if (*cx >= ci->M) *cx = ci->M - 1;
    if (*cy >= ci->M) *cy = ci->M - 1;
}


CellIndex build_cell_index(
    Particle *particles,
    int n
) {
    CellIndex ci;

    ci.M = 4;
    ci.cell_size = (2.0 * SYSTEM_RADIUS) / ci.M;

    ci.grid = malloc(ci.M * sizeof(Cell*));

    for (int i = 0; i < ci.M; i++) {
        ci.grid[i] = malloc(ci.M * sizeof(Cell));

        for (int j = 0; j < ci.M; j++) {
            ci.grid[i][j].particle_indices = NULL;
            ci.grid[i][j].count = 0;
            ci.grid[i][j].capacity = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        int cx, cy;

        get_particle_cell(&ci, &particles[i], &cx, &cy);

        append_to_cell(&ci.grid[cx][cy], i);
    }

    return ci;
}


void free_cell_index(
    CellIndex *ci
) {
    for (int i = 0; i < ci->M; i++) {
        for (int j = 0; j < ci->M; j++) {
            free(ci->grid[i][j].particle_indices);
        }

        free(ci->grid[i]);
    }

    free(ci->grid);
}
