#pragma once
#include <cstdint>

namespace hal::esp32 {

    class steady_clock {
    public:
        uint64_t frequency();
    };
};
