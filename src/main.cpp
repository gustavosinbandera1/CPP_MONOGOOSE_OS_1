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
    LOG(LL_INFO, ("-------------------------------------Just got IP!---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------Just got IP!---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------Just got IP!---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------Just got IP!---------------------------------------------------------"));
    // Fetch something very useful from somewhere
  } else if(ev == MGOS_NET_EV_CONNECTING)
  {
        LOG(LL_INFO, ("---------------------------------connecting ---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------connecting ---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------connecting ---------------------------------------------------------"));
    LOG(LL_INFO, ("-------------------------------------connecting ---------------------------------------------------------"));
    
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


extern "C" enum mgos_app_init_result mgos_app_init(void) {

  mgos_event_add_handler(BUTTON_PRESSED, btn_cb, NULL );
  //mgos_event_add_group_handler(EVENTS_BUTTON_BASE, btn_event_base_cb, NULL);

  mgos_event_add_group_handler(MGOS_EVENT_GRP_NET, my_net_ev_handler, NULL);
  //mgos_event_add_handler(MGOS_NET_EV_CONNECTED, connected_cb, NULL );

  GPIO_CONTROLLER->config_gpio(2, MGOS_GPIO_MODE_OUTPUT);
  GPIO_CONTROLLER->config_gpio(mgos_sys_config_get_buttons_button1(), MGOS_GPIO_MODE_INPUT);
  GPIO_CONTROLLER->set_gpio_isr(mgos_sys_config_get_buttons_button1(), MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, NULL);

  
  return MGOS_APP_INIT_SUCCESS;
}

// https://iotquindio.blogspot.com/