/**
 * @file AS5047P.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Main implementation file for the AS5047P library.
 *
 *        Provides high-level read/write helpers, error aggregation utilities,
 *        and user-facing convenience functions for angle and magnitude reads.
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#include "AS5047P.h"
#include "util/AS5047P_Util.h"

// ======================================================================
// Constructors
// ======================================================================

AS5047P::AS5047P(const uint8_t chipSelectPinNo, const uint32_t spiSpeed)
    : __spiInterface(chipSelectPinNo, spiSpeed)
{
}

// ======================================================================
// Init
// ======================================================================

/**
 * @brief Check that SPI communication works as expected.
 *
 * Performs a series of reads and a write to verify basic SPI functionality,
 *
 * @return true if the check passes and parity error is detected, false otherwise.
 */
bool AS5047P::checkSPICon()
{
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
    Serial.println(F("=== AS5047P SPI Connection Test (compact + safe restore) ==="));
#endif

    AS5047P_Types::ERROR_t err;

    // 1) ERRFL: quick comm/parity check
    auto errfl = AS5047P::read_ERRFL(&err, true, true, true);
    if (err.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] Parity error on ERRFL read."));
#endif
        return false;
    }
    if (errfl.data.raw)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.print(F("[FAIL] ERRFL nonzero: 0b"));
        Serial.println(errfl.data.raw, BIN);
#endif
        return false;
    }

    // 2) ANGLEUNC: basic data sanity + parity
    auto angle = AS5047P::read_ANGLEUNC(&err, true, true, false);
    if (err.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] Parity error on ANGLEUNC read."));
#endif
        return false;
    }
    uint16_t ang = angle.data.values.CORDICANG;
    if (ang > 0x3FFF)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] ANGLE out of range (>16383)."));
#endif
        return false;
    }

    // 3) Soft write test on SETTINGS2 (mask writable bits only: 0..7)
    constexpr uint16_t S2_WRITABLE_MASK = 0x00FF;

    AS5047P_Types::ERROR_t e_before{};
    auto s2_before = AS5047P::read_SETTINGS2(&e_before, true, true, false);
    if (e_before.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] Parity error on SETTINGS2 read (before)."));
#endif
        return false;
    }

    // Prepare modified value (harmless flip of HYS LSB)
    AS5047P_Types::SETTINGS2_t s2_w = s2_before;
    s2_w.data.values.HYS ^= 0x1;

    // Track if we changed the setting so we can always restore it later
    bool s2_changed = false;

    // Helper to restore original SETTINGS2 before returning on failure/success
    auto restore_s2 = [&](const __FlashStringHelper *ctx_label)
    {
        if (!s2_changed)
            return true; // nothing to restore
        AS5047P_Types::ERROR_t e_restore{};
        bool ok = AS5047P::write_SETTINGS2(&s2_before, &e_restore, true, false);
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        if (!ok || e_restore.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
        {
            Serial.print(F("[WARN] Restore SETTINGS2 failed during "));
            Serial.print(ctx_label);
            Serial.println(F("."));
        }
#endif
        return ok && !e_restore.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR;
    };

    // 3a) Write modified SETTINGS2
    AS5047P_Types::ERROR_t e_wr{};
    if (!AS5047P::write_SETTINGS2(&s2_w, &e_wr, /*checkForComError=*/true, /*verifyWrittenReg=*/false) || e_wr.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] SETTINGS2 write failed or parity error."));
#endif
        // nothing changed on chip if write failed, so just return
        return false;
    }
    s2_changed = true;

    // 3b) Read back and verify ONLY writable bits
    AS5047P_Types::ERROR_t e_after{};
    auto s2_after = AS5047P::read_SETTINGS2(&e_after, true, true, false);
    if (e_after.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
        restore_s2(F("post-write read"));
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] Parity error on SETTINGS2 read (after)."));
#endif
        return false;
    }

    const uint16_t wrote_m = s2_w.data.raw & S2_WRITABLE_MASK;
    const uint16_t read_m = s2_after.data.raw & S2_WRITABLE_MASK;
    if (read_m != wrote_m)
    {
        restore_s2(F("verification"));
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.print(F("[FAIL] SETTINGS2 mismatch (masked). wrote=0x"));
        Serial.print(wrote_m, HEX);
        Serial.print(F(" read=0x"));
        Serial.println(read_m, HEX);
#endif
        return false;
    }

    // 3c) Restore original SETTINGS2 and (optionally) verify
    if (!restore_s2(F("restore")))
    {
#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
        Serial.println(F("[FAIL] SETTINGS2 restore failed."));
#endif
        return false;
    }

