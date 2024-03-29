#include "mgos.h"
#include "mgos_gpio.h"
#include "FreeRTOS.h"
#include "iostream"
#include <cstdint>
#include <cstring>
#include "mgos_system.h"
#include "mgos_timers.h"
#include "mgos_adc.h"


static void my_timer_cb(void *arg) {
   bool val = mgos_gpio_toggle(2);
   //LOG(LL_INFO, ("uptime: %.2lf", mgos_uptime()));
   //std::cout << "*************** hello world "<< "Uptime " << mgos_uptime() << std::endl;
   std::cout << "\033[1;32mbold red text\033[0m\n";

   int reading = mgos_adc_read(32);   
   std::cout << "**********************" << reading << std::endl;
   (void) arg;
}

static void my_timer_cb2(void *arg) {
   bool val = mgos_gpio_toggle(2);
   //LOG(LL_INFO, ("uptime: %.2lf", mgos_uptime()));
   std::cout << "\033[1;31mbold red text\033[0m\n";
   (void) arg;
}


extern "C" enum mgos_app_init_result mgos_app_init(void)
{
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, my_timer_cb, NULL);
    mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb2, NULL);
    
    mgos_adc_enable(32);
    return MGOS_APP_INIT_SUCCESS;
}
