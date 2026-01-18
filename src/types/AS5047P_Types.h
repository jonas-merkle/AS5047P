/**
 * @file AS5047P_Types.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Type definitions used by the AS5047P library (errors, SPI frames, register wrappers).
 * @version 2.2.3
 * @date 2025-10-07
 *
 * @copyright
 * Copyright (c) 2024 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#ifndef AS5047P_TYPES_h
#define AS5047P_TYPES_h

#include <inttypes.h>

#include "./util/AS5047P_Settings.h"

#if defined(AS5047P_STD_STRING_SUPPORT)
#include <string>
#endif

#include <Arduino.h>

#define AS5047P_TYPES_WRITE_CMD 0  ///< Write command flag.
#define AS5047P_TYPES_READ_CMD 1   ///< Read command flag.
#define AS5047P_TYPES_ALWAYS_LOW 0 ///< Always-low flag.

#define AS5047P__TYPES_ERROR_STRING_BUFFER_SIZE 600 ///< Buffer size for error string.

/**
 * @namespace AS5047P_Types
 * @brief Namespace for all custom types used with the AS5047P sensor.
 */
namespace AS5047P_Types
{

    // ======================================================================
    // Error types
    // ======================================================================

    /**
     * @enum ERROR_Names
     * @brief Bit positions of error flags and their corresponding names.
     *
     * Note: Sensor-side and controller-side flags live in separate bytes.
     */
    enum ERROR_Names : uint8_t
    {
        // Sensor-side flags
        SENS_SPI_FRAMING_ERROR = 1,
        SENS_SPI_INVALID_CMD = 2,
        SENS_SPI_PARITY_ERROR = 4,
        SENS_OFFSET_COMP_ERROR = 8,
        SENS_CORDIC_OVERFLOW_ERROR = 16,
        SENS_MAG_TOO_HIGH = 32,
        SENS_MAG_TOO_LOW = 64,

        // Controller-side flags
        CONT_SPI_PARITY_ERROR = 1,
        CONT_GENERAL_COM_ERROR = 2,
        CONT_WRITE_VERIFY_FAILED = 4,
    };

    /**
     * @class ERROR_t
     * @brief Container for error information reported by the sensor and host.
     */
    class ERROR_t
    {
    public:
        /**
         * @typedef SensorSideErrors_t
         * @brief Sensor-side error flags and raw byte.
         */
        typedef union
        {
            /**
             * @typedef SensorSideErrorsFlags_t
             * @brief Individual sensor-side error flags.
             */
            typedef struct __attribute__((__packed__))
            {
                uint8_t SENS_SPI_FRAMING_ERROR : 1; ///< Framing error: non-compliant SPI frame detected.
                uint8_t SENS_SPI_INVALID_CMD : 1;   ///< Invalid command: read/write of an invalid register address.
                uint8_t SENS_SPI_PARITY_ERROR : 1;  ///< Parity error on SPI command/data.

                uint8_t SENS_OFFSET_COMP_ERROR : 1;     ///< Diagnostics: offset loop not finished (LF=0) / finished (LF=1).
                uint8_t SENS_CORDIC_OVERFLOW_ERROR : 1; ///< Diagnostics: CORDIC overflow.
                uint8_t SENS_MAG_TOO_HIGH : 1;          ///< Diagnostics: magnetic field strength too high (AGC=0x00).
                uint8_t SENS_MAG_TOO_LOW : 1;           ///< Diagnostics: magnetic field strength too low (AGC=0xFF).
            } SensorSideErrorsFlags_t;

            uint8_t raw = 0;               ///< Raw sensor-side error byte.
            SensorSideErrorsFlags_t flags; ///< Sensor-side error flags.
        } SensorSideErrors_t;

