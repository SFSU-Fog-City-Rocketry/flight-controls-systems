#include <esp32/output_pin.hpp>

#include "driver/gpio.h"


namespace hal::esp32 {

    output_pin::output_pin(uint8_t p_port, uint8_t p_pin) : m_port(p_port), m_pin(p_pin) {}

    void output_pin::level(bool p_value) {
        gpio_reset_pin(static_cast<gpio_num_t>(m_pin));
        gpio_set_direction(static_cast<gpio_num_t>(m_pin), GPIO_MODE_OUTPUT);
        gpio_set_level(static_cast<gpio_num_t>(m_pin), p_value);
    }
};
