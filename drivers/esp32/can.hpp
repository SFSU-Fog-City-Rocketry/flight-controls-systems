#pragma once
#include <cstdint>

namespace hal::esp32 {


    enum class can_mode {
        normal = 0,
        listen_only = 1,
        self_test = 2
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

        void configure(const settings& p_settings);


        [[nodiscard]] bool is_ready() const {
            return m_ready;
        }


    private:
        bool m_ready = false;
    };
};
