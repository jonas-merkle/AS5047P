/**
 * @file AS5047P_SPI_Arduino.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This sourefile contains the implementation of the Arduino SPI bus handler for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#include "AS5047P_SPI_Arduino.h"

// disable in non Arduino op mode
#if defined(AS5047P_OP_MODE_Arduino)

// as5047p libraries
#include "./../types/AS5047P_Types.h"

// arduino libraries
#include <Arduino.h>


namespace AS5047P_ComBackend {

    AS5047P_SPI_Arduino::AS5047P_SPI_Arduino(const uint8_t chipSelectPinNo, const uint32_t spiSpeed) {
        
        this->_chipSelectPinNo = chipSelectPinNo;
        this->_spiSettings = SPISettings(spiSpeed, MSBFIRST, SPI_MODE1);

        pinMode(_chipSelectPinNo, OUTPUT);
        digitalWrite(_chipSelectPinNo, HIGH);
    }

    void AS5047P_SPI_Arduino::init() {
        SPI.begin();
    }

    void AS5047P_SPI_Arduino::write(const uint16_t regAddress, const uint16_t data) const {

        // init spi interface
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.begin();
        #endif // AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.beginTransaction(_spiSettings);

        // set register address
        digitalWrite(_chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(_chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        _delay100Ns();
        #else
        delayMicroseconds(1);
        #endif // F_CPU && AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY
        
        // write data
        digitalWrite(_chipSelectPinNo, LOW);
        SPI.transfer16(data);
        digitalWrite(_chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        _delay100Ns();
        #else
        delayMicroseconds(1);
        #endif // F_CPU && AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY

        // close spi interface
        SPI.endTransaction();
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.end();
        #endif // AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB

    }

    uint16_t AS5047P_SPI_Arduino::read(const uint16_t regAddress) const {
        
        uint16_t receivedData = 0;
        
        // init spi interface
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.begin();
        #endif
        SPI.beginTransaction(_spiSettings);

        // set register address
        digitalWrite(_chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(_chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        _delay100Ns();
        #else
        delayMicroseconds(1);
        #endif // F_CPU && AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY
        
        // write nop & reading data
        digitalWrite(_chipSelectPinNo, LOW);
        AS5047P_Types::SPI_Command_Frame_t nopFrame(AS5047P_Types::NOP_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);
        receivedData = SPI.transfer16(nopFrame.data.raw);
        digitalWrite(_chipSelectPinNo, HIGH);
        #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        _delay100Ns();
        #else
        delayMicroseconds(1);
        #endif // F_CPU && AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY
        

        // close spi interface
        SPI.endTransaction();
        #ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
        SPI.end();
        #endif // AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB

        return receivedData;

    }

    #if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY) 

    void AS5047P_SPI_Arduino::_delay100Ns() const {
        for (uint16_t i = 0; i < _numberOfNops; i++) {
            __asm__("nop");
        }
    }

    #endif // F_CPU && AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY
}

#endif // AS5047P_OP_MODE_Arduino
