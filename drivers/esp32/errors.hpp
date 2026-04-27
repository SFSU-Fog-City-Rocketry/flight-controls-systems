#pragma once
#include "driver/twai.h"

namespace hal::esp32 {
    enum can_error_type : uint32_t {
        ok                    = 0,          /*!< success (no error) */
        fail                  = 0xFFFFFFFF, /*!< Generic failure (-1) */

        no_mem            = 0x101,      /*!< Out of memory */
        invalid_arg       = 0x102,      /*!< Invalid argument */
        invalid_state     = 0x103,      /*!< Invalid state */
        invalid_size      = 0x104,      /*!< Invalid size */
        not_found         = 0x105,      /*!< Requested resource not found */
        not_supported     = 0x106,      /*!< Operation or feature not supported */
        timeout           = 0x107,      /*!< Operation timed out */
        invalid_response  = 0x108,      /*!< Received response was invalid */
        invalid_crc       = 0x109,      /*!< CRC or checksum was invalid */
        invalid_version   = 0x10A,      /*!< Version was invalid */
        invalid_mac       = 0x10B,      /*!< MAC address was invalid */
        not_finished      = 0x10C,      /*!< Operation has not fully completed */
        not_allowed       = 0x10D,      /*!< Operation is not allowed */

        wifi_base         = 0x3000,     /*!< Starting number of WiFi error codes */
        mesh_base         = 0x4000,     /*!< Starting number of MESH error codes */
        flash_base        = 0x6000,     /*!< Starting number of flash error codes */
        hw_crypto_base    = 0xC000,     /*!< Starting number of HW cryptography module error codes */
        memprot_base      = 0xD000      /*!< Starting number of Memory Protection API error codes */
    };

    struct can_error {
        can_error_type error_type;  
        uint8_t length=0x0;
    };
};