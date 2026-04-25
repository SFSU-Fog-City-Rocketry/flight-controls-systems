#include <esp32/can.hpp>
#include "driver/twai.h"

namespace hal::esp32 {

    void can::configure(const settings& p_settings) {
        if (p_settings.enabled) {
            twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(static_cast<gpio_num_t>(p_settings.rx), static_cast<gpio_num_t>(p_settings.tx), static_cast<twai_mode_t>(p_settings.mode));
            twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
            twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

            //Install twai driver
            if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
            }
            else {
                return;
            }

            //Start twai driver
            if (twai_start() == ESP_OK) {
                m_ready = true;
            }
            else {
                m_ready = false;
                return;
            }
        }
    }
};
