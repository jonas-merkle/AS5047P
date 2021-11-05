/**
 * @file AS5047P_SPI_Zephyr.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This headerfile contains the Zephyr SPI bus handler for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_SPI_Zephyr_h
#define AS5047P_SPI_Zephyr_h

// std libraties
#include <inttypes.h>

// as5047p libraries
#include "./../util/AS5047P_Settings.h"
#include "./../spi/AS5047P_SPI.h"

// disable in non Zephyr op mode
#if defined(AS5047P_OP_MODE_Zephyr)
// zephyr libraties
#include <logging/log.h>
#include <devicetree.h>
#include <drivers/spi.h>

/**
 * @namespace AS5047P_ComBackend
 * @brief The namespace for the communication backend of the AS5047P sensor.
 */
namespace AS5047P_ComBackend {

    /**
     * @class AS5047P_SPI_Zephyr
     * @brief The arduino spi interface wrapper class for the AS5047P sensor.
     */
    class AS5047P_SPI_Zephyr : AS5047P_SPI {

        public:

            /**
             * Constructor.
             * @param spiDevSpec The zephyr spi devices spec for the AS5047P sensor.
             */
            explicit AS5047P_SPI_Zephyr(const struct spi_dt_spec *spiDevSpec);

            /**
             * Initializes the spi interface.
             */
            void init() override;


            /**
             * Wirte data to register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be written.
             * @param data The data to wirte.
             */
            void write(uint16_t regAddress, uint16_t data) const override;

            /**
             * Read data from a register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be read.
             * @return The data in the register.
             */
            uint16_t read(uint16_t regAddress) const override;


        private:

            const struct spi_dt_spec *_spiDevSpec;
    };

}
#endif // AS5047P_OP_MODE_Zephyr

#endif // AS5047P_SPI_ARDUINO_h
