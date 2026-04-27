#pragma once
#include "driver/twai.h"
#include <chrono>
#include <array>

namespace hal::esp32 {
    /**
    * @brief Initializer macros for timing configuration structure
    *
    * The following initializer macros offer commonly found bit rates. These macros
    * place the sample point at 80% or 67% of a bit time.
    *
    * @note The available bit rates are dependent on the chip target and ECO version.
    */
    #if SOC_TWAI_BRP_MAX > 256
    // #define TWAI_TIMING_CONFIG_1KBITS()     {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twaitwai_timing_config_t config_timing_1kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_5KBITS()     {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 100000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_twai_timing_config_t config_timing_5kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 100000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_10KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 200000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_10kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 200000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    #endif // SOC_TWAI_BRP_MAX > 256

    #if (SOC_TWAI_BRP_MAX > 128) || (CONFIG_ESP32_REV_MIN_FULL >= 200)
    // #define TWAI_TIMING_CONFIG_12_5KBITS()  {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 312500, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_12_5kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 312500, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_16KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 400000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_16kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 400000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_20KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 400000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    #endif // (SOC_TWAI_BRP_MAX > 128) || (CONFIG_ESP32_REV_MIN_FULL >= 200)

    #if SOC_TWAI_CLK_SUPPORT_XTAL
    // #define TWAI_TIMING_CONFIG_25KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 500000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_25kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 500000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    #else   // APB80M
    // twai_timing_config_t TWAI_TIMING_CONFIG_25KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 625000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_25kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 625000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    #endif
    // #define TWAI_TIMING_CONFIG_50KBITS()    {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 1000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_50kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 1000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_100KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 2000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_100kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 2000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_125KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 2000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_125kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 2000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_250KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 4000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 2, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_250kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 4000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 2, .ssp_offset = 0, .triple_sampling = false};
    }
    #if SOC_TWAI_CLK_SUPPORT_XTAL && CONFIG_XTAL_FREQ == 40   // TWAI_CLK_SRC_XTAL = 40M
    // #define TWAI_TIMING_CONFIG_500KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 10000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_500kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 10000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_800KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_800kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_1MBITS()     {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_1mbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_800KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_800kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 16, .tseg_2 = 8, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_1MBITS()     {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_1mbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 20000000, .brp = 0, .prop_seg = 0, .tseg_1 = 15, .tseg_2 = 4, .sjw = 3, .ssp_offset = 0, .triple_sampling = false};
    }
    #else   // 32M, 48M, APB80M
    // #define TWAI_TIMING_CONFIG_500KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 2, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_500kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 11, .tseg_2 = 4, .sjw = 2, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_800KBITS()   {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 6, .tseg_2 = 3, .sjw = 1, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_800kbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 6, .tseg_2 = 3, .sjw = 1, .ssp_offset = 0, .triple_sampling = false};
    }
    // #define TWAI_TIMING_CONFIG_1MBITS()     {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 5, .tseg_2 = 2, .sjw = 1, .ssp_offset = 0, .triple_sampling = false}
    inline constexpr twai_timing_config_t config_timing_1mbits() {
        return {.clk_src = TWAI_CLK_SRC_DEFAULT, .quanta_resolution_hz = 8000000, .brp = 0, .prop_seg = 0, .tseg_1 = 5, .tseg_2 = 2, .sjw = 1, .ssp_offset = 0, .triple_sampling = false};
    }
    #endif

    /**
    * @brief   Initializer macro for filter configuration to accept all IDs
    */
    // #define TWAI_FILTER_CONFIG_ACCEPT_ALL() {.acceptance_code = 0, .acceptance_mask = 0xFFFFFFFF, .single_filter = true}
    inline constexpr twai_filter_config_t config_filter_accept_all() {
        return {.acceptance_code = 0, .acceptance_mask = 0xFFFFFFFF, .single_filter = true};
    }

    template <typename Rep, typename Period>
    constexpr TickType_t to_ticks(std::chrono::duration<Rep, Period> d) {
        using FreeRTOSTicks = std::chrono::duration<TickType_t, std::ratio<1, configTICK_RATE_HZ>>;
        return std::chrono::duration_cast<FreeRTOSTicks>(d).count();
    }
};