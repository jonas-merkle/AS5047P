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

    class PROG_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t PROGEN:1;
            uint16_t OTPREF:1;
            uint16_t PROGOTP:1;
            uint16_t PROGVER:1;

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

    class DIAAGC_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t AGC:8;
            uint16_t LF:1;
            uint16_t COF:1;
            uint16_t MAGH:1;
            uint16_t MAGL:1;

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

    class MAG_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t CMAG:14;

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

    class ANGLEUNC_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t CORDICANG:14;

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

    class ANGLECOM_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t DAECANG:14;

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

    class ZPOSM_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t ZPOSM:8;

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

    class ZPOSL_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t ZPOSL:6;
            uint16_t comp_l_error_en:1;
            uint16_t comp_h_error_en:1;

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

    class SETTINGS1_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t FactorySetting:1;
            uint16_t NOISESET:1;
            uint16_t DIR:1;
            uint16_t UVW_ABI:1;
            uint16_t DAECDIS:1;
            uint16_t ABIBIN:1;
            uint16_t Dataselect:1;
            uint16_t PWMon:1;

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

    class SETTINGS2_t {

    public:

        typedef struct __attribute__ ((__packed__)) {

            uint16_t UVWPP:3;
            uint16_t HYS:2;
            uint16_t ABIRES:3;

        } SETTINGS2_values_t;

        static const uint16_t REG_ADDRESS = 0x3FFD;     ///< Register address.
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