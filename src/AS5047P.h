/**
 * @file AS5047P.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Main header for the AS5047P library.
 *
 *        Declares the high-level sensor API, read/write helpers for volatile
 *        and non-volatile registers, and optional status/debug utilities.
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#ifndef AS5047P_h
#define AS5047P_h

#include <inttypes.h>

#include "./util/AS5047P_Settings.h"

// #ifdef Arduino_h
#include <Arduino.h>
#include "spi/AS5047P_SPI_Arduino.h"
// #endif

#if defined(AS5047P_STD_STRING_SUPPORT)
#include <string>
#endif

#include "types/AS5047P_Types.h"

#define AS5047P_INFO_STRING_BUFFER_SIZE 350 ///< Buffer size for formatted status text.

/**
 * @class AS5047P
 * @brief Main class for interacting with the AS5047P sensor.
 */
class AS5047P
{

public:
    // ======================================================================
    // Constructors
    // ======================================================================

    /**
     * @brief Construct an AS5047P interface.
     * @param chipSelectPinNo Chip Select (CS) pin number. Default: 9.
     * @param spiSpeed        SPI clock speed in Hz. (Default as declared below.)
     */
    AS5047P(uint8_t chipSelectPinNo = 9, uint32_t spiSpeed = 100000);

    // ======================================================================
    // Initialization
    // ======================================================================

    /**
     * @brief Test the SPI connection to the AS5047P.
     * @return true if the connection behaves as expected; false otherwise.
     */
    bool checkSPICon();

    /**
     * @brief Initialize the sensor and verify the connection.
     *        Call this once before using the sensor object.
     * @return true if initialization and connectivity check succeed; false otherwise.
     */
    bool initSPI();

    // ======================================================================
    // Utilities
    // ======================================================================

    /**
     * @brief Check the sensor’s error flags for communication issues and
     *        OR them into @p errorOut.
     * @param errorOut Pointer to an AS5047P_Types::ERROR_t to receive flags (must be non-null).
     * @return true if no communication errors are present; false otherwise.
     */
    bool checkForComErrorF(AS5047P_Types::ERROR_t *errorOut);

    /**
     * @brief Check the sensor’s diagnostics for sensor-related issues and
     *        OR them into @p errorOut.
     * @param errorOut Pointer to an AS5047P_Types::ERROR_t to receive flags (must be non-null).
     * @return true if no sensor errors are present; false otherwise.
     */
    bool checkForSensorErrorF(AS5047P_Types::ERROR_t *errorOut);

    /**
     * @brief Verify that a register contains the expected 16-bit frame (including parity).
     * @param regAddress   Register address to read.
     * @param expectedData Full 16-bit frame expected (bit 15 is the parity bit).
     * @return true if parity is valid and the frame matches; false otherwise.
     */
    bool verifyWrittenRegF(uint16_t regAddress, uint16_t expectedData);

    /**
     * @brief Deprecated alias for verifyWrittenRegF (for backward compatibility).
     * @deprecated Use verifyWrittenRegF instead.
     */
#if defined(__cplusplus) && __cplusplus >= 201402L
    [[deprecated("Use verifyWrittenRegF instead.")]]
#endif
    inline bool verifyWittenRegF(uint16_t regAddress, uint16_t expectedData)
    {
        return verifyWrittenRegF(regAddress, expectedData);
    }
#if defined(AS5047P_STD_STRING_SUPPORT)
    /**
     * @brief Read status/error information and return it as a std::string.
     * @return std::string with formatted status and diagnostic information.
     */
    std::string readStatusAsStdString();
#endif

    /**
     * @brief Read status/error information and return it as an Arduino String.
     * @return String with formatted status and diagnostic information.
     */
    String readStatusAsArduinoString();

    // ======================================================================
    // High-level reads
    // ======================================================================

    /**
     * @brief Read the current CORDIC magnitude.
     * @param errorOut            Optional: error accumulator (nullptr disables checks).
     * @param verifyParity        Verify parity on the read frame (effective when errorOut is set).
     * @param checkForComError    Poll ERRFL for communication errors (effective when errorOut is set).
     * @param checkForSensorError Poll DIAAGC for sensor diagnostics (effective when errorOut is set).
     * @return 14-bit magnitude value.
     */
    uint16_t readMagnitude(AS5047P_Types::ERROR_t *errorOut = nullptr,
                           bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false);

    /**
     * @brief Read the 14-bit raw angle.
     * @param withDAEC            true → ANGLECOM (with DAE compensation), false → ANGLEUNC (raw).
     * @param errorOut            Optional: error accumulator (nullptr disables checks).
     * @param verifyParity        Verify parity on the read frame (effective when errorOut is set).
     * @param checkForComError    Poll ERRFL for communication errors (effective when errorOut is set).
     * @param checkForSensorError Poll DIAAGC for sensor diagnostics (effective when errorOut is set).
     * @return 14-bit angle value.
     */
    uint16_t readAngleRaw(bool withDAEC = true, AS5047P_Types::ERROR_t *errorOut = nullptr,
                          bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false);

    /**
     * @brief Read the angle in degrees.
     * @param withDAEC            true → ANGLECOM (with DAE compensation), false → ANGLEUNC (raw).
     * @param errorOut            Optional: error accumulator (nullptr disables checks).
     * @param verifyParity        Verify parity on the read frame (effective when errorOut is set).
     * @param checkForComError    Poll ERRFL for communication errors (effective when errorOut is set).
     * @param checkForSensorError Poll DIAAGC for sensor diagnostics (effective when errorOut is set).
     * @return Angle in degrees in [0, 360).
     */
    float readAngleDegree(bool withDAEC = true, AS5047P_Types::ERROR_t *errorOut = nullptr,
                          bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false);

