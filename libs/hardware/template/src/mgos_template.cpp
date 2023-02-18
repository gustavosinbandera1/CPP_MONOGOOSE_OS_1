#include "mgos_template.h"

#include <iostream>
#include "mgos.h"
#include "mgos_timers.h"
//---------------------------------------------------------------------------------------------------------------

static void my_timer_cb(void *arg) {
  LOG(LL_INFO, ("**********************************************template "
                "library* working fine *************************"));
}

// constructor
PlantillaCtrl::PlantillaCtrl() {
}

void PlantillaCtrl::method1(float param)
{

}

int PlantillaCtrl::method2(char param)
{
    return 0;
}

bool PlantillaCtrl::method3(int param)
{
    return true;
}
//---------------------------------------------------------------------------------------------------------------
int mgos_template_init() {
  mgos_set_timer(1000*60*5, MGOS_TIMER_REPEAT, my_timer_cb, NULL);
  return true;
}