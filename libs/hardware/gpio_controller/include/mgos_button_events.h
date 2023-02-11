#pragma once

#include "mgos.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVENTS_BUTTON_BASE MGOS_EVENT_BASE('B', 'T', 'N')  // generate a unique identifier 

enum btn_event_t {
    BUTTON_PRESSED = EVENTS_BUTTON_BASE,  // raised when the cook process  is first started,
    BUTTON_RELEASED
};

#ifdef __cplusplus
}
#endif
