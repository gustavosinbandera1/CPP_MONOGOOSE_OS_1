#include "mgos.h"
#include "mgos_gpio.h"
#include "FreeRTOS.h"
#include "iostream"
#include <cstdint>
#include <cstring>
#include "mgos_system.h"
#include "mgos_timers.h"

#include "mgos_mqtt.h"




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

static void my_timer_cb3(void *arg) {
   char topic[100];
   static int var = 32;
   int var2 = 1;
   float testFloat = 3.3456789;

   char message[100];
   snprintf(message, sizeof(message), "sensor: %d", 4);
   
   //mgos_mqtt_pub(topic,message, strlen(message), 0, false);


   snprintf(topic, sizeof(topic), "/devices/%s/test", mgos_sys_config_get_device_id());
   bool res = mgos_mqtt_pubf(topic, 0, false /* retain */,
                            "{count_ascii: %c, count2: %d, test_float : %f}", (int) var++, var2++, testFloat);


  char buf[8];
  LOG(LL_INFO,("published: %s", res ? "yes" : "no"));

   
   LOG(LL_INFO, ("topic: %s", topic));
   std::cout << "\033[1;31mbold red text\033[0m\n";
   (void) arg;
}


static void mifunc(struct mg_connection *c, const char *topic, int topic_len,
                    const char *msg, int msg_len, void *userdata) {
  
  LOG(LL_INFO, ("Got message on topic %.*s", msg_len, msg));
}



extern "C" enum mgos_app_init_result mgos_app_init(void)
{
   mgos_gpio_set_mode(2, MGOS_GPIO_MODE_OUTPUT);
   mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb2, NULL);
    mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb3, NULL);

    mgos_mqtt_sub("/devices/data", mifunc, NULL);
    
    return MGOS_APP_INIT_SUCCESS;
}

// https://iotquindio.blogspot.com/