#ifdef AS5047P_DEBUG_OUTPUT_ENABLE
    // Optional masked verify of the restore (cheap and safe)
    AS5047P_Types::ERROR_t e_verify{};
    auto s2_restored = AS5047P::read_SETTINGS2(&e_verify, true, true, false);
    if (!e_verify.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
        uint16_t before_m = s2_before.data.raw & S2_WRITABLE_MASK;
        uint16_t now_m = s2_restored.data.raw & S2_WRITABLE_MASK;
        if (before_m != now_m)
        {
            Serial.print(F("[FAIL] SETTINGS2 did not restore on writable bits. got=0x"));
            Serial.print(now_m, HEX);
            Serial.print(F(" expected=0x"));
            Serial.println(before_m, HEX);
            return false;
        }
    }
    else
    {
        Serial.println(F("[FAIL] Parity error while verifying SETTINGS2 restore."));
        return false;
    }

    Serial.println(F("[PASS] SPI OK (ERRFL, ANGLE, SETTINGS2 masked write + guaranteed restore)."));
#endif

    return true;
}

/**
 * @brief Initialize the SPI backend and verify connectivity.
 * @return true if initialization and connectivity check succeed; false otherwise.
 */
bool AS5047P::initSPI()
{
    __spiInterface.init();
    return checkSPICon();
}

// ======================================================================
// Utilities (error collection & verification helpers)
// ======================================================================

/**
 * @brief Check for communication-related errors and OR them into @p errorOut.
 *
 * Reads ERRFL and updates:
 *  - controller-side parity error (from the current transaction),
 *  - sensor-side FRERR / INVCOMM / PARERR bits (OR-assigned).
 *
 * @param errorOut Output accumulator for error flags (must be non-null).
 * @return true if no errors are present after the check; false otherwise.
 */
