#include <esp32/uart.hpp>
#include "driver/uart.h"
#include "hal/uart_types.h"

namespace hal::esp32 {

    uart::uart(/*NOLINT*/uint8_t p_port, std::span<uint8_t> p_receive_buffer, const settings& p_settings) : m_port(p_port), m_receive_buffer(p_receive_buffer.begin(), p_receive_buffer.end()) {

        uart_config_t uart_config = {};
        uart_config.baud_rate = static_cast<int>(p_settings.baud_rate);
        uart_config.data_bits = static_cast<uart_word_length_t>(p_settings.word_length);
        uart_config.parity = static_cast<uart_parity_t>(p_settings.parity_bit);
        uart_config.stop_bits = static_cast<uart_stop_bits_t>(p_settings.stop_bit);
        uart_config.flow_ctrl = static_cast<uart_hw_flowcontrol_t>(p_settings.control_mode);
        uart_config.rx_flow_ctrl_thresh = 0x7a;

        uart_driver_install(static_cast<uart_port_t>(m_port), static_cast<int>(p_receive_buffer.size()), static_cast<int>(p_receive_buffer.size_bytes()), 0, nullptr, 0);
        uart_param_config(static_cast<uart_port_t>(m_port), &uart_config);
        // uart_set_mode(static_cast<uint64_t>(p_port), static_cast<uart_mode_t>(p_settings.mode));
        uart_set_pin(static_cast<uart_port_t>(m_port), p_settings.tx, p_settings.rx, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    }

    void uart::set_loop_back(bool p_value) {
        uart_set_loop_back(static_cast<uart_port_t>(m_port), true);
    }

    serial::message uart::write(std::span<uint8_t> p_in_buffer) {
        int capacity = uart_write_bytes(static_cast<uart_port_t>(m_port), p_in_buffer.data(), p_in_buffer.size());

        return {
            .data = p_in_buffer,
            .capacity = static_cast<uint32_t>(capacity),
        };
    }

    serial::message uart::read(std::span<uint8_t> p_out_bytes) {

        const int capacity = uart_read_bytes(static_cast<uart_port_t>(m_port), p_out_bytes.data(), p_out_bytes.size(), 0);

        return {
            .data = p_out_bytes.subspan(0, m_receive_buffer.size()),
            .capacity = static_cast<uint32_t>(capacity),
        };
    }

    int32_t uart::read_length() {
        size_t length = 0;
        uart_get_buffered_data_len(static_cast<uart_port_t>(m_port), &length);
        return static_cast<int32_t>(length);
    }
};