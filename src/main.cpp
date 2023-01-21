#include "mgos.h"
#include "mgos_gpio.h"
#include "FreeRTOS.h"
#include "iostream"
#include <cstdint>
#include <cstring>
#include "mgos_system.h"
#include "mgos_timers.h"
#include "mgos_adc.h"
#include "mgos_mqtt.h"


static void my_timer_cb(void *arg) {
   std::cout << "\033[1;32mbold green text\033[0m\n";

   int reading = mgos_adc_read(32);   
   std::cout << "**********************" << reading << std::endl;
   (void) arg;
}

static void my_timer_cb2(void *arg) {
   bool val = mgos_gpio_toggle(2);
   char topic[100];
   snprintf(topic, sizeof(topic), "/devices/%s/events", mgos_sys_config_get_device_id());
  
  bool res = mgos_mqtt_pubf(topic, 0, false /* retain */,
                            "{total_ram: %lu, free_ram: %lu}",
                            (unsigned long) mgos_get_heap_size(),
                            (unsigned long) mgos_get_free_heap_size());
  char buf[8];
  LOG(LL_INFO,("published: %s", res ? "yes" : "no"));

   
   LOG(LL_INFO, ("topic: %s", topic));
   std::cout << "\033[1;31mbold red text\033[0m\n";
   (void) arg;
}

static void handler(struct mg_connection *c, const char *topic, int topic_len,
                    const char *msg, int msg_len, void *userdata) {
  LOG(LL_INFO, ("Got message on topic %.*s", msg_len, msg));
}



extern "C" enum mgos_app_init_result mgos_app_init(void)
{
   mgos_gpio_set_mode(2, MGOS_GPIO_MODE_OUTPUT);
    mgos_set_timer(1000, MGOS_TIMER_REPEAT, my_timer_cb, NULL);
    mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb2, NULL);

    mgos_mqtt_sub("/devices/data", handler, NULL);
    
    mgos_adc_enable(32);
    return MGOS_APP_INIT_SUCCESS;
}