bool AS5047P::checkForComErrorF(AS5047P_Types::ERROR_t *errorOut)
{
    // Read the error register and collect controller-side parity status.
    AS5047P_Types::ERROR_t e;
    auto errorReg = AS5047P::read_ERRFL(&e, true, false, false);

    // Propagate controller-side parity error from the last read.
    errorOut->controllerSideErrors.flags.CONT_SPI_PARITY_ERROR =
        e.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR;

    // OR-accumulate sensor-side error bits.
    errorOut->sensorSideErrors.flags.SENS_SPI_FRAMING_ERROR |= errorReg.data.values.FRERR;
    errorOut->sensorSideErrors.flags.SENS_SPI_INVALID_CMD |= errorReg.data.values.INVCOMM;
    errorOut->sensorSideErrors.flags.SENS_SPI_PARITY_ERROR |= errorReg.data.values.PARERR;

    // Return true when no errors are present.
    if (!errorReg.data.values.FRERR &&
        !errorReg.data.values.INVCOMM &&
        !errorReg.data.values.PARERR &&
        !errorOut->controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Check sensor diagnostics and OR them into @p errorOut.
 *
 * Reads DIAAGC and updates:
 *  - controller-side parity error (from the current transaction),
 *  - sensor-side COF / LF (inverted for error) / MAGH / MAGL bits (OR-assigned).
 *
 * Note on LF: LF==1 indicates the internal offset loop is finished (OK),
 * LF==0 indicates "not finished" (treated as an error). We therefore OR in `!LF`.
 *
 * @param errorOut Output accumulator for error flags (must be non-null).
 * @return true if no sensor-related errors are present; false otherwise.
 */
bool AS5047P::checkForSensorErrorF(AS5047P_Types::ERROR_t *errorOut)
{
    // Read the diagnostics register and collect controller-side parity status.
    AS5047P_Types::ERROR_t e;
    auto diagReg = AS5047P::read_DIAAGC(&e, true, false, false);

    // Propagate controller-side parity error from the last read.
    errorOut->controllerSideErrors.flags.CONT_SPI_PARITY_ERROR =
        e.controllerSideErrors.flags.CONT_SPI_PARITY_ERROR;

    // OR-accumulate sensor-side diagnostic bits.
    errorOut->sensorSideErrors.flags.SENS_CORDIC_OVERFLOW_ERROR |= diagReg.data.values.COF;
    errorOut->sensorSideErrors.flags.SENS_OFFSET_COMP_ERROR |= !diagReg.data.values.LF; // LF==0 → error
    errorOut->sensorSideErrors.flags.SENS_MAG_TOO_HIGH |= diagReg.data.values.MAGH;
    errorOut->sensorSideErrors.flags.SENS_MAG_TOO_LOW |= diagReg.data.values.MAGL;

    // Return true when no sensor errors are present.
    // (LF==1 is the OK state, so we require diagReg.LF==1 here.)
    if (!diagReg.data.values.COF &&
        diagReg.data.values.LF &&
        !diagReg.data.values.MAGH &&
        !diagReg.data.values.MAGL &&
        !errorOut->controllerSideErrors.flags.CONT_SPI_PARITY_ERROR)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Verify that a register contains the expected raw 16-bit word.
 *
 * Performs a read of the 16-bit frame (including parity) and compares it
 * against @p expectedData. Both parity and content must match.
 *
 * @param regAddress   Register address to verify.
 * @param expectedData Expected 16-bit word (including parity bit).
 * @return true if parity is valid and the frame matches; false otherwise.
 */
bool AS5047P::verifyWrittenRegF(uint16_t regAddress, uint16_t expectedData)
{
    // Check parity of the expected frame (bit 15 is parity).
    if (!AS5047P_Util::parityCheck(expectedData))
    {
        return false;
    }

    // Read register content (16-bit frame, includes parity).
    AS5047P_Types::SPI_ReadData_Frame_t recData(__spiInterface.read(regAddress));

    // Validate parity of the received frame.
    if (!AS5047P_Util::parityCheck(recData.data.raw))
    {
        return false;
    }

    // Match full 16-bit frame (including parity).
    return recData.data.raw == expectedData;
}

#if defined(AS5047P_STD_STRING_SUPPORT)
/**
 * @brief Render a human-readable status dump (std::string).
 */
std::string AS5047P::readStatusAsStdString()
{
    AS5047P_Types::ERRFL_t errorReg = read_ERRFL();
    AS5047P_Types::DIAAGC_t diagReg = read_DIAAGC();

    std::string str;
    str.reserve(AS5047P_INFO_STRING_BUFFER_SIZE);

    str.append("#########################\n");
    str.append(" Error Information:\n");
    str.append("-------------------------\n");
    str.append("- Framing error:   ");
    str.append(AS5047P_Util::to_string(errorReg.data.values.FRERR));
    str.append("\n");
    str.append("- Invalid command: ");
    str.append(AS5047P_Util::to_string(errorReg.data.values.INVCOMM));
    str.append("\n");
    str.append("- Parity error:    ");
    str.append(AS5047P_Util::to_string(errorReg.data.values.PARERR));
    str.append("\n");
    str.append("#########################\n");
    str.append(" Diagnostic Information:\n");
    str.append("-------------------------\n");
    str.append("- AGC Value:       ");
    str.append(AS5047P_Util::to_string(diagReg.data.values.AGC));
    str.append("\n");
    str.append("- Offset comp.:    ");
    str.append(AS5047P_Util::to_string(diagReg.data.values.LF)); // 1 = finished (OK), 0 = not finished
    str.append("\n");
    str.append("- CORDIC overflow: ");
    str.append(AS5047P_Util::to_string(diagReg.data.values.COF));
    str.append("\n");
    str.append("- MAG too high:    ");
    str.append(AS5047P_Util::to_string(diagReg.data.values.MAGH));
    str.append("\n");
    str.append("- MAG too low:     ");
    str.append(AS5047P_Util::to_string(diagReg.data.values.MAGL));
    str.append("\n");
    str.append("#########################\n");

    str.shrink_to_fit();
    return str;
}
#endif

/**
 * @brief Render a human-readable status dump (Arduino String).
 */
String AS5047P::readStatusAsArduinoString()
{
    AS5047P_Types::ERRFL_t errorReg = read_ERRFL();
    AS5047P_Types::DIAAGC_t diagReg = read_DIAAGC();

    char buf[AS5047P_INFO_STRING_BUFFER_SIZE] = {0};

    sprintf(buf,
            "#########################\n"
            " Error Information:\n"
            "-------------------------\n"
            "- Framing error:   %d\n"
            "- Invalid command: %d\n"
            "- Parity error:    %d\n"
            "#########################\n"
            " Diagnostic Information:\n"
            "-------------------------\n"
            "- AGC Value:       %d\n"
            "- Offset comp.:    %d\n"
            "- CORDIC overflow: %d\n"
            "- MAG too high:    %d\n"
            "- MAG too low:     %d\n"
            "#########################\n",
            errorReg.data.values.FRERR, errorReg.data.values.INVCOMM, errorReg.data.values.PARERR,
            diagReg.data.values.AGC, diagReg.data.values.LF, diagReg.data.values.COF,
            diagReg.data.values.MAGH, diagReg.data.values.MAGL);

    return String(buf);
}

// ======================================================================
// High-level reads
// ======================================================================

/**
 * @brief Read CORDIC magnitude (CMAG).
 * @return 14-bit magnitude value.
 */
uint16_t AS5047P::readMagnitude(AS5047P_Types::ERROR_t *errorOut,
                                bool verifyParity, bool checkForComError, bool checkForSensorError)
{
    AS5047P_Types::MAG_t res = AS5047P::read_MAG(errorOut, verifyParity, checkForComError, checkForSensorError);
    return res.data.values.CMAG;
}

/**
 * @brief Read raw angle (14-bit), optionally with DAE compensation.
 * @param withDAEC true to read ANGLECOM (DAECANG), false to read ANGLEUNC (CORDICANG).
 */
uint16_t AS5047P::readAngleRaw(bool withDAEC, AS5047P_Types::ERROR_t *errorOut,
                               bool verifyParity, bool checkForComError, bool checkForSensorError)
{
    if (withDAEC)
    {
        AS5047P_Types::ANGLECOM_t res = AS5047P::read_ANGLECOM(errorOut, verifyParity, checkForComError, checkForSensorError);
        return res.data.values.DAECANG;
    }
    else
    {
        AS5047P_Types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC(errorOut, verifyParity, checkForComError, checkForSensorError);
        return res.data.values.CORDICANG;
    }
}

/**
 * @brief Read angle in degrees, optionally with DAE compensation.
 * @param withDAEC true → ANGLECOM (DAEC), false → ANGLEUNC (raw).
 * @return Angle in degrees in [0, 360).
 */
float AS5047P::readAngleDegree(bool withDAEC, AS5047P_Types::ERROR_t *errorOut,
                               bool verifyParity, bool checkForComError, bool checkForSensorError)
{
    if (withDAEC)
    {
        AS5047P_Types::ANGLECOM_t res = AS5047P::read_ANGLECOM(errorOut, verifyParity, checkForComError, checkForSensorError);
        return (res.data.values.DAECANG / (float)16384) * 360;
    }
    else
    {
        AS5047P_Types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC(errorOut, verifyParity, checkForComError, checkForSensorError);
        return (res.data.values.CORDICANG / (float)16384) * 360;
    }
}

// ======================================================================
// Template helpers (read/write core)
// ======================================================================

/**
 * @brief Read a register type @tparam T and optionally perform parity/diagnostic checks.
 *
 * @tparam T Register wrapper type with REG_ADDRESS and a constructor from raw.
 * @param errorOut          Optional error accumulator (nullptr to skip).
 * @param verifyParity      Verify parity on the readback frame.
 * @param checkForComError  Poll ERRFL to OR-in comms errors.
 * @param checkForSensorError Poll DIAAGC to OR-in sensor diagnostics.
 * @return T                Decoded register wrapper.
 */
template <class T>
T AS5047P::readReg(AS5047P_Types::ERROR_t *errorOut,
                   bool verifyParity, bool checkForComError, bool checkForSensorError)
{
    // Issue read command and fetch data frame.
    AS5047P_Types::SPI_ReadData_Frame_t recData(__spiInterface.read(T::REG_ADDRESS));

    if (errorOut == nullptr)
    {
        return T(recData.data.raw);
    }

    // Reset error output for this transaction.
    *errorOut = AS5047P_Types::ERROR_t();

    // Verify parity if requested.
    if (verifyParity)
    {
        errorOut->controllerSideErrors.flags.CONT_SPI_PARITY_ERROR =
            !AS5047P_Util::parityCheck(recData.data.raw);
    }

    // Aggregate communication errors if requested.
    if (checkForComError)
    {
        checkForComErrorF(errorOut);
    }

    // Aggregate sensor diagnostics if requested.
    if (checkForSensorError)
    {
        checkForSensorErrorF(errorOut);

        // Optionally poll comms again, since reading DIAAGC is another transaction.
        if (checkForComError)
        {
            checkForComErrorF(errorOut);
        }
    }

    return T(recData.data.raw);
}

/**
 * @brief Write a register and optionally poll for errors / verify.
 *
 * @tparam T Register wrapper type with REG_ADDRESS.
 * @param regData           Data to write (16-bit raw in regData->data.raw).
 * @param errorOut          Optional error accumulator (nullptr to skip).
 * @param checkForComError  Poll ERRFL to OR-in comms errors after write.
 * @param verifyWrittenReg   If true, also polls sensor diagnostics (historical naming kept).
 * @return true if @p errorOut shows no errors (or @p errorOut is nullptr); false otherwise.
 */
template <class T>
bool AS5047P::writeReg(const T *regData, AS5047P_Types::ERROR_t *errorOut,
                       bool checkForComError, bool verifyWrittenReg)
{
    // Perform write (frame assembly handled by lower layer).
    __spiInterface.write(T::REG_ADDRESS, regData->data.raw);

    if (errorOut == nullptr)
    {
        return true;
    }

    // Reset error output for this transaction.
    *errorOut = AS5047P_Types::ERROR_t();

    // Aggregate communication errors if requested.
    if (checkForComError)
    {
        checkForComErrorF(errorOut);
    }

    // Optionally run a sensor diagnostic pass (historical flag name preserved).
    if (verifyWrittenReg)
    {
        checkForSensorErrorF(errorOut);

        // Optionally poll comms again, since reading DIAAGC is another transaction.
        if (checkForComError)
        {
            checkForComErrorF(errorOut);
        }
    }

    // Success iff no errors were accumulated.
    return errorOut->noError();
}

// ======================================================================
// Read: volatile registers
// ======================================================================

auto AS5047P::read_ERRFL(AS5047P_Types::ERROR_t *errorOut,
                         bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::ERRFL_t
{
    return readReg<AS5047P_Types::ERRFL_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_PROG(AS5047P_Types::ERROR_t *errorOut,
                        bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::PROG_t
{
    return readReg<AS5047P_Types::PROG_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_DIAAGC(AS5047P_Types::ERROR_t *errorOut,
                          bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::DIAAGC_t
{
    return readReg<AS5047P_Types::DIAAGC_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_MAG(AS5047P_Types::ERROR_t *errorOut,
                       bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::MAG_t
{
    return readReg<AS5047P_Types::MAG_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_ANGLEUNC(AS5047P_Types::ERROR_t *errorOut,
                            bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::ANGLEUNC_t
{
    return readReg<AS5047P_Types::ANGLEUNC_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_ANGLECOM(AS5047P_Types::ERROR_t *errorOut,
                            bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::ANGLECOM_t
{
    return readReg<AS5047P_Types::ANGLECOM_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

// ======================================================================
// Write: volatile registers
// ======================================================================

bool AS5047P::write_PROG(const AS5047P_Types::PROG_t *regData,
                         AS5047P_Types::ERROR_t *errorOut, bool checkForComError, bool verifyWrittenReg)
{
    return writeReg<AS5047P_Types::PROG_t>(regData, errorOut, checkForComError, verifyWrittenReg);
}

// ======================================================================
// Read: non-volatile registers
// ======================================================================

auto AS5047P::read_ZPOSM(AS5047P_Types::ERROR_t *errorOut,
                         bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::ZPOSM_t
{
    return readReg<AS5047P_Types::ZPOSM_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_ZPOSL(AS5047P_Types::ERROR_t *errorOut,
                         bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::ZPOSL_t
{
    return readReg<AS5047P_Types::ZPOSL_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_SETTINGS1(AS5047P_Types::ERROR_t *errorOut,
                             bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::SETTINGS1_t
{
    return readReg<AS5047P_Types::SETTINGS1_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

auto AS5047P::read_SETTINGS2(AS5047P_Types::ERROR_t *errorOut,
                             bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_Types::SETTINGS2_t
{
    return readReg<AS5047P_Types::SETTINGS2_t>(errorOut, verifyParity, checkForComError, checkForSensorError);
}

// ======================================================================
// Write: non-volatile registers
// ======================================================================

bool AS5047P::write_ZPOSM(const AS5047P_Types::ZPOSM_t *regData,
                          AS5047P_Types::ERROR_t *errorOut, bool checkForComError, bool verifyWrittenReg)
{
    return writeReg<AS5047P_Types::ZPOSM_t>(regData, errorOut, checkForComError, verifyWrittenReg);
}

bool AS5047P::write_ZPOSL(const AS5047P_Types::ZPOSL_t *regData,
                          AS5047P_Types::ERROR_t *errorOut, bool checkForComError, bool verifyWrittenReg)
{
    return writeReg<AS5047P_Types::ZPOSL_t>(regData, errorOut, checkForComError, verifyWrittenReg);
}

bool AS5047P::write_SETTINGS1(const AS5047P_Types::SETTINGS1_t *regData,
                              AS5047P_Types::ERROR_t *errorOut, bool checkForComError, bool verifyWrittenReg)
{
    return writeReg<AS5047P_Types::SETTINGS1_t>(regData, errorOut, checkForComError, verifyWrittenReg);
}

bool AS5047P::write_SETTINGS2(const AS5047P_Types::SETTINGS2_t *regData,
                              AS5047P_Types::ERROR_t *errorOut, bool checkForComError, bool verifyWrittenReg)
{
    return writeReg<AS5047P_Types::SETTINGS2_t>(regData, errorOut, checkForComError, verifyWrittenReg);
}
