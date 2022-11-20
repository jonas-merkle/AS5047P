#include "AS5047P_SPI_Arduino.h"

/**
 * @file AS5047P_SPI_Arduino.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This sourefile contains the implementation of the Arduino SPI bus handler for the AS5047P Library.
 * @version 2.2.0
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#include <Arduino.h>
#include "types/AS5047P_Types.h"

namespace AS5047P_ComBackend {

    AS5047P_SPI::AS5047P_SPI(const uint8_t chipSelectPinNo, const uint32_t spiSpeed) {
        
        this->__chipSelectPinNo = chipSelectPinNo;
        this->__spiSettings = SPISettings(spiSpeed, MSBFIRST, SPI_MODE1);

        pinMode(__chipSelectPinNo, OUTPUT);
        digitalWrite(__chipSelectPinNo, HIGH);
    }

    void AS5047P_SPI::init() {
        SPI.begin();
    }

    void AS5047P_SPI::write(const uint16_t regAddress, const uint16_t data) {

        // init spi interface
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.begin();
        #endif
        SPI.beginTransaction(__spiSettings);

        // set register address
        digitalWrite(__chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(__chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        __delay100Ns();
        #else
        delayMicroseconds(1);
        #endif
        
        // write data
        digitalWrite(__chipSelectPinNo, LOW);
        SPI.transfer16(data);
        digitalWrite(__chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        __delay100Ns();
        #else
        delayMicroseconds(1);
        #endif

        // close spi interface
        SPI.endTransaction();
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.end();
        #endif

    }


    uint16_t AS5047P_SPI::read(const uint16_t regAddress) {
        
        uint16_t receivedData = 0;
        
        // init spi interface
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.begin();
        #endif
        SPI.beginTransaction(__spiSettings);

        // set register address
        digitalWrite(__chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(__chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        __delay100Ns();
        #else
        delayMicroseconds(1);
        #endif
        
        // write nop & reading data
        digitalWrite(__chipSelectPinNo, LOW);
        AS5047P_Types::SPI_Command_Frame_t nopFrame(AS5047P_Types::NOP_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);
        receivedData = SPI.transfer16(nopFrame.data.raw);
        digitalWrite(__chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        __delay100Ns();
        #else
        delayMicroseconds(1);
        #endif
        

        // close spi interface
        SPI.endTransaction();
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.end();
        #endif

        return receivedData;

    }

    #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY) 

    const void AS5047P_SPI::__delay100Ns() {
        for (uint16_t i = 0; i < __numberOfNops; i++) {
            __asm__("nop");
        }
    }

    #endif
}
