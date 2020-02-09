#include "gpio.h"

#include "gpio_impl.h"

inline gpio_state_t gpio_get_pin_state(gpio_port_t port, gpio_pin_t pin) {
    return _gpio_get_pin_state_impl(port, pin);
}

inline void gpio_set_pin_state(gpio_port_t port, gpio_pin_t pin, gpio_state_t state) {
    _gpio_set_pin_state_impl(port, pin, state);
}

inline void gpio_set_pin_mode(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode) {
    _gpio_set_pin_mode_impl(port, pin, mode);
}

inline void gpio_set_pin_pull(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull) {
    _gpio_set_pin_pull_impl(port, pin, pull);
}

inline void gpio_set_pin_speed(gpio_port_t port, gpio_pin_t pin, gpio_speed_t speed) {
    _gpio_set_pin_speed_impl(port, pin, speed);
}

inline void gpio_set_pin_af(gpio_port_t port, gpio_pin_t pin, gpio_af_t af) {
    _gpio_set_pin_af_impl(port, pin, af);
}

inline void gpio_config_pin(gpio_port_t port, gpio_pin_t pin, gpio_config_t* config) {
    _gpio_config_pin_impl(port, pin, config);
}

inline void gpio_unconfig_pin(gpio_port_t port, gpio_pin_t pin) {
    _gpio_unconfig_pin_impl(port, pin);
}