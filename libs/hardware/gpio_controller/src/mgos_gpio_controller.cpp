#include "mgos_gpio_controller.h"
#include <iostream>
#include "mgos.h"
#include "mgos_timers.h"
#include "mgos_gpio.h"
//---------------------------------------------------------------------------------------------------------------

static void my_timer_cb(void *arg) {
    LOG(LL_INFO, ("**********************************************gpio controller*************************"));
}
//---------------------------------------------------------------------------------------------------------------


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

bool GPIOController::set_gpio_isr(int pin, enum mgos_gpio_pull_type pull, 
                                    enum mgos_gpio_int_mode mode, 
                                    mgos_gpio_int_handler_f cb, 
                                    void *arg)
{
    mgos_gpio_enable_int(pin);
    return mgos_gpio_set_button_handler(pin, pull, mode, 150, cb, arg);
}

GPIOController::GPIOController()
{

}
//---------------------------------------------------------------------------------------------------------------

int mgos_gpio_controller_init() {
    return true;
}