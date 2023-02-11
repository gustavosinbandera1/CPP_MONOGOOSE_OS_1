#pragma once
#include "mgos.h"

#ifdef __cplusplus
extern "C" {
#endif
int mgos_gpio_controller_init(void);
#ifdef __cplusplus
}
#endif

#define GPIO_CONTROLLER GPIOController::getInstance()

class GPIOController {
 public:
  static GPIOController *getInstance() {
    static GPIOController inst;
    return &inst;
  }

  void config_gpio(int pin, enum mgos_gpio_mode mode);
  void write_gpio(int pin, bool level);
  bool read_gpio(int pin);
  bool set_pull_resistor(int pin, enum mgos_gpio_pull_type pull);
  //bool set_gpio_isr(int pin, enum mgos_gpio_pull_type pull, enum mgos_gpio_int_mode mode, mgos_gpio_int_handler_f cb, void *arg);
  bool set_gpio_isr(int pin, enum mgos_gpio_pull_type pull, enum mgos_gpio_int_mode mode, void *arg);

 private:
  GPIOController();
};
