#ifndef EVENT_H
#define EVENT_H

#include "config.h"


/* ============================================================
 * Event Types
 * ============================================================ */

typedef enum {
    EVENT_NONE = 0,
    EVENT_PARTICLE_PARTICLE,
    EVENT_PARTICLE_WALL,
    EVENT_PARTICLE_OBSTACLE
} EventType;


/* ============================================================
 * Event Structure
 * ============================================================ */

typedef struct {
    EventType type;

    double time;

    int i;
    int j;
} Event;


/* ============================================================
 * Event API
 * ============================================================ */

/* Returns an invalid/null event */
Event event_none(void);

/* Creates an event */
Event event_create(
    EventType type,
    double time,
    int i,
    int j
);

/* Returns 1 if event is valid */
int event_is_valid(
    const Event *e
);

#endif
