#include <hal/uart_types.h>
#include <esp32/serial.hpp>
#include <esp32/utils.hpp>
#include <esp32/uart.hpp>
#include <esp32/can.hpp>
#include <array>
#include <span>

#include <memory_resource>

extern "C" void app_main() {
    hal::esp32::print("Serial", "Demo Application Initiated!");

    hal::esp32::can::settings can_settings{.tx=0x4, .rx=0x5, .enabled=true, .mode=hal::esp32::can_mode::normal};
    hal::esp32::can can_bus(can_settings);
    while(true) {

        hal::esp32::print("CAN", "Is CAN bus ready? %s", can_bus.is_ready() ? "Yes" : "No");
        hal::esp32::delay(20);
    }
}
