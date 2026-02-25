#pragma once
#include <cstdint>
#include <span>

#include <esp32/serial.hpp>
#include <nonstd/ring_span.hpp>

namespace hal::esp32 {

    enum parity : uint8_t {
        disable = 0x0,
        odd = 0x1,
        even = 0x2
    };

    enum class flow_control_mode : uint8_t {
        disable=0x0, // disable hardware flow control
        rts=0x1,     // enable RX hardware flow control (rts)
        cts=0x2,     // enable TX hardware flow control  (cts)
        cts_rts=0x3, // enable hardware flow control
        max=0x4
    };

    struct settings {
        uint32_t baud_rate=115200;
        uint8_t word_length=0x3; // 0: 5 bits, 1: 6 bits, 2: 7 bits, 3: 8 bits
        uint8_t stop_bit=0x1;
        parity parity_bit=parity::disable; // 0: None, 1: Odd, 2: Even
        flow_control_mode control_mode=flow_control_mode::cts_rts;
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
         * @param p_buffer are the bytes to write
         * @return int32_t returns -1 if invalid bytes written, otherwise returns the length of bytes written
         */
        serial::message write(std::span<uint8_t> p_in_buffer);

        /**
         * @brief 
         * 
         * @param p_in_buffer is the buffer to read
         * @return int32_t returns -1 if invalid bytes written, otherwise returns the length of bytes written
         */
        serial::message read(std::span<uint8_t> p_out_bytes);
        /**
         * @brief Reading the available length for writing a buffer
         * 
         * @return int32_t returns -1 if invalid bytes written, otherwise returns the length of bytes written
         */
        int32_t read_length();

    private:
        uint8_t m_port;
        nonstd::ring_span<uint8_t> m_receive_buffer;
    };
};