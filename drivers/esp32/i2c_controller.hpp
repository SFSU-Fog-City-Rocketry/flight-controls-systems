#pragma once
// #include <esp_err.h>
#include <driver/i2c_master.h>
#include <cstdint>
#include <span>

namespace hal::espe32 {

    struct settings {
        uint8_t sda=0x0;
        uint8_t scl=0x0;
        uint8_t clk=0x0;
        uint8_t glitch_ignore=0x7;
        uint8_t interrupt_priority=0x0;
    };

    struct device_settings {
        uint8_t length=0x0;
        uint8_t address=0x0;
        uint32_t scl_speed=100000; // 100kHz
    };

    class i2c_controller {
    public:
        i2c_controller(uint8_t p_port, const settings& p_settings);

        ~i2c_controller();

        //! @brief Sends data to targeted device
        void transmit(std::span<const uint8_t> p_bytes, uint16_t p_timeout=1000);

        //! @brief Reads data from specified target device.
        void receive(std::span<const uint8_t> p_bytes, uint16_t p_timeout=1000);

        //! @brief Combines both write-then-read transaction
        void transmit_receive(uint8_t p_address, std::span<const uint8_t> p_response, uint16_t p_timeout=1000);

        //! @brief Scans/probs specific address on the bus if the peripheral ACK'd.
        //! @return ESP_OK if device is found, otherwise device not found
        esp_err_t probe(uint8_t p_address, uint8_t p_value);


        //! @brief Registers peripheral to the I2C controller bus
        void add_device(const device_settings& p_settings);


    private:
        i2c_master_bus_handle_t m_bus=nullptr;
        i2c_master_dev_handle_t m_dev=nullptr;
    };
};