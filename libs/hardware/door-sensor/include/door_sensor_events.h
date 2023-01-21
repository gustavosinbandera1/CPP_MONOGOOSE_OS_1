#pragma once

#include "mgos.h"

#define EVENT_DOOR_SENSOR_BASE MGOS_EVENT_BASE('D', 'S', 'C')

enum door_event_t {
    EVENT_DOOR_OPENED = EVENT_DOOR_SENSOR_BASE,
    EVENT_DOOR_CLOSED,
    EVENT_DOOR_UKN
};
