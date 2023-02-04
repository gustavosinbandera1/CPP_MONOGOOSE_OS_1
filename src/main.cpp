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

  // mgos_mqtt_pub(topic,message, strlen(message), 0, false);

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


static void my_isr_cb(int pin, void *arg) {
    LOG(LL_INFO, ("**********************************************gpio isr called*************************%d", pin));
    switch(pin)
    {
      case 32:
           LOG(LL_INFO, ("****se presiono el pin 32"));
      break;

      case 33:
         LOG(LL_INFO, ("****se presiono el pin 33"));
      break;

    }
}



extern "C" enum mgos_app_init_result mgos_app_init(void) {
  mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb2, NULL);
  mgos_set_timer(3000, MGOS_TIMER_REPEAT, my_timer_cb3, NULL);

  mgos_mqtt_sub("/devices/data", mifunc, NULL);
  GPIO_CONTROLLER->config_gpio(2, MGOS_GPIO_MODE_OUTPUT);

  GPIO_CONTROLLER->config_gpio(32, MGOS_GPIO_MODE_INPUT);
  GPIO_CONTROLLER->set_gpio_isr(32, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, my_isr_cb, NULL);

  GPIO_CONTROLLER->config_gpio(33, MGOS_GPIO_MODE_INPUT);
  GPIO_CONTROLLER->set_gpio_isr(33, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, my_isr_cb, NULL);
  return MGOS_APP_INIT_SUCCESS;
}

// https://iotquindio.blogspot.com/