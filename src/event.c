#include "event.h"


Event event_none(void) {
    return (Event){
        .type = EVENT_NONE,
        .time = INF,
        .i = -1,
        .j = -1
    };
}


Event event_create(
    EventType type,
    double time,
    int i,
    int j
) {
    return (Event){
        .type = type,
        .time = time,
        .i = i,
        .j = j
    };
}


int event_is_valid(
    const Event *e
) {
    return e->type != EVENT_NONE && e->time < INF;
}
