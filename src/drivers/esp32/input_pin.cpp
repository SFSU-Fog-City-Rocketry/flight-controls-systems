#include <esp32/input_pin.hpp>
#include "driver/gpio.h"
#include "hal/gpio_types.h"

namespace hal::esp32 {
    input_pin::input_pin(uint8_t p_port, uint8_t p_pin) : m_port(p_port), m_pin(p_pin) {
        gpio_config_t io_conf = {};
    
        // 2. Set the bit mask for the pins you want to configure
        io_conf.pin_bit_mask = (1ULL << m_pin);
        
        // 3. Set the mode (Input)
        io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
        // 4. Configure Pull-ups/Pull-downs
        // Enable pull-up if you're using a button connected to GND
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE; 
        io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        
        // 5. Disable interrupts (for simple polling)
        io_conf.intr_type = GPIO_INTR_DISABLE;
        gpio_config(&io_conf);
    }

    bool input_pin::level() {
        return gpio_get_level(static_cast<gpio_num_t>(m_pin));
    }

};