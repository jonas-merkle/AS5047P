#include "AS5047P_SPI.h"

#include <Arduino.h>
#include "AS5047P_types.h"

namespace AS5047P_ComBackend {

    AS5047P_SPI::AS5047P_SPI(const uint8_t chipSelectPinNo, const uint32_t spiSpeed = 100000) { // todo: check for: 14000000
        
        this->chipSelectPinNo = chipSelectPinNo;
        this->spiSettings = SPISettings(spiSpeed, MSBFIRST, SPI_MODE1);

        pinMode(chipSelectPinNo, OUTPUT);
        digitalWrite(chipSelectPinNo, HIGH);

    }

    void AS5047P_SPI::write(const uint16_t regAddress, const uint16_t data) {

        SPI.beginTransaction(spiSettings);

        // Send command
        digitalWrite(chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(chipSelectPinNo, HIGH);
        delayMicroseconds(1);
        
        // Read data
        digitalWrite(chipSelectPinNo, LOW);
        SPI.transfer16(data);
        digitalWrite(chipSelectPinNo, HIGH);
        delayMicroseconds(1);

        SPI.endTransaction();

    }


    uint16_t AS5047P_SPI::read(const uint16_t regAddress) {
        
        uint16_t receivedData = 0;
        
        SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1));

        // Send Read Command
        digitalWrite(chipSelectPinNo, LOW);
        SPI.transfer16(regAddress);
        digitalWrite(chipSelectPinNo, HIGH);
        delayMicroseconds(1);
        
        // Send Nop Command while receiving data
        digitalWrite(chipSelectPinNo, LOW);
        receivedData = SPI.transfer16(AS5047P_types::NOP_t::REG_ADDRESS);
        digitalWrite(chipSelectPinNo, HIGH);
        delayMicroseconds(1);
        
        SPI.endTransaction();

        return receivedData;

    }
}