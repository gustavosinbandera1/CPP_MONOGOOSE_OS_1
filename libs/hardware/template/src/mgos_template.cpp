#include "mgos_template.h"

#include <iostream>
#include "mgos.h"
#include "mgos_timers.h"
//---------------------------------------------------------------------------------------------------------------

static void my_timer_cb(void *arg) {
    LOG(LL_INFO, ("**********************************************template library* working fine *************************"));
}
//---------------------------------------------------------------------------------------------------------------
int mgos_template_init() {
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, my_timer_cb, NULL);
    return true;
}