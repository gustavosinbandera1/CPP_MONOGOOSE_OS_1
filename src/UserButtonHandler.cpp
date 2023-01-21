#include "UserButtonHandler.h"

#include "default.h"
#include <esp_log.h>


#define LED_R DEFAULT_RGB_LED_R
#define LED_G DEFAULT_RGB_LED_G
#define LED_B DEFAULT_RGB_LED_B

#define RGB_GPIO_OUTPUT_PIN_SEL ((1ULL << LED_R) | (1ULL << LED_G) | (1ULL << LED_B))

static bool toggle_r = false;
static bool toggle_g = false;
static bool toggle_b = false;

void UserButtonHandler::click(void)
{
    gpio_set_level(static_cast<gpio_num_t>(LED_R), toggle_r = !toggle_r);
}

void UserButtonHandler::doubleClick(void)
{
    gpio_set_level(static_cast<gpio_num_t>(LED_G), toggle_g = !toggle_g);
}

void UserButtonHandler::longClick(void)
{
    gpio_set_level(static_cast<gpio_num_t>(LED_B), toggle_b = !toggle_b);
}
