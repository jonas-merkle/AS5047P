/**
 * @file AS5047P.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This is the main headerfile of the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_h
#define AS5047P_h

// std libraries
#include <inttypes.h>

// as5047p libraries
#include "./util/AS5047P_Settings.h"
#include "./types/AS5047P_Types.h"

// op mode dependent libraries
#if defined(AS5047P_OP_MODE_Arduino)
#include <Arduino.h>
#include "./spi/AS5047P_SPI_Arduino.h"
#endif // AS5047P_OP_MODE_Arduino

#if defined(AS5047P_OP_MODE_Zephyr)
#include "./spi/AS5047P_SPI_Zephyr.h"
#endif // AS5047P_OP_MODE_Zephyr

#if (defined(AS5047P_OP_MODE_Arduino) && (defined(ARDUINO_ARCH_SAMD) || defined(CORE_TEENSY))) || defined(AS5047P_OP_MODE_Zephyr)
#include <string>
#endif // (AS5047P_OP_MODE_Arduino && (ARDUINO_ARCH_SAMD || CORE_TEENSY)) || AS5047P_OP_MODE_Zephyr


// op mode dependent defines
#if (defined(AS5047P_OP_MODE_Arduino) && (defined(ARDUINO_ARCH_SAMD) || defined(CORE_TEENSY))) || defined(AS5047P_OP_MODE_Zephyr)
#define AS5047P_INFO_STRING_BUFFER_SIZE 350     ///< buffer size for information string
#endif // (AS5047P_OP_MODE_Arduino && (ARDUINO_ARCH_SAMD || CORE_TEENSY)) || AS5047P_OP_MODE_Zephyr


/**
 * @class AS5047P
 * @brief The main class for the AS5047P sensor.
 */
class AS5047P {
    
    public:

        // Constructors ------------------------------------------------

        #if defined(AS5047P_OP_MODE_Arduino)
        /**
         * Constructor.
         * @param chipSelectPinNo The pin number of the chip select pin (default: 9);
         * @param spiSpeed The spi bus speed (default: 8000000, on Feather M0 tested up to 32000000)
         */
        explicit AS5047P(uint8_t chipSelectPinNo = 9, uint32_t spiSpeed = 100000);
        #endif // AS5047P_OP_MODE_Arduino

        #if defined(AS5047P_OP_MODE_Zephyr)
        /**
         * Constructor.
         * @param spiDevSpec The zephyr spi devices spec for the AS5047P sensor.
         */
        explicit AS5047P(const struct spi_dt_spec *spiDevSpec);

        #endif // AS5047P_OP_MODE_Zephyr

        // -------------------------------------------------------------

        // Init --------------------------------------------------------

        /**
         * Tests the spi connection to the AS5047P sensor.
         * @return True on success, else false.
         */
        bool checkSPICon() const;

        /**
         * Initializes the sensor object & tests the connection. Must be calles once befor unsing the sensor object.
         * @return True on success, else false.
         */
        bool initSPI();

        // -------------------------------------------------------------

        // Util --------------------------------------------------------

        /**
         * Checks the AS5047P sensors error registers for communication errors and clears this register.
         * @param errorOut A pointer to an AS5047P_types::ERROR_t error object to store the received information.
         * @return True if no errors were found, else false.
         */
        bool checkForComErrorF(AS5047P_Types::ERROR_t *errorOut) const;

        /**
         * Checks the AS5047P sensors error registers for sensor errors.
         * @param errorOut A pointer to an AS5047P_types::ERROR_t error object to store the received information.
         * @return True if no errors were found, else false.
         */
        bool checkForSensorErrorF(AS5047P_Types::ERROR_t *errorOut) const;

        /**
         * Verifies the content of a given register.
         * @param regAddress The address of the register to verify.
         * @param expectedData The expected data in the register (The correct parity bit must be set!).
         * @return True if the register contains the expected data, else false.
         */
        bool verifyWittenRegF(uint16_t regAddress, uint16_t expectedData) const;

        #if (defined(AS5047P_OP_MODE_Arduino) && (defined(ARDUINO_ARCH_SAMD) || defined(CORE_TEENSY))) || defined(AS5047P_OP_MODE_Zephyr)
        /**
         * Reads all status information from the AS5047P sensor and returns them as a string.
         * @return A std::string with all status information.
         */
        std::string readStatusAsStdString() const;
        #endif // (AS5047P_OP_MODE_Arduino && (ARDUINO_ARCH_SAMD || CORE_TEENSY)) || AS5047P_OP_MODE_Zephyr

        #if defined(AS5047P_OP_MODE_Arduino)
        /**
         * Reads all status information from the AS5047P sensor and returns them as a string.
         * @return A string (Arduino String) with all status information.
         */
        String readStatusAsArduinoString() const;
        #endif // AS5047P_OP_MODE_Arduino

        // -------------------------------------------------------------

        // Read High-Level ---------------------------------------------
        
