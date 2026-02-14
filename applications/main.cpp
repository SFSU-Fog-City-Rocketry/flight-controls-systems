#include <esp32/serial.hpp>
#include <esp32/input_pin.hpp>
#include <esp32/output_pin.hpp>
#include <esp32/utils.hpp>

// main entry point for application
extern "C" void app_main() {
    hal::esp32::print("Serial", "Demo Application Initiated!");
    hal::esp32::output_pin gpio2(0, 0x02);
    hal::esp32::input_pin input_gpio2(0, 0x02);

    while(true) {
        gpio2.level(true);
        hal::esp32::print("Serial", "input_pin: %d", input_gpio2.level());
        hal::esp32::delay(20);
        gpio2.level(false);
        hal::esp32::print("Serial", "input_pin: %d", input_gpio2.level());
        hal::esp32::delay(20);
    }

}