        /**
         * @typedef ControllerSideErrors_t
         * @brief Controller-side error flags and raw byte.
         */
        typedef union
        {
            /**
             * @typedef ControllerSideErrorsFlags_t
             * @brief Individual controller-side error flags.
             */
            typedef struct __attribute__((__packed__))
            {
                uint8_t CONT_SPI_PARITY_ERROR : 1;    ///< Parity error detected by controller.
                uint8_t CONT_GENERAL_COM_ERROR : 1;   ///< General communication error with the sensor.
                uint8_t CONT_WRITE_VERIFY_FAILED : 1; ///< Written register content could not be verified.
            } ControllerSideErrorsFlags_t;

            uint8_t raw = 0;                   ///< Raw controller-side error byte.
            ControllerSideErrorsFlags_t flags; ///< Controller-side error flags.
        } ControllerSideErrors_t;

        SensorSideErrors_t sensorSideErrors;         ///< Sensor-side error data.
        ControllerSideErrors_t controllerSideErrors; ///< Controller-side error data.

        /**
         * @brief Construct an ERROR_t container.
         * @param sensorSideErrorsRaw      Sensor-side error raw byte (default: 0).
         * @param controllerSideErrorsRaw  Controller-side error raw byte (default: 0).
         */
        ERROR_t(uint8_t sensorSideErrorsRaw = 0, uint8_t controllerSideErrorsRaw = 0);

        /**
         * @brief Check if no error is present.
         * @return true if no sensor-side nor controller-side errors are set; false otherwise.
         */
        bool noError();

#if defined(AS5047P_STD_STRING_SUPPORT)
        /**
         * @brief Render a human-readable error report as std::string.
         * @return std::string with all error information.
         */
        std::string toStdString();
#endif

        /**
         * @brief Render a human-readable error report as Arduino String.
         * @return String with all error information.
         */
        String toArduinoString();
    };

    // ======================================================================
    // SPI frame types
    // ======================================================================

    /**
     * @class SPI_Command_Frame_t
     * @brief Representation of an SPI command frame (address + R/W + parity).
     */
    class SPI_Command_Frame_t
    {
    public:
        /**
         * @typedef SPI_Command_Frame_data_t
         * @brief Raw/decoded view of a command frame.
         */
        typedef union
        {
            /**
             * @typedef SPI_Command_Frame_values_t
             * @brief Field view of a command frame.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t ADDR : 14; ///< Register address (14 bits).
                uint16_t RW : 1;    ///< 0: Write, 1: Read.
                uint16_t PARC : 1;  ///< Even parity over the lower 15 bits.
            } SPI_Command_Frame_values_t;

            uint16_t raw = 0;                  ///< Raw 16-bit frame.
            SPI_Command_Frame_values_t values; ///< Decoded fields.
        } SPI_Command_Frame_data_t;

        SPI_Command_Frame_data_t data; ///< Backing storage.

        /**
         * @brief Construct from raw 16-bit frame.
         */
        SPI_Command_Frame_t(uint16_t raw);

        /**
         * @brief Construct from address and R/W.
         * @param ADDR 14-bit register address.
         * @param RW   0: Write, 1: Read.
         */
        SPI_Command_Frame_t(uint16_t ADDR, uint16_t RW);
    };

    /**
     * @class SPI_ReadData_Frame_t
     * @brief Representation of an SPI read-data frame (data + EF + parity).
     */
    class SPI_ReadData_Frame_t
    {
    public:
        /**
         * @typedef SPI_ReadData_Frame_data_t
         * @brief Raw/decoded view of a read-data frame.
         */
        typedef union
        {
            /**
             * @typedef SPI_ReadData_Frame_values_t
             * @brief Field view of a read-data frame.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t DATA : 14; ///< 14-bit data payload.
                uint16_t EF : 1;    ///< Error flag for the *previous* command frame (0: OK, 1: error).
                uint16_t PARD : 1;  ///< Even parity over the lower 15 bits.
            } SPI_ReadData_Frame_values_t;

            uint16_t raw = 0;                   ///< Raw 16-bit frame.
            SPI_ReadData_Frame_values_t values; ///< Decoded fields.
        } SPI_ReadData_Frame_data_t;

        SPI_ReadData_Frame_data_t data; ///< Backing storage.

        /**
         * @brief Construct from raw 16-bit frame.
         */
        SPI_ReadData_Frame_t(uint16_t raw);

        /**
         * @brief Construct from fields.
         * @param DATA 14-bit data payload.
         * @param EF   Error flag for previous command frame (0: OK, 1: error).
         */
        SPI_ReadData_Frame_t(uint16_t DATA, uint16_t EF);
    };