    // ======================================================================
    // Template helpers
    // ======================================================================

    /**
     * @brief Read a register of type @tparam T.
     * @tparam T Register wrapper with REG_ADDRESS and a constructor from raw.
     * @param errorOut            Optional: error accumulator (nullptr disables checks).
     * @param verifyParity        Verify parity on the read frame (effective when errorOut is set).
     * @param checkForComError    Poll ERRFL for communication errors (effective when errorOut is set).
     * @param checkForSensorError Poll DIAAGC for sensor diagnostics (effective when errorOut is set).
     * @return The register content decoded as @tparam T.
     */
    template <class T>
    T readReg(AS5047P_Types::ERROR_t *errorOut = nullptr,
              bool verifyParity = false, bool checkForComError = false, bool checkForSensorError = false);

    /**
     * @brief Write a register of type @tparam T.
     * @tparam T Register wrapper with REG_ADDRESS and .data.raw.
     * @param regData            Pointer to the data to write.
     * @param errorOut           Optional: error accumulator (nullptr disables checks).
     * @param checkForComError   Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg    If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    template <class T>
    bool writeReg(const T *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                  bool checkForComError = false, bool verifyWrittenReg = false);

    // ======================================================================
    // Read: volatile registers
    // ======================================================================

    /**
     * @brief Read the ERRFL register.
     * @return Decoded ERRFL register.
     */
    auto read_ERRFL(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                    bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::ERRFL_t;

    /**
     * @brief Read the PROG register.
     * @return Decoded PROG register.
     */
    auto read_PROG(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                   bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::PROG_t;

    /**
     * @brief Read the DIAAGC register.
     * @return Decoded DIAAGC register.
     */
    auto read_DIAAGC(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                     bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::DIAAGC_t;

    /**
     * @brief Read the MAG register.
     * @return Decoded MAG register.
     */
    auto read_MAG(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                  bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::MAG_t;

    /**
     * @brief Read the ANGLEUNC register.
     * @return Decoded ANGLEUNC register.
     */
    auto read_ANGLEUNC(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                       bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::ANGLEUNC_t;

    /**
     * @brief Read the ANGLECOM register.
     * @return Decoded ANGLECOM register.
     */
    auto read_ANGLECOM(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                       bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::ANGLECOM_t;

    // ======================================================================
    // Write: volatile registers
    // ======================================================================

    /**
     * @brief Write to the PROG register.
     * @param regData           New content to write.
     * @param errorOut          Optional: error accumulator (nullptr disables checks).
     * @param checkForComError  Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg   If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    bool write_PROG(const AS5047P_Types::PROG_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                    bool checkForComError = false, bool verifyWrittenReg = false);

    // ======================================================================
    // Read: non-volatile registers
    // ======================================================================

    /**
     * @brief Read the ZPOSM register.
     * @return Decoded ZPOSM register.
     */
    auto read_ZPOSM(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                    bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::ZPOSM_t;

    /**
     * @brief Read the ZPOSL register.
     * @return Decoded ZPOSL register.
     */
    auto read_ZPOSL(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                    bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::ZPOSL_t;

    /**
     * @brief Read the SETTINGS1 register.
     * @return Decoded SETTINGS1 register.
     */
    auto read_SETTINGS1(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                        bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::SETTINGS1_t;

    /**
     * @brief Read the SETTINGS2 register.
     * @return Decoded SETTINGS2 register.
     */
    auto read_SETTINGS2(AS5047P_Types::ERROR_t *errorOut = nullptr, bool verifyParity = false,
                        bool checkForComError = false, bool checkForSensorError = false) -> AS5047P_Types::SETTINGS2_t;

    // ======================================================================
    // Write: non-volatile registers
    // ======================================================================

    /**
     * @brief Write to the ZPOSM register.
     * @param regData           New content to write.
     * @param errorOut          Optional: error accumulator (nullptr disables checks).
     * @param checkForComError  Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg   If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    bool write_ZPOSM(const AS5047P_Types::ZPOSM_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                     bool checkForComError = false, bool verifyWrittenReg = false);

    /**
     * @brief Write to the ZPOSL register.
     * @param regData           New content to write.
     * @param errorOut          Optional: error accumulator (nullptr disables checks).
     * @param checkForComError  Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg   If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    bool write_ZPOSL(const AS5047P_Types::ZPOSL_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                     bool checkForComError = false, bool verifyWrittenReg = false);

    /**
     * @brief Write to the SETTINGS1 register.
     * @param regData           New content to write.
     * @param errorOut          Optional: error accumulator (nullptr disables checks).
     * @param checkForComError  Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg   If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    bool write_SETTINGS1(const AS5047P_Types::SETTINGS1_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                         bool checkForComError = false, bool verifyWrittenReg = false);

    /**
     * @brief Write to the SETTINGS2 register.
     * @param regData           New content to write.
     * @param errorOut          Optional: error accumulator (nullptr disables checks).
     * @param checkForComError  Poll ERRFL for communication errors after write (effective when errorOut is set).
     * @param verifyWrittenReg   If true, perform a diagnostic pass after write (historical flag name kept).
     * @return true if no errors were accumulated (or errorOut is nullptr); false otherwise.
     */
    bool write_SETTINGS2(const AS5047P_Types::SETTINGS2_t *regData, AS5047P_Types::ERROR_t *errorOut = nullptr,
                         bool checkForComError = false, bool verifyWrittenReg = false);

private:
    AS5047P_ComBackend::AS5047P_SPI __spiInterface; ///< SPI backend used for sensor communication.
};

#endif // AS5047P_h
