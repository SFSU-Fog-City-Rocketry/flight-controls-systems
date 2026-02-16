#include "hal/uart_types.h"
#include <esp32/serial.hpp>
#include <esp32/input_pin.hpp>
#include <esp32/output_pin.hpp>
#include <esp32/utils.hpp>
#include <esp32/uart.hpp>
#include <array>

extern "C" void app_main() {
    hal::esp32::print("Serial", "Demo Application Initiated!");
    hal::esp32::output_pin gpio2(0, 0x02);
    hal::esp32::input_pin input_gpio2(0, 0x02);

    std::array<uint8_t, 10> receive_buffer{};
    hal::esp32::settings settings{.baud_rate=115200, .tx=0x4, .rx=0x5};
    hal::esp32::uart uart_console(0x1, receive_buffer, settings);

    while(true) {

        std::array<uint8_t, 3> payload = {0x1, 0x2, 0x3};
        const int bytes_written = uart_console.write(payload);
        hal::esp32::print("Serial", "Wrote %d bytes", bytes_written);

        // hal::esp32::delay(20);

        const int length_of_buffer = uart_console.read(receive_buffer);
        // const size_t length_of_buffer = console.read_length();
        hal::esp32::print("Serial", "Received %d bytes", length_of_buffer);

        for(const auto& byte : receive_buffer) {
            hal::esp32::print("Serial", "Received byte: %d", byte);
        }
        hal::esp32::delay(20);

        // gpio2.level(true);
        // hal::esp32::print("Serial", "input_pin: %d", input_gpio2.level());
        // gpio2.level(false);
        // hal::esp32::print("Serial", "input_pin: %d", input_gpio2.level());
        // hal::esp32::delay(20);
    }

}
