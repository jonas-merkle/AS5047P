/**
 * @file AS5047P_SPI_Arduino.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This headerfile contains the Arduino SPI bus handler for the AS5047P Library.
 * @version 2.2.0
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_SPI_ARDUINO_h
#define AS5047P_SPI_ARDUINO_h

#include <inttypes.h>
#include <SPI.h>

#include "./util/AS5047P_Settings.h"

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
             * @param chipSelectPinNo The pin number of the chip select pin (default: 9);
             * @param spiSpeed The spi bus speed (default: 8000000, on Feather M0 tested up to 32000000)
             */
            AS5047P_SPI(uint8_t chipSelectPinNo = 9, uint32_t spiSpeed = 8000000);


            /**
             * Initializes the spi interface.
             */
            void init();


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

            uint8_t __chipSelectPinNo;        ///< The pin number of the chip select pin.
            SPISettings __spiSettings;        ///< The spi bus settings.

            #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)

            const uint16_t __numberOfNops = (uint16_t) ((100 * (F_CPU/1000000L))/1000);     ///< Number of asm nop operations for 100 ns delay.

            /**
             * @brief Custom delay function to wait 100 ns based on asm nop operations.
             * 
             */
            const void __delay100Ns(); 

            #endif

    };

}

#endif // AS5047P_SPI_ARDUINO_h