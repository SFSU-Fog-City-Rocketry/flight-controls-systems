#include <esp32/can.hpp>
#include "driver/twai.h"
#include <esp32/can_utils.hpp>
#include <chrono>

namespace hal::esp32 {

    constexpr twai_general_config_t create_twai_general_config(int controller_num, gpio_num_t tx_io, gpio_num_t rx_io, twai_mode_t op_mode) {
        return twai_general_config_t {
            .controller_id  = controller_num,
            .mode           = op_mode,
            .tx_io          = tx_io,
            .rx_io          = rx_io,
            .clkout_io      = TWAI_IO_UNUSED,
            .bus_off_io     = TWAI_IO_UNUSED,
            .tx_queue_len   = 5,
            .rx_queue_len   = 5,
            .alerts_enabled = TWAI_ALERT_NONE,
            .clkout_divider = 0,
            .intr_flags     = ESP_INTR_FLAG_LEVEL1,
            .general_flags  = {0} // Designated initializers (C++20)
        };
    }

    /**
    * @brief Overload for the default V1 behavior (Controller ID 0).
    */
    constexpr twai_general_config_t create_twai_general_config_default(gpio_num_t tx_io, gpio_num_t rx_io, twai_mode_t op_mode) {
        return create_twai_general_config(0, tx_io, rx_io, op_mode);
    }

    void can::configure(const settings& p_settings) {
        if (p_settings.enabled) {
            twai_general_config_t g_config = create_twai_general_config_default(
                static_cast<gpio_num_t>(p_settings.rx),
                static_cast<gpio_num_t>(p_settings.tx),
                static_cast<twai_mode_t>(p_settings.mode)
            );
            twai_timing_config_t t_config = config_timing_500kbits();
            twai_filter_config_t f_config = config_filter_accept_all();

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

    can::~can() {
        if (m_ready) {
            twai_stop();
            twai_driver_uninstall();
            m_ready = false;
        }
    }

    can_error_type can::transmit(std::span<const can_message>) {
        using namespace std::chrono_literals;

        twai_message_t message;
        message.identifier = 0xAAAA;
        message.flags = TWAI_MSG_FLAG_EXTD;
        message.data_length_code = 4;
        for (int i = 0; i < 4; i++) {
            message.data[i] = 0;
        }

        // const auto res = twai_transmit(&message, to_ticks(1000ms));
        const auto res = twai_transmit(&message, pdMS_TO_TICKS(1000));

        return static_cast<can_error_type>(res);
    }
};
