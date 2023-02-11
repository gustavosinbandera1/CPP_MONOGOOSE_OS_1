#include <cstdint>
#include <cstring>
#include "FreeRTOS.h"
#include "iostream"
#include "mgos.h"
#include "mgos_gpio.h"
#include "mgos_system.h"
#include "mgos_timers.h"

#include "mgos_gpio_controller.h"
#include "mgos_mqtt.h"
#include "mgos_button_events.h"
#include "mgos_net.h"

static void btn_cb(int id, void* ev_data, void* user_data)
{
  int *pin = static_cast<int*>(ev_data);
  //int *data = (int*)ev_data;
  LOG(LL_INFO, ("pin: %d pressed", *pin));
}


// grupo de eventos
static void my_net_ev_handler(int ev, void *evd, void *arg) {
  if (ev == MGOS_NET_EV_IP_ACQUIRED) {
    LOG(LL_INFO, ("Just got IP!"));
    // Fetch something very useful from somewhere
  } else if(ev == MGOS_NET_EV_CONNECTING)
  {

  }

  (void) evd;
  (void) arg;
}

// evento en particular 
static void connected_cb(int ev, void *evd, void *arg) {

//log estoy connectado
  (void) evd;
  (void) arg;
}


static void my_timer_cb2(void *arg) {
  // bool val = mgos_gpio_toggle(2);

  int status = GPIO_CONTROLLER->read_gpio(32);
   LOG(LL_INFO, ("pin 32 status: %d", status));

  static int x = 0;

  if (x % 2) {
    GPIO_CONTROLLER->write_gpio(2, true);

  } else {
    GPIO_CONTROLLER->write_gpio(2, false);
  }
  x++;

  char topic[100];
  snprintf(topic, sizeof(topic), "/devices/%s/events",
           mgos_sys_config_get_device_id());

  bool res = mgos_mqtt_pubf(topic, 0, false /* retain */,
                            "{total_ram: %lu, free_ram: %lu}",
                            (unsigned long) mgos_get_heap_size(),
                            (unsigned long) mgos_get_free_heap_size());

  char buf[8];
  LOG(LL_INFO, ("published: %s", res ? "yes" : "no"));

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


  snprintf(topic, sizeof(topic), "/devices/%s/test",
           mgos_sys_config_get_device_id());
  bool res = mgos_mqtt_pubf(topic, 0, false /* retain */,
                            "{count_ascii: %c, count2: %d, test_float : %f}",
                            (int) var++, var2++, testFloat);

  char buf[8];
  LOG(LL_INFO, ("published: %s", res ? "yes" : "no"));

  LOG(LL_INFO, ("topic: %s", topic));
  std::cout << "\033[1;31mbold red text\033[0m\n";
  (void) arg;
}

static void mifunc(struct mg_connection *c, const char *topic, int topic_len,
                   const char *msg, int msg_len, void *userdata) {
  LOG(LL_INFO, ("Got message on topic %.*s", msg_len, msg));
}

extern "C" enum mgos_app_init_result mgos_app_init(void) {

  mgos_event_add_handler(BUTTON_PRESSED, btn_cb, NULL );
  //mgos_event_add_group_handler(EVENTS_BUTTON_BASE, btn_event_base_cb, NULL);

  mgos_event_add_group_handler(MGOS_EVENT_GRP_NET, my_net_ev_handler, NULL);
  //mgos_event_add_handler(MGOS_NET_EV_CONNECTED, connected_cb, NULL );

  mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb2, NULL);
  mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb3, NULL);

  mgos_mqtt_sub("/devices/data", mifunc, NULL);
  GPIO_CONTROLLER->config_gpio(2, MGOS_GPIO_MODE_OUTPUT);

  GPIO_CONTROLLER->config_gpio(mgos_sys_config_get_buttons_button1(), MGOS_GPIO_MODE_INPUT);
  GPIO_CONTROLLER->set_gpio_isr(mgos_sys_config_get_buttons_button1(), MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, NULL);

  
  return MGOS_APP_INIT_SUCCESS;
}

// https://iotquindio.blogspot.com/