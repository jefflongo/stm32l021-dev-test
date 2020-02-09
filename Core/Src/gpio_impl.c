#include "gpio_impl.h"

#include "stm32l0xx_hal.h"

#include <assert.h>

#define GPIO_MODE ((uint32_t)0x00000003U)
#define EXTI_MODE ((uint32_t)0x10000000U)
#define GPIO_MODE_IT ((uint32_t)0x00010000U)
#define GPIO_MODE_EVT ((uint32_t)0x00020000U)
#define RISING_EDGE ((uint32_t)0x00100000U)
#define FALLING_EDGE ((uint32_t)0x00200000U)
#define GPIO_OUTPUT_TYPE ((uint32_t)0x00000010U)

gpio_state_t _gpio_get_pin_state_impl(gpio_port_t port, gpio_pin_t pin) {
    assert(IS_GPIO_PIN_AVAILABLE(port, pin));

    return (port->IDR & pin) != (uint32_t)GPIO_PIN_RESET ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void _gpio_set_pin_state_impl(gpio_port_t port, gpio_pin_t pin, gpio_state_t state) {
    assert(IS_GPIO_PIN_AVAILABLE(port, pin) && IS_GPIO_PIN_ACTION(state));

    if (state != GPIO_PIN_RESET) {
        port->BSRR = pin;
    } else {
        port->BRR = pin;
    }
}

void _gpio_set_pin_mode_impl(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode) {
    assert(IS_GPIO_MODE(mode) && IS_GPIO_PIN_AVAILABLE(port, pin));

    uint32_t pos = 0;
    while (!(pin & (1U << pos))) pos++;
    pin = pin & (1U << pos);

    uint32_t temp = port->MODER;
    temp &= ~(GPIO_MODER_MODE0 << (pos * 2U));
    temp |= (mode & GPIO_MODE) << (pos * 2U);
    port->MODER = temp;

    if (
      mode == GPIO_MODE_OUTPUT_PP || mode == GPIO_MODE_OUTPUT_OD || mode == GPIO_MODE_AF_PP ||
      mode == GPIO_MODE_AF_OD) {
        temp = port->OTYPER;
        temp &= ~(GPIO_OTYPER_OT_0 << pos);
        temp |= ((mode & GPIO_OUTPUT_TYPE) >> 4U) << pos;
        port->OTYPER = temp;
    } else if ((mode & EXTI_MODE) == EXTI_MODE) {
        __HAL_RCC_SYSCFG_CLK_ENABLE();

        temp = SYSCFG->EXTICR[pos >> 2U];
        CLEAR_BIT(temp, ((uint32_t)0x0FU) << (4U * (pos & 0x03U)));
        SET_BIT(temp, (GPIO_GET_INDEX(port)) << (4 * (pos & 0x03U)));
        SYSCFG->EXTICR[pos >> 2U] = temp;

        temp = EXTI->IMR;
        temp &= ~((uint32_t)pin);
        if ((mode & GPIO_MODE_IT) == GPIO_MODE_IT) {
            temp |= pin;
        }
        EXTI->IMR = temp;

        temp = EXTI->EMR;
        temp &= ~((uint32_t)pin);
        if ((mode & GPIO_MODE_EVT) == GPIO_MODE_EVT) {
            temp |= pin;
        }
        EXTI->EMR = temp;

        temp = EXTI->RTSR;
        temp &= ~((uint32_t)pin);
        if ((mode & RISING_EDGE) == RISING_EDGE) {
            temp |= pin;
        }
        EXTI->RTSR = temp;

        temp = EXTI->FTSR;
        temp &= ~((uint32_t)pin);
        if ((mode & FALLING_EDGE) == FALLING_EDGE) {
            temp |= pin;
        }
        EXTI->FTSR = temp;
    }
}

void _gpio_set_pin_pull_impl(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull) {
    assert(IS_GPIO_PULL(pull) && IS_GPIO_PIN_AVAILABLE(port, pin));

    uint32_t pos = 0;
    while (!(pin & (1U << pos))) pos++;

    uint32_t temp = port->PUPDR;
    temp &= ~(GPIO_PUPDR_PUPD0 << (pos * 2U));
    temp |= (pull << (pos * 2U));

    port->PUPDR = temp;
}

void _gpio_set_pin_speed_impl(gpio_port_t port, gpio_pin_t pin, gpio_speed_t speed) {
    assert(IS_GPIO_SPEED(speed) && IS_GPIO_PIN_AVAILABLE(port, pin));

    uint32_t pos = 0;
    while (!(pin & (1U << pos))) pos++;

    uint32_t temp = port->OSPEEDR;
    temp &= ~(GPIO_OSPEEDER_OSPEED0 << (pos * 2U));
    temp |= speed << (pos * 2U);
    port->OSPEEDR = temp;
}

void _gpio_set_pin_af_impl(gpio_port_t port, gpio_pin_t pin, gpio_af_t af) {
    assert(IS_GPIO_AF_INSTANCE(port) && IS_GPIO_AF(af) && IS_GPIO_PIN_AVAILABLE(port, pin));

    uint32_t pos = 0;
    while (!(pin & (1U << pos))) pos++;

    uint32_t temp = port->AFR[pos >> 3U];
    temp &= ~((uint32_t)0xFU << ((uint32_t)(pos & (uint32_t)0x07U) * 4U));
    temp |= ((uint32_t)af << (((uint32_t)pos & (uint32_t)0x07U) * 4U));
    port->AFR[pos >> 3U] = temp;
}

void _gpio_config_pin_impl(gpio_port_t port, gpio_pin_t pin, gpio_config_t* config) {
    GPIO_InitTypeDef init = {
        .Pin = pin,
        .Mode = config->mode,
        .Pull = config->pull,
        .Speed = config->speed,
        .Alternate = config->af,
    };
    HAL_GPIO_Init(port, &init);
}

void _gpio_unconfig_pin_impl(gpio_port_t port, gpio_pin_t pin) {
    HAL_GPIO_DeInit(port, pin);
}