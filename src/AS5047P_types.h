#ifndef AS5047P_types_h
#define AS5047P_types_h

#include <inttypes.h>

namespace AS5047P_types {

    // Volatile Registers ------------------------------------------

    /**
     * @class ERRFL_t
     * @brief Provides a representation of the error register of the AS5047P.
     */
    class ERRFL_t {

    public:

        /**
         * @typedef ERRFL_values_t
         * @brief Provides a new datatype for the content of the ERRFL register.
         */
        typedef struct __attribute__ ((__packed__)) {

            uint16_t FRERR:1;       ///< Framing error: is set to 1 when a non-compliant SPI frame is detected.
            uint16_t INVCOMM:1;     ///< Invalid command error: set to 1 by reading or writing an invalid register address.
            uint16_t PARERR:1;      ///< Parity error.

        } ERRFL_values_t;

        static const uint16_t REG_ADDRESS = 0x0001;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.

        ERRFL_values_t values{};      ///< Register values.

        /**
         * Default constructor.
         */
        ERRFL_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> ERRFL_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(ERRFL_values_t values) -> uint16_t;

    };

    /**
     * @class PROG_t
     * @brief Provides a representation of the programming register register of the AS5047P.
     */
    class PROG_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t PROGEN:1;      ///< Program OTP enable: enables programming the entire OTP memory.
            uint16_t OTPREF:1;      ///< Refreshes the non-volatile memory content with the OTP programmed content.
            uint16_t PROGOTP:1;     ///< Start OTP programming cycle.
            uint16_t PROGVER:1;     ///< Program verify: must be set to 1 for verifying the correctness of the OTP programming.

        } PROG_values_t;

        static const uint16_t REG_ADDRESS = 0x0003;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.

        PROG_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        PROG_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> PROG_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(PROG_values_t values) -> uint16_t;

    };

    /**
     * @class DIAAGC_t
     * @brief Provides a representation of the diagnostic and AGC register of the AS5047P.
     */
    class DIAAGC_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t AGC:8;     ///< Automatic gain control value.
            uint16_t LF:1;      ///< Diagnostics: Offset compensation LF=0:internal offset loops not ready regulated LF=1:internal offset loop finished.
            uint16_t COF:1;     ///< Diagnostics: CORDIC overflow.
            uint16_t MAGH:1;    ///< Diagnostics: Magnetic field strength too high; AGC=0x00.
            uint16_t MAGL:1;    ///< Diagnostics: Magnetic field strength too low; AGC=0xFF.

        } DIAAGC_values_t;

        static const uint16_t REG_ADDRESS = 0x3FFC;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0180;     ///< Register default values.

        DIAAGC_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        DIAAGC_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> DIAAGC_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(DIAAGC_values_t values) -> uint16_t;

    };

    /**
     * @class MAG_t
     * @brief Provides a representation of the CORDIC magnitude register of the AS5047P.
     */
    class MAG_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t CMAG:14;       ///< CORDIC magnitude information.

        } MAG_values_t;

        static const uint16_t REG_ADDRESS = 0x3FFD;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.

        MAG_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        MAG_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> MAG_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(MAG_values_t values) -> uint16_t;

    };

    /**
     * @class ANGLEUNC_t
     * @brief Provides a representation of the measured angle without dynamic angle error compensation register of the AS5047P.
     */
    class ANGLEUNC_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t CORDICANG:14;      ///< Angle information without dynamic angle error compensation.

        } ANGLEUNC_values_t;

        static const uint16_t REG_ADDRESS = 0x3FFE;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.

        ANGLEUNC_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        ANGLEUNC_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> ANGLEUNC_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(ANGLEUNC_values_t values) -> uint16_t;

    };

    /**
     * @class ANGLECOM_t
     * @brief Provides a representation of the measured angle with dynamic angle error compensation register of the AS5047P.
     */
    class ANGLECOM_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t DAECANG:14;        ///< Angle information with dynamic angle error compensation.

        } ANGLECOM_values_t;

        static const uint16_t REG_ADDRESS = 0x3FFF;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.

        ANGLECOM_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        ANGLECOM_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> ANGLECOM_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(ANGLECOM_values_t values) -> uint16_t;

    };

    // -------------------------------------------------------------

    // Non-Volatile Registers --------------------------------------

    /**
     * @class ZPOSM_t
     * @brief Provides a representation of the zero position MSB register of the AS5047P.
     */
    class ZPOSM_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t ZPOSM:8;       ///< 8 most significant bits of the zero position.

        } ZPOSM_values_t;

        static const uint16_t REG_ADDRESS = 0x0016;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.
        
        ZPOSM_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        ZPOSM_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> ZPOSM_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(ZPOSM_values_t values) -> uint16_t;

    };

    /**
     * @class ZPOSL_t
     * @brief Provides a representation of the zero position LSB /MAG diagnostic register of the AS5047P.
     */
    class ZPOSL_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t ZPOSL:6;               ///< 6 least significant bits of the zero position.
            uint16_t comp_l_error_en:1;     ///< This bit enables the contribution of MAGH (Magnetic field strength too high) to the error flag.
            uint16_t comp_h_error_en:1;     ///< This bit enables the contribution of MAGL (Magnetic field strength too low) to the error flag.

        } ZPOSL_values_t;

        static const uint16_t REG_ADDRESS = 0x0017;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.
        
        ZPOSL_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        ZPOSL_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> ZPOSL_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(ZPOSL_values_t values) -> uint16_t;

    };

    /**
     * @class SETTINGS1_t
     * @brief Provides a representation of the custom setting register 1 of the AS5047P.
     */
    class SETTINGS1_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t FactorySetting:1;  ///< Pre-Programmed to 1.
            uint16_t NOISESET:1;        ///< Noise settings.
            uint16_t DIR:1;             ///< Rotation direction.
            uint16_t UVW_ABI:1;         ///< Defines the PWM Output (0 = ABI is operating, W is used as PWM 1 = UVW is operating, I is used as PWM).
            uint16_t DAECDIS:1;         ///< Disable Dynamic Angle Error Compensation (0 = DAE compensation ON, 1 = DAE compensation OFF).
            uint16_t ABIBIN:1;          ///< ABI decimal or binary selection of the ABI pulses per revolution.
            uint16_t Dataselect:1;      ///< This bit defines which data can be read form address 16383dec (3FFFhex). 0->DAECANG 1->CORDICANG.
            uint16_t PWMon:1;           ///< Enables PWM (setting of UVW_ABI Bit necessary).

        } SETTINGS1_values_t;

        static const uint16_t REG_ADDRESS = 0x0018;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0001;     ///< Register default values.
        
        SETTINGS1_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        SETTINGS1_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> SETTINGS1_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(SETTINGS1_values_t values) -> uint16_t;

    };

    /**
     * @class SETTINGS2_t
     * @brief Provides a representation of the custom setting register 2 of the AS5047P.
     */
    class SETTINGS2_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t UVWPP:3;       ///< UVW number of pole pairs (000 = 1, 001 = 2, 010 = 3, 011 = 4, 100 = 5, 101 = 6, 110 = 7, 111 = 7).
            uint16_t HYS:2;         ///< Hysteresis setting.
            uint16_t ABIRES:3;      ///<  Resolution of ABI.

        } SETTINGS2_values_t;

        static const uint16_t REG_ADDRESS = 0x0019;     ///< Register address.
        static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.
        
        SETTINGS2_values_t values;      ///< Register values.

        /**
         * Default constructor.
         */
        SETTINGS2_t();

        /**
         * Converts a raw byte into a register value struct.
         * @param raw A byte containing the raw data.
         * @return A new value struct.
         */
        static auto RawToValues(uint16_t raw) -> SETTINGS2_values_t;

        /**
         * Converts a value struct into a byte containing the raw data.
         * @param values A value struct.
         * @return A new byte containing the raw data.
         */
        static auto ValuesToRaw(SETTINGS2_values_t values) -> uint16_t;

    };

    // -------------------------------------------------------------
}

#endif // AS5047P_types_h