#pragma once
#include <cstdint>
#include <span>
#include <esp32/errors.hpp>

namespace hal::esp32 {


    enum class can_mode {
        normal = 0,
        listen_only = 1,
        self_test = 2
    };


    struct can_message {
        uint32_t id;
        std::span<const uint8_t> data;
        uint8_t data_length;
        uint8_t ticks=0x00;
    };

    class can {
    public:
        /**
         * @brief Can settings for configurint pins to inter-communicating to
         * 
         */
        struct settings {
            uint8_t tx = 0x0;
            uint8_t rx = 0x0;
            bool enabled=false;
            can_mode mode = can_mode::normal;
        };
    public:
        can(const settings& p_settings) {
            configure(p_settings);
        }

        ~can();

        void configure(const settings& p_settings);

        can_error_type transmit(std::span<const can_message>);

        [[nodiscard]] bool is_ready() const {
            return m_ready;
        }


    private:
        bool m_ready = false;
    };
};
