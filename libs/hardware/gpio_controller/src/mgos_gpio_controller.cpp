#include "mgos_gpio_controller.h"
#include <iostream>
#include "mgos.h"
#include "mgos_timers.h"
#include "mgos_gpio.h"
#include "mgos_button_events.h"
//---------------------------------------------------------------------------------------------------------------
static void isr_callback(int pin, void* arg)
{
    /// emit events
    mgos_event_trigger(BUTTON_PRESSED, (void*)&pin);
}

void GPIOController::config_gpio(int pin, enum mgos_gpio_mode mode)
{
    mgos_gpio_set_mode(pin, mode);
}
//---------------------------------------------------------------------------------------------------------------

void GPIOController::write_gpio(int pin, bool level)
{
    mgos_gpio_write(pin, level);
}
//---------------------------------------------------------------------------------------------------------------
bool GPIOController::read_gpio(int pin)
{
    return mgos_gpio_read(pin);
}

bool GPIOController::set_pull_resistor(int pin, enum mgos_gpio_pull_type pull)
{
    return mgos_gpio_set_pull(pin, pull);

}

// bool GPIOController::set_gpio_isr(int pin, enum mgos_gpio_pull_type pull, 
//                                     enum mgos_gpio_int_mode mode, 
//                                     mgos_gpio_int_handler_f cb, 
//                                     void *arg)
// {
//     mgos_gpio_enable_int(pin);
//     return mgos_gpio_set_button_handler(pin, pull, mode, 150, cb, arg);
// }

bool GPIOController::set_gpio_isr(int pin, enum mgos_gpio_pull_type pull, 
                                    enum mgos_gpio_int_mode mode,
                                    void *arg)
{
    mgos_gpio_enable_int(pin);
    return mgos_gpio_set_button_handler(pin, pull, mode, 150, isr_callback, arg);
}

GPIOController::GPIOController()
{

}
//---------------------------------------------------------------------------------------------------------------
int mgos_gpio_controller_init() {
    mgos_event_register_base(EVENTS_BUTTON_BASE, "EVENTS_BUTTON_BASE"); //registering event on mongoose os SO
    return true;
}