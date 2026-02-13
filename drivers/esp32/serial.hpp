#pragma once
#include <esp_log.h>
#include <utility>

namespace hal::esp32 {
    
    /*
     * @param p_tag is the tag to filter out print messages
     * @param p_fmt is the formatted mesage to print serially
     * @param p_params are variadic arguments of values to print through serial
    */
    template<typename... Parameters>
    void print(const char* p_tag, const char* p_fmt, Parameters&&... p_params) {
        esp_log_write(ESP_LOG_INFO, p_tag, LOG_COLOR_I "I (%lu) %s: ", esp_log_timestamp(), p_tag);
        esp_log_write(ESP_LOG_INFO, p_tag, p_fmt, std::forward<Parameters>(p_params)...);
        esp_log_write(ESP_LOG_INFO, p_tag, LOG_RESET_COLOR "\n");
    }
};
