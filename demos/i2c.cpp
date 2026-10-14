#include <cstring>
#include <driver/i2c_master.h>
#include <esp32/i2c_controller.hpp>

static const uint32_t port = I2C_NUM_1;

// main entry point for application
extern "C" void app_main() {

    hal::espe32::i2c_controller peripheral = hal::esp32::i2c_controller()

}