    /**
     * @class SPI_WriteData_Frame_t
     * @brief Representation of an SPI write-data frame (data + NC + parity).
     */
    class SPI_WriteData_Frame_t
    {
    public:
        /**
         * @typedef SPI_WriteData_Frame_data_t
         * @brief Raw/decoded view of a write-data frame.
         */
        typedef union
        {
            /**
             * @typedef SPI_WriteData_Frame_values_t
             * @brief Field view of a write-data frame.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t DATA : 14; ///< 14-bit data payload.
                uint16_t NC : 1;    ///< Not connected / always 0.
                uint16_t PARD : 1;  ///< Even parity over the lower 15 bits.
            } SPI_WriteData_Frame_values_t;

            uint16_t raw = 0;                    ///< Raw 16-bit frame.
            SPI_WriteData_Frame_values_t values; ///< Decoded fields.
        } SPI_WriteData_Frame_data_t;

        SPI_WriteData_Frame_data_t data; ///< Backing storage.

        /**
         * @brief Construct from raw 16-bit frame.
         */
        SPI_WriteData_Frame_t(uint16_t raw);

        /**
         * @brief Construct from fields.
         * @param DATA 14-bit data payload.
         * @param NC   Always 0.
         */
        SPI_WriteData_Frame_t(uint16_t DATA, uint16_t NC);
    };

    // ======================================================================
    // Volatile registers
    // ======================================================================

    /**
     * @class NOP_t
     * @brief No-operation register (used to clock out readback data).
     */
    class NOP_t
    {
    public:
        static const uint16_t REG_ADDRESS = 0x0000; ///< Register address.
    };

