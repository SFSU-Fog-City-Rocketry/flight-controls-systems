#pragma once
#include <cstdint>

namespace hal::esp32 {
    class input_pin {
    public:
        input_pin() = delete;
        input_pin(uint8_t p_port, uint8_t p_pin);
        
        input_pin(input_pin const& p_other) = delete;
        input_pin& operator=(input_pin const& p_other) = delete;
        input_pin(input_pin&& p_other) noexcept = delete;
        input_pin& operator=(input_pin&& p_other) noexcept = delete;
        ~input_pin() = default;

        /*
         * Used for reading the state of the pin
         *
         * 0 - State is LOW
         * 1 - State is HIGH
         *
         * */
        bool level();
    private:
        uint8_t m_port;
        uint8_t m_pin;
    };
};