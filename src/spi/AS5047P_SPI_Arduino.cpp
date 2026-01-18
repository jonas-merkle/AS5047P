#include "AS5047P_SPI_Arduino.h"

/**
 * @file AS5047P_SPI_Arduino.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Arduino SPI bus backend implementation for the AS5047P library.
 *
 *        Provides a thin wrapper around the Arduino SPI API to handle
 *        command/data frames, chip-select timing, and the readback NOP
 *        transaction required by the AS5047P.
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#include <Arduino.h>
#include "types/AS5047P_Types.h"

namespace AS5047P_ComBackend
{

        AS5047P_SPI::AS5047P_SPI(const uint8_t chipSelectPinNo, const uint32_t spiSpeed)
        {
                // Store configuration and set up SPI settings:
                // - MSB first
                // - SPI mode 1 (CPOL = 0, CPHA = 1) as required by AS5047P
                this->__chipSelectPinNo = chipSelectPinNo;
                this->__spiSettings = SPISettings(spiSpeed, MSBFIRST, SPI_MODE1);

                // Configure CS as output and deassert it (active LOW).
                pinMode(__chipSelectPinNo, OUTPUT);
                digitalWrite(__chipSelectPinNo, HIGH);
        }

        void AS5047P_SPI::init()
        {
                // Initialize the SPI peripheral (idempotent on Arduino).
                SPI.begin();
        }

        void AS5047P_SPI::write(const uint16_t regAddress, const uint16_t data)
        {
                // Optionally (re-)initialize SPI for each transaction if enabled via macro.
#ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
                SPI.begin();
#endif
                SPI.beginTransaction(__spiSettings);

                // -------- Send WRITE command frame (register address) --------
                digitalWrite(__chipSelectPinNo, LOW);
                AS5047P_Types::SPI_Command_Frame_t cmdFrame(regAddress, AS5047P_TYPES_WRITE_CMD);
                SPI.transfer16(cmdFrame.data.raw);
                digitalWrite(__chipSelectPinNo, HIGH);

                // Inter-frame gap: either precise ~100 ns NOPs or a conservative 1 µs delay.
#if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
                __delay100Ns();
#else
                delayMicroseconds(1);
#endif

                // -------- Send WRITE data frame --------
                digitalWrite(__chipSelectPinNo, LOW);
                AS5047P_Types::SPI_WriteData_Frame_t writeFrame(data, AS5047P_TYPES_ALWAYS_LOW);
                SPI.transfer16(writeFrame.data.raw);
                digitalWrite(__chipSelectPinNo, HIGH);

                // Inter-frame gap again to respect device timing.
#if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
                __delay100Ns();
#else
                delayMicroseconds(1);
#endif

                // Close the SPI transaction (and SPI itself if macro requests it).
                SPI.endTransaction();
#ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
                SPI.end();
#endif
        }

        uint16_t AS5047P_SPI::read(const uint16_t regAddress)
        {
                uint16_t receivedData = 0;

                // Optionally (re-)initialize SPI for each transaction if enabled via macro.
#ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
                SPI.begin();
#endif
                SPI.beginTransaction(__spiSettings);

                // -------- Send READ command frame (register address) --------
                digitalWrite(__chipSelectPinNo, LOW);
                AS5047P_Types::SPI_Command_Frame_t cmdFrame(regAddress, AS5047P_TYPES_READ_CMD);
                SPI.transfer16(cmdFrame.data.raw);
                digitalWrite(__chipSelectPinNo, HIGH);

                // Inter-frame gap before issuing the NOP (readback) frame.
#if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
                __delay100Ns();
#else
                delayMicroseconds(1);
#endif

                // -------- Clock out the response with a NOP frame --------
                // Per AS5047P timing, the data is returned during the next frame.
                digitalWrite(__chipSelectPinNo, LOW);
                AS5047P_Types::SPI_Command_Frame_t nopFrame(AS5047P_Types::NOP_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);
                receivedData = SPI.transfer16(nopFrame.data.raw);
                digitalWrite(__chipSelectPinNo, HIGH);

                // Optional inter-frame gap (kept symmetrical with write path).
#if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
                __delay100Ns();
#else
                delayMicroseconds(1);
#endif

                // Close the SPI transaction (and SPI itself if macro requests it).
                SPI.endTransaction();
#ifdef AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB
                SPI.end();
#endif

                return receivedData;
        }

#if defined(F_CPU) && defined(AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY)
        /**
         * @brief Busy-wait loop that approximates ~100 ns delay using NOPs.
         *
         * The exact delay depends on F_CPU and the value of __numberOfNops
         * (configured in the header). Used to meet the AS5047P inter-frame
         * timing without relying on microsecond-level delays.
         */
        const void AS5047P_SPI::__delay100Ns()
        {
                for (uint16_t i = 0; i < __numberOfNops; i++)
                {
                        __asm__("nop");
                }
        }
#endif

} // namespace AS5047P_ComBackend
