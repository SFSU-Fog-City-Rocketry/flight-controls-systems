#include "esp_err.h"
#include <esp32/i2c_controller.hpp>
#include <span>
#include <cstdint>

namespace hal::espe32 {

    i2c_controller::i2c_controller(uint8_t p_port, const settings& p_settings) {
        i2c_master_bus_config_t bus_config = {
            .i2c_port = p_port,
            .sda_io_num = p_settings.sda,
            .scl_io_num = p_settings.scl,
            .clk_source = p_settings.clk,
            .glitch_ignore_cnt = p_settings.glitch_ignore,
            .flags = { .enable_internal_pullup = true },
        };

        i2c_new_master_bus(&bus_config, &bus_handle);
    }

    i2c_controller::~i2c_controller() {
        i2c_master_bus_rm_device(m_dev);
        i2c_del_master_bus(m_bus);
    }

    //! @brief Sends data to targeted device
    void i2c_controller::transmit(std::span<const uint8_t> p_bytes, uint16_t p_timeout) {
        i2c_master_transmit(m_dev, p_bytes.data(), p_bytes.size_bytes(), p_timeout);
    }

    //! @brief Reads data from specified target device.
    void i2c_controller::receive(std::span<const uint8_t> p_bytes, uint16_t p_timeout) {
        i2c_master_receive(m_dev, p_bytes.data(), p_bytes.size_bytes(), p_timeout);
    }

    //! @brief Combines both write-then-read transaction
    void i2c_controller::transmit_receive(uint8_t p_address, std::span<const uint8_t> p_response, uint16_t p_timeout) {
        i2c_master_transmit_receive(m_dev, &p_address, p_response.data(), p_response.size_bytes(), p_timeout);
    }

    //! @brief Scans/probs specific address on the bus if the peripheral ACK'd.
    //! @return ESP_OK if device is found, otherwise device not found
    esp_err_t i2c_controller::probe(uint8_t p_address, uint8_t p_value) {
        return i2c_master_probe(m_bus, p_address, p_value);
    }


    //! @brief Registers peripheral to the I2C controller bus
    void i2c_controller::add_device(const device_settings& p_settings) {
        i2c_device_config_t config = {
            .dev_addr_length = p_settings.length,
            .device_address = p_settings.address,
            .scl_speed_hz = p_settings.scl_speed,
        };
        i2c_master_bus_add_device(m_bus, &config, &m_dev);
    }
};