#ifndef GPIO_IMPL_H
#define GPIO_IMPL_H

#include "gpio.h"

#include <stdbool.h>

gpio_state_t _gpio_get_pin_state_impl(gpio_port_t port, gpio_pin_t pin);
void _gpio_set_pin_state_impl(gpio_port_t port, gpio_pin_t pin, gpio_state_t state);
void _gpio_set_pin_mode_impl(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode);
void _gpio_set_pin_pull_impl(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull);
void _gpio_set_pin_speed_impl(gpio_port_t port, gpio_pin_t pin, gpio_speed_t speed);
void _gpio_set_pin_af_impl(gpio_port_t port, gpio_pin_t pin, gpio_af_t af);
void _gpio_config_pin_impl(gpio_port_t port, gpio_pin_t pin, gpio_config_t* config);
void _gpio_unconfig_pin_impl(gpio_port_t port, gpio_pin_t pin);

#endif // GPIO_IMPL_H