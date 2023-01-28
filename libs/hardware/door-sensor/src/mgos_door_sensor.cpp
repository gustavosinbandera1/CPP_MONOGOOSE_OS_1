#include "mgos_door_sensor.h"

#include <iostream>

#include "door_sensor_events.h"
#include "mgos.h"
#include "mgos_adc.h"
#include "mgos_timers.h"
//---------------------------------------------------------------------------------------------------------------
// void DoorSensor::checkDoor() {
//     bool new_door_closed = !mgos_gpio_read(mgos_sys_config_get_door_sensor_pin());

//     if (new_door_closed != last_door_closed_) {
//         door_closed_cnt_ = 0;
//     } else {
//         if (new_door_closed != door_closed_ && ++door_closed_cnt_ == 5) {
//             door_closed_ = new_door_closed;
//             if (door_closed_) {
//                 LOG(LL_INFO, ("The door was CLOSED"));
//                 mgos_event_trigger(EVENT_DOOR_CLOSED, NULL);
//             } else {
//                 LOG(LL_INFO, ("The door was OPENED"));
//                 mgos_event_trigger(EVENT_DOOR_OPENED, NULL);
//             }
//         }
//     }
//     last_door_closed_ = new_door_closed;
// }
//---------------------------------------------------------------------------------------------------------------
// DoorSensor::DoorSensor() {
//     last_door_closed_ = door_closed_ = !mgos_gpio_read(mgos_sys_config_get_door_sensor_pin());
//     door_closed_cnt_ = 0;
//     checkDoorTimerId_ = mgos_set_timer(200, MGOS_TIMER_REPEAT, checkDoorTimer_cb, NULL);
//     x=1;
// }


//---------------------------------------------------------------------------------------------------------------

static void my_timer_cb(void *arg) {
    int *param = (int*)arg;
    LOG(LL_INFO, ("********************************************** door sensor The var as paarmeter is: %d **************************",*param));
}
//---------------------------------------------------------------------------------------------------------------
int mgos_door_sensor_init() {
    mgos_event_register_base(EVENT_DOOR_SENSOR_BASE, "DOOR_SENSOR_EVENTS");
    mgos_gpio_setup_input(mgos_sys_config_get_door_sensor_pin(), MGOS_GPIO_PULL_UP);

    static int y = 20;

    mgos_set_timer(1000, MGOS_TIMER_REPEAT, my_timer_cb, &y);
    std::string name = mgos_sys_config_get_door_sensor_name();

    mgos_adc_enable(32);
    LOG(LL_INFO, (name.c_str()));
    //DoorSensor::getInstance();

    return true;
}