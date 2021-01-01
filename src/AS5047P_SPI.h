#ifndef AS5047P_SPI_h
#define AS5047P_SPI_h

#include <inttypes.h>
#include <SPI.h>

#include "AS5047P_SPI.h"

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
             * Constructor.
             * @param chipSelectPinNo The pin number of the chip select pin (default: 12);
             * @param spiSpeed The spi bus speed (default: 8000000, on Feather M0 tested up to 32000000)
             */
            AS5047P_SPI(uint8_t chipSelectPinNo = 12, uint32_t spiSpeed = 8000000);


            /**
             * Wirte data to register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be written.
             * @param data The data to wirte.
             */
            void write(uint16_t regAddress, uint16_t data);

            /**
             * Read tata from a register of the AS5047P sensor.
             * @param regAddress The address of the register where the data should be read.
             * @return The data in the register.
             */ 
            uint16_t read(uint16_t regAddress);


        private:

            uint8_t chipSelectPinNo;        ///< The pin number of the chip select pin.
            SPISettings spiSettings;        ///< The spi bus settings.

    };

}

#endif // AS5047P_SPI_h
