/**
 * @file AS5047P_SPI_Zephyr.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This sourefile contains the implementation of the Zephyr SPI bus handler for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#include "AS5047P_SPI_Zephyr.h"

// disable in non Zephyr op mode
#if defined(AS5047P_OP_MODE_Zephyr)

// as5047p libraries
#include "./../types/AS5047P_Types.h"

// arduino libraries
#include <Arduino.h>


namespace AS5047P_ComBackend {

    AS5047P_SPI_Zephyr::AS5047P_SPI_Zephyr() {
        
    }

    void AS5047P_SPI_Zephyr::init() {

    }

    void AS5047P_SPI_Zephyr::write(const uint16_t regAddress, const uint16_t data) {

    }

    uint16_t AS5047P_SPI_Zephyr::read(const uint16_t regAddress) {

        return 0;
    }
}

#endif // AS5047P_OP_MODE_Zephyr