        /**
         * Read the current magnitude value.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The current magnitude value.
         */
        uint16_t readMagnitude(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const;
        
        /**
         * Read the current raw angle value.
         * @param withDAEC Flag to select if the value with or without dynamic angle error correction should be returned.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The current raw angle value.
         */
        uint16_t readAngleRaw(bool withDAEC = true, AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const;

        /**
         * Read the current angle value in degree value.
         * @param withDAEC Flag to select if the value with or without dynamic angle error correction should be returned.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The current angle value in degree value.
         */
        float readAngleDegree(bool withDAEC = true, AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const;

        // -------------------------------------------------------------

        // Template functions ------------------------------------------

        /**
         * Reads a register of type T.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The the register content as type T.
         */
        template<class T>
        T readReg(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const;
        
        /**
         * Writes a register of type T.
         * @param regDate A pointer to the new content of the register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True on success, else false.
         */ 
        template<class T>
        bool writeReg(const T *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        // -------------------------------------------------------------

        // Read Volatile Registers -------------------------------------

        /**
         * Read the ERRFL register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the ERRFL register.
         */
        auto read_ERRFL(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::ERRFL_t;

        /**
         * Read the PROG register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the PROG register.
         */
        auto read_PROG(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::PROG_t;

        /**
         * Read the DIAAGC register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the DIAAGC register.
         */
        auto read_DIAAGC(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::DIAAGC_t;

        /**
         * Read the MAG register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the MAG register.
         */
        auto read_MAG(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::MAG_t;

        /**
         * Read the ANGLEUNC register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the ANGLEUNC register.
         */
        auto read_ANGLEUNC(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::ANGLEUNC_t;

        /**
         * Read the ANGLECOM register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the ANGLECOM register.
         */
        auto read_ANGLECOM(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::ANGLECOM_t;

        // -------------------------------------------------------------

        // Write Volatile Registers ------------------------------------

        /**
         * Write into the PROG register.
         * @param regDat The new content of the PROG register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True if no error occurred, else false.
         */ 
        bool write_PROG(const AS5047P_Types::PROG_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        // -------------------------------------------------------------

        // Read Non-Volatile Registers ---------------------------------

        /**
         * Read the ZPOSM register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the ZPOSM register.
         */
        auto read_ZPOSM(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::ZPOSM_t;

        /**
         * Read the ZPOSL register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the ZPOSL register.
         */
        auto read_ZPOSL(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::ZPOSL_t;

        /**
         * Read the SETTINGS1 register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the SETTINGS1 register.
         */
        auto read_SETTINGS1(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::SETTINGS1_t;

        /**
         * Read the SETTINGS2 register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param verifyParity Flag to activate the parity check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForComError Flag to activate communication error check on read (optional, default: false -> only active when errorOut is set).
         * @param checkForSensorError Flag to activate sensor error check on read (optional, default: false -> only active when errorOut is set).
         * @return The content of the SETTINGS2 register.
         */
        auto read_SETTINGS2(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false) const -> AS5047P_Types::SETTINGS2_t;

        // -------------------------------------------------------------

        // Write Non-Volatile Registers --------------------------------

        /**
         * Write into the ZPOSM register.
         * @param regDat The new content of the ZPOSM register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True if no error occurred, else false.
         */
        bool write_ZPOSM(const AS5047P_Types::ZPOSM_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        /**
         * Write into the ZPOSL register.
         * @param regDat The new content of the ZPOSL register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True if no error occurred, else false.
         */
        bool write_ZPOSL(const AS5047P_Types::ZPOSL_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        /**
         * Write into the SETTINGS1 register.
         * @param regDat The new content of the SETTINGS1 register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True if no error occurred, else false.
         */
        bool write_SETTINGS1(const AS5047P_Types::SETTINGS1_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        /**
         * Write into the SETTINGS2 register.
         * @param regDat The new content of the SETTINGS2 register.
         * @param errorOut A pointer to an error object to get error information back (optional, default: nullptr -> error checks not active).
         * @param checkForComError Flag to activate communication error check on wirte (optional, default: false -> only active when errorOut is set).
         * @param verifyWittenReg Flag to activate the verification of the register content after it's been wirtten (optional, default: false -> only active when errorOut is set).
         * @return True if no error occurred, else false.
         */
        bool write_SETTINGS2(const AS5047P_Types::SETTINGS2_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr, bool checkForComError = false, bool verifyWittenReg = false) const;

        // -------------------------------------------------------------

    private:

        #if defined(AS5047P_OP_MODE_Arduino)
        AS5047P_ComBackend::AS5047P_SPI_Arduino _spiInterface;         ///< The instance of the spi interface for the sensor communication.
        #endif // AS5047P_OP_MODE_Arduino
        #if defined(AS5047P_OP_MODE_Zephyr)
        AS5047P_ComBackend::AS5047P_SPI_Zephyr _spiInterface;          ///< The instance of the spi interface for the sensor communication.
        #endif // AS5047P_OP_MODE_Zephyr
    
};
#endif // AS5047P_h
