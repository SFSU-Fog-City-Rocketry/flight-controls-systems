#pragma once
#include <cstdint>
#include <span>
#include <nonstd/ring_span.hpp>

namespace hal::esp32 {


    enum parity : uint8_t {
        disable = 0x0,
        odd = 0x1,
        even = 0x2
    };

    struct settings {
        uint32_t baud_rate=115200;
        uint8_t word_length=0x3; // 0: 5 bits, 1: 6 bits, 2: 7 bits, 3: 8 bits
        uint8_t stop_bit=0x1;
        // uint8_t parity=0; // 0: None, 1: Odd, 2: Even
        enum parity parity=parity::disable;
        uint8_t tx=0;
        uint8_t rx=0;
    };

    class uart {
    public:
        uart() = delete;
        /**
         * @brief Construct a new uart object
         * 
         * @param p_port is the port to do serial communication to
         * @param p_receive_buffer is the buffer to pre-allocate buffer for passing
         * @param p_settings 
         */
        uart(uint8_t p_port, std::span<uint8_t> p_receive_buffer, const settings& p_settings);

        ~uart() = default;
        uart(const uart&) = delete;
        uart& operator=(const uart&) = delete;
        uart(uart&&) = delete;
        uart& operator=(uart&&) = delete;

        /**
         * @brief Set the loop back object for the particular port with this uart driver
         * 
         * @param p_value is true to enable lookback, otherwise false to disable
         */
        void set_loop_back(bool p_value);

        /**
         * @brief transmitting bytes of data
         * 
         * @param p_buffer 
         * @return uint32_t
         */
        uint32_t write(std::span<const uint8_t> p_buffer);

        /**
         * @brief 
         * 
         * @param p_in_buffer 
         * @return uint32_t 
         */
        uint32_t read(std::span<uint8_t> p_in_buffer);

        /**
         * @brief Reading the available length for writing a buffer
         * 
         * @return uint32_t
         */
        uint32_t read_length();

    private:
        uint8_t m_port;
        nonstd::ring_span<uint8_t> m_receive_buffer;
    };
};