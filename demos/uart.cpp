#include <hal/uart_types.h>
#include <esp32/serial.hpp>
#include <esp32/utils.hpp>
#include <esp32/uart.hpp>
#include <array>
#include <span>

extern "C" void app_main() {
    hal::esp32::print("Serial", "Demo Application Initiated!");

    std::array<uint8_t, 2048> bytes{};
    hal::esp32::settings settings{.baud_rate=115200, .tx=0x17, .rx=0x16,};
    hal::esp32::uart uart_console(UART_NUM_1, bytes, settings);

    // Configure TX signal loop back to RX module, just for the test usage. 
    uart_console.set_loop_back(true);

    while(true) {

        std::array<uint8_t, 3> payload = {0x1, 0x2, 0x3};
        hal::esp32::serial::message msg = uart_console.write(payload);
        hal::esp32::delay(20);
        hal::esp32::print("Sent", "Wrote %d bytes", msg.capacity);

        std::array<uint8_t, 3> payload_read{};

        uart_console.read(payload_read);
        for(size_t i = 0; i < payload_read.size(); i++) {
            hal::esp32::print("Received", "I = %i", payload_read[i]);
        }

        hal::esp32::delay(20);
    }
}