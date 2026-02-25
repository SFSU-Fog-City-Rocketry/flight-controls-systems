#pragma once
#include <span>
#include <cstdint>

namespace hal::esp32::serial {

    struct message {
        std::span<uint8_t> data{};
        uint32_t capacity=0;
    };
};
