#include <esp32/utils.hpp>
#include <esp32/steady_clock.hpp>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

namespace hal::esp32 { 
    void delay(uint32_t p_ms) {
        vTaskDelay(200);
    }
};
