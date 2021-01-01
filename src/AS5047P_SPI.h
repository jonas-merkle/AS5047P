#ifndef AS5047P_SPI_h
#define AS5047P_SPI_h

#include <inttypes.h>
#include <SPI.h>

#include "AS5047P_SPI.h"

namespace AS5047P_ComBackend {

    class AS5047P_SPI {
    
        public:

            AS5047P_SPI(uint8_t chipSelectPinNo, uint32_t spiSpeed = 100000);

            void write(uint16_t regAddress, uint16_t data);
            uint16_t read(uint16_t regAddress);


        private:

            uint8_t chipSelectPinNo;
            SPISettings spiSettings;

    };

}

#endif // AS5047P_SPI_h