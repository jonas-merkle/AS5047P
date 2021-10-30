/**
 * @file AS5047P_SPI.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This headerfile contains the pure virtual SPI bus handler for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_SPI_h
#define AS5047P_SPI_h

// std libraries
#include <inttypes.h>

/**
 * @namespace AS5047P_ComBackend
 * @brief The namespace for the communication backend of the AS5047P sensor.
 */
namespace AS5047P_ComBackend {

    /**
     * @class AS5047P_SPI
     * @brief The arduino spi interface wrapper class for the AS5047P sensor.
     */
    class AS5047P_SPI {
    
        public:

            /**
             * Initializes the spi interface.
             */
            virtual void init() = 0;

            /**
             * Wirte data to register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be written.
             * @param data The data to wirte.
             */
            virtual void write(uint16_t regAddress, uint16_t data) const = 0;

            /**
             * Read tata from a register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be read.
             * @return The data in the register.
             */ 
            virtual uint16_t read(uint16_t regAddress) const = 0;


        private:

    };

}

#endif // AS5047P_SPI_h
