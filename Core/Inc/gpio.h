#ifndef GPIO_H
#define GPIO_H

// TODO: Make this platform independent
#include "stm32l0xx_hal.h"

#include <stdint.h>

typedef GPIO_TypeDef* gpio_port_t;
typedef uint32_t gpio_pin_t;

typedef uint32_t gpio_mode_t;
typedef uint32_t gpio_pull_t;
typedef uint32_t gpio_speed_t;
typedef uint32_t gpio_af_t;

typedef struct {
    gpio_mode_t mode;
    gpio_pull_t pull;
    gpio_speed_t speed;
    gpio_af_t af;
} gpio_config_t;

typedef GPIO_PinState gpio_state_t;

gpio_state_t gpio_get_pin_state(gpio_port_t port, gpio_pin_t pin);
void gpio_set_pin_state(gpio_port_t port, gpio_pin_t pin, gpio_state_t state);
void gpio_set_pin_mode(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode);
void gpio_set_pin_pull(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull);
void gpio_set_pin_speed(gpio_port_t port, gpio_pin_t pin, gpio_speed_t speed);
void gpio_set_pin_af(gpio_port_t port, gpio_pin_t pin, gpio_af_t af);
void gpio_config_pin(gpio_port_t port, gpio_pin_t pin, gpio_config_t* config);
void gpio_unconfig_pin(gpio_port_t port, gpio_pin_t pin);

#endif // GPIO_H