#pragma once
#include <cstdint>

namespace hal::esp32 {
    
    /*
     * Digital output pin specifically for the esp32-wroom-32 device
     *
     * Use this abstraction to toggle between HIGH and LOW to sending a signal to the LED.
     *
     * */
    class output_pin {
    public:
        output_pin() = delete;
        /*
         *
         * @param p_port select the pin port to use
         * @param p_pin select specific pin at the specific port to use for this output pin.
         *
        */
        output_pin(uint8_t p_port, uint8_t p_pin);
        output_pin(output_pin const& p_other) = delete;
        output_pin& operator=(output_pin const& p_other) = delete;
        output_pin(output_pin&& p_other) noexcept = delete;
        output_pin& operator=(output_pin&& p_other) noexcept = delete;
        ~output_pin() = default;
        
        /*
         * Used for setting the state of the pin
         *
         * 0 - State set to LOW
         * 1 - State set to HIGH
         *
         * */
        void level(bool p_value);
        

    private:
        uint8_t m_port;
        uint8_t m_pin;
    };
};
