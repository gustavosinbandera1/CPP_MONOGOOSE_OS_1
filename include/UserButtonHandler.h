/**
 * @file defaults.h
 * @author Locha Mesh project developers (locha.io)
 * @brief
 * @version 0.1
 * @date 2019-11-07
 *
 * @copyright Copyright (c) 2020 Locha Mesh project developers
 * @license Apache 2.0, see LICENSE file for details
 */

#ifndef USER_BUTTON_HANDLER_H_
#define USER_BUTTON_HANDLER_H_

#include "driver/gpio.h"
#include "driver/ledc.h"
#include <iostream>
/**
 * @brief Handler callback for different press button types
 */
class UserButtonHandler
{
public:
    static void click(void);
    static void doubleClick(void);
    static void longClick(void);
    //static void initRGBPort(void);
}; // UserButtonHandler

#endif