#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <span>
#include <vector>
#include "driver/gpio.h"

static constexpr const char* TAG = "APP";


void print_span(std::span<const uint8_t> p_data) {
    
    for(const auto& i : p_data) {
        ESP_LOGI("I", "%i", i);
    }
}

// main entry point for application
extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Starting ESP-IDF with LLVM/Clang...");
    auto gpio_2 = 2;
    while(true) {
        gpio_reset_pin(GPIO_NUM_2);
        gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(2000);
        
        gpio_set_level(static_cast<gpio_num_t>(gpio_2), 0);
        vTaskDelay(2000);
    }

    std::vector<uint8_t> payload = {0x1, 0x2, 0x3};

    print_span(payload);
}