    /**
     * @class ERRFL_t
     * @brief Error flags register (framing/invalid-command/parity).
     */
    class ERRFL_t
    {
    public:
        /**
         * @typedef ERRFL_data_t
         * @brief Raw/decoded view of the ERRFL register.
         */
        typedef union
        {
            /**
             * @typedef ERRFL_values_t
             * @brief Field view of the ERRFL register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t FRERR : 1;   ///< Framing error: non-compliant SPI frame detected.
                uint16_t INVCOMM : 1; ///< Invalid command: invalid register address read/written.
                uint16_t PARERR : 1;  ///< Parity error.
            } ERRFL_values_t;

            uint16_t raw = 0;      ///< Raw 16-bit register value.
            ERRFL_values_t values; ///< Decoded fields.
        } ERRFL_data_t;

        static const uint16_t REG_ADDRESS = 0x0001; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        ERRFL_data_t data; ///< Backing storage.

        ERRFL_t();             ///< Default constructor.
        ERRFL_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class PROG_t
     * @brief Programming control register (OTP operations).
     */
    class PROG_t
    {
    public:
        /**
         * @typedef PROG_data_t
         * @brief Raw/decoded view of the PROG register.
         */
        typedef union
        {
            /**
             * @typedef PROG_values_t
             * @brief Field view of the PROG register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t PROGEN : 1;  ///< Enable programming of OTP memory.
                uint16_t :1;
                uint16_t OTPREF : 1;  ///< Refresh non-volatile regs from OTP content.
                uint16_t PROGOTP : 1; ///< Start OTP programming cycle.
                uint16_t :2;
                uint16_t PROGVER : 1; ///< Enable verify phase after programming.
            } PROG_values_t;

            uint16_t raw = 0;     ///< Raw 16-bit register value.
            PROG_values_t values; ///< Decoded fields.
        } PROG_data_t;

        static const uint16_t REG_ADDRESS = 0x0003; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        PROG_data_t data; ///< Backing storage.

        PROG_t();             ///< Default constructor.
        PROG_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class DIAAGC_t
     * @brief Diagnostics and AGC register.
     */
    class DIAAGC_t
    {
    public:
        /**
         * @typedef DIAAGC_data_t
         * @brief Raw/decoded view of the DIAAGC register.
         */
        typedef union
        {
            /**
             * @typedef DIAAGC_values_t
             * @brief Field view of the DIAAGC register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t AGC : 8;  ///< Automatic gain control value.
                uint16_t LF : 1;   ///< Offset loop finished (1) / not finished (0).
                uint16_t COF : 1;  ///< CORDIC overflow.
                uint16_t MAGH : 1; ///< Magnetic field strength too high (AGC=0x00).
                uint16_t MAGL : 1; ///< Magnetic field strength too low (AGC=0xFF).
            } DIAAGC_values_t;

            uint16_t raw = 0;       ///< Raw 16-bit register value.
            DIAAGC_values_t values; ///< Decoded fields.
        } DIAAGC_data_t;

        static const uint16_t REG_ADDRESS = 0x3FFC; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0180; ///< Register default.

        DIAAGC_data_t data; ///< Backing storage.

        DIAAGC_t();             ///< Default constructor.
        DIAAGC_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class MAG_t
     * @brief CORDIC magnitude register.
     */
    class MAG_t
    {
    public:
        /**
         * @typedef MAG_data_t
         * @brief Raw/decoded view of the MAG register.
         */
        typedef union
        {
            /**
             * @typedef MAG_values_t
             * @brief Field view of the MAG register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t CMAG : 14; ///< CORDIC magnitude information.
            } MAG_values_t;

            uint16_t raw = 0;    ///< Raw 16-bit register value.
            MAG_values_t values; ///< Decoded fields.
        } MAG_data_t;

        static const uint16_t REG_ADDRESS = 0x3FFD; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        MAG_data_t data; ///< Backing storage.

        MAG_t();             ///< Default constructor.
        MAG_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class ANGLEUNC_t
     * @brief Measured angle without dynamic angle error compensation.
     */
    class ANGLEUNC_t
    {
    public:
        /**
         * @typedef ANGLEUNC_data_t
         * @brief Raw/decoded view of the ANGLEUNC register.
         */
        typedef union
        {
            /**
             * @typedef ANGLEUNC_values_t
             * @brief Field view of the ANGLEUNC register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t CORDICANG : 14; ///< Angle without DAE compensation.
            } ANGLEUNC_values_t;

            uint16_t raw = 0;         ///< Raw 16-bit register value.
            ANGLEUNC_values_t values; ///< Decoded fields.
        } ANGLEUNC_data_t;

        static const uint16_t REG_ADDRESS = 0x3FFE; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        ANGLEUNC_data_t data; ///< Backing storage.

        ANGLEUNC_t();             ///< Default constructor.
        ANGLEUNC_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class ANGLECOM_t
     * @brief Measured angle with dynamic angle error compensation.
     */
    class ANGLECOM_t
    {
    public:
        /**
         * @typedef ANGLECOM_data_t
         * @brief Raw/decoded view of the ANGLECOM register.
         */
        typedef union
        {
            /**
             * @typedef ANGLECOM_values_t
             * @brief Field view of the ANGLECOM register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t DAECANG : 14; ///< Angle with DAE compensation.
            } ANGLECOM_values_t;

            uint16_t raw = 0;         ///< Raw 16-bit register value.
            ANGLECOM_values_t values; ///< Decoded fields.
        } ANGLECOM_data_t;

        static const uint16_t REG_ADDRESS = 0x3FFF; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        ANGLECOM_data_t data; ///< Backing storage.

        ANGLECOM_t();             ///< Default constructor.
        ANGLECOM_t(uint16_t raw); ///< Construct from raw value.
    };

    // ======================================================================
    // Non-volatile registers
    // ======================================================================

    /**
     * @class ZPOSM_t
     * @brief Zero position MSB register.
     */
    class ZPOSM_t
    {
    public:
        /**
         * @typedef ZPOSM_data_t
         * @brief Raw/decoded view of the ZPOSM register.
         */
        typedef union
        {
            /**
             * @typedef ZPOSM_values_t
             * @brief Field view of the ZPOSM register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t ZPOSM : 8; ///< 8 most significant bits of zero position.
            } ZPOSM_values_t;

            uint16_t raw = 0;      ///< Raw 16-bit register value.
            ZPOSM_values_t values; ///< Decoded fields.
        } ZPOSM_data_t;

        static const uint16_t REG_ADDRESS = 0x0016; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        ZPOSM_data_t data; ///< Backing storage.

        ZPOSM_t();             ///< Default constructor.
        ZPOSM_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class ZPOSL_t
     * @brief Zero position LSB / MAG diagnostic control register.
     */
    class ZPOSL_t
    {
    public:
        /**
         * @typedef ZPOSL_data_t
         * @brief Raw/decoded view of the ZPOSL register.
         */
        typedef union
        {
            /**
             * @typedef ZPOSL_values_t
             * @brief Field view of the ZPOSL register.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t ZPOSL : 6;           ///< 6 least significant bits of zero position.
                uint16_t comp_l_error_en : 1; ///< Enable MAGL (too low) to contribute to ERRFL.
                uint16_t comp_h_error_en : 1; ///< Enable MAGH (too high) to contribute to ERRFL.
            } ZPOSL_values_t;

            uint16_t raw = 0;      ///< Raw 16-bit register value.
            ZPOSL_values_t values; ///< Decoded fields.
        } ZPOSL_data_t;

        static const uint16_t REG_ADDRESS = 0x0017; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        ZPOSL_data_t data; ///< Backing storage.

        ZPOSL_t();             ///< Default constructor.
        ZPOSL_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class SETTINGS1_t
     * @brief Custom setting register 1.
     */
    class SETTINGS1_t
    {
    public:
        /**
         * @typedef SETTINGS1_data_t
         * @brief Raw/decoded view of SETTINGS1.
         */
        typedef union
        {
            /**
             * @typedef SETTINGS1_values_t
             * @brief Field view of SETTINGS1.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t FactorySetting : 1; ///< Pre-programmed to 1.
                uint16_t NOISESET : 1;       ///< Noise settings.
                uint16_t DIR : 1;            ///< Rotation direction.
                uint16_t UVW_ABI : 1;        ///< PWM function selection with UVW/ABI.
                uint16_t DAECDIS : 1;        ///< Disable DAE compensation (0=ON, 1=OFF).
                uint16_t ABIBIN : 1;         ///< ABI pulses per revolution decimal/binary.
                uint16_t Dataselect : 1;     ///< 0->DAECANG, 1->CORDICANG returned at 0x3FFF.
                uint16_t PWMon : 1;          ///< Enable PWM (requires UVW_ABI setting).
            } SETTINGS1_values_t;

            uint16_t raw = 0;          ///< Raw 16-bit register value.
            SETTINGS1_values_t values; ///< Decoded fields.
        } SETTINGS1_data_t;

        static const uint16_t REG_ADDRESS = 0x0018; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0001; ///< Register default.

        SETTINGS1_data_t data; ///< Backing storage.

        SETTINGS1_t();             ///< Default constructor.
        SETTINGS1_t(uint16_t raw); ///< Construct from raw value.
    };

    /**
     * @class SETTINGS2_t
     * @brief Custom setting register 2.
     */
    class SETTINGS2_t
    {
    public:
        /**
         * @typedef SETTINGS2_data_t
         * @brief Raw/decoded view of SETTINGS2.
         */
        typedef union
        {
            /**
             * @typedef SETTINGS2_values_t
             * @brief Field view of SETTINGS2.
             */
            typedef struct __attribute__((__packed__))
            {
                uint16_t UVWPP : 3;  ///< UVW number of pole pairs (encoded 0..7 → 1..8).
                uint16_t HYS : 2;    ///< Hysteresis setting.
                uint16_t ABIRES : 3; ///< ABI resolution setting.
            } SETTINGS2_values_t;

            uint16_t raw = 0;          ///< Raw 16-bit register value.
            SETTINGS2_values_t values; ///< Decoded fields.
        } SETTINGS2_data_t;

        static const uint16_t REG_ADDRESS = 0x0019; ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000; ///< Register default.

        SETTINGS2_data_t data; ///< Backing storage.

        SETTINGS2_t();             ///< Default constructor.
        SETTINGS2_t(uint16_t raw); ///< Construct from raw value.
    };

} // namespace AS5047P_Types

#endif // AS5047P_TYPES_h
