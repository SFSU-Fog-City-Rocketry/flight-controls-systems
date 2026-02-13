#include <esp32/steady_clock.hpp>
#include <cstdint>
#include "esp_timer.h"

namespace hal::esp32 {
    uint64_t steady_clock::frequency() {
        return static_cast<uint64_t>(esp_timer_get_time());
    }
};
