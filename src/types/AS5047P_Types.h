#ifndef AS5047P_types_h
#define AS5047P_types_h

#include <inttypes.h>

#define AS5047P_TYPES_WRITE_CMD 0       ///< Write command flag.
#define AS5047P_TYPES_READ_CMD 1        ///< Read command flag.

/**
 * @namespace AS5047P_types
 * @brief The namespace for all custom types needed for the AS5047P sensor.
 */
namespace AS5047P_types {

    // SPI Frames --------------------------------------------------

    /**
     * @class SPI_Command_Frame_t
     * @brief Provides a representation a "SPI Command Frame".
     */
    class SPI_Command_Frame_t {

        public:
            /**
             * @typedef SPI_Command_Frame_values_t
             * @brief Provides a new datatype for the content of a "SPI Command Frame".
             */
            typedef struct __attribute__ ((__packed__)) {

                uint16_t ADDR:14;       ///< Address to read or write.
                uint16_t RW:1;          ///< 0: Write 1: Read.
                uint16_t PARC:1;        ///< Parity bit (even) calculated on the lower 15 bits of command frame.

            } SPI_Command_Frame_values_t;

            SPI_Command_Frame_values_t values;      ///< Register values.

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            SPI_Command_Frame_t(uint16_t raw);
            
            /**
             * Constructor.
             * @param ADDR 14 bit address.
             * @param RW 0: Write 1: Read.
             */
            SPI_Command_Frame_t(uint16_t ADDR, uint16_t RW);


            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> SPI_Command_Frame_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const SPI_Command_Frame_values_t *values) -> uint16_t;

    };


    /**
     * @class SPI_ReadData_Frame_t
     * @brief Provides a representation a "SPI Read Data Frame".
     */
    class SPI_ReadData_Frame_t {

        public:
            /**
             * @typedef SPI_ReadData_Frame_t
             * @brief Provides a new datatype for the content of a "SPI Read Data Frame".
             */
            typedef struct __attribute__ ((__packed__)) {

                uint16_t DATA:14;       ///< Address to read or write.
                uint16_t EF:1;          ///< 0: No command frame error occurred 1: Error occurred.
                uint16_t PARD:1;        ///< Parity bit (even) calculated on the lower 15 bits.

            } SPI_ReadData_Frame_values_t;

            SPI_ReadData_Frame_values_t values;      ///< Register values.

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            SPI_ReadData_Frame_t(uint16_t raw);
            
            /**
             * Constructor.
             * @param ADDR 14 bit data.
             * @param EF 0: No command frame error occurred 1: Error occurred.
             */
            SPI_ReadData_Frame_t(uint16_t ADDR, uint16_t EF);


            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> SPI_ReadData_Frame_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const SPI_ReadData_Frame_values_t *values) -> uint16_t;

    };


    /**
     * @class SPI_WriteData_Frame_t
     * @brief Provides a representation a "SPI Write Data Frame".
     */
    class SPI_WriteData_Frame_t {

        public:
            /**
             * @typedef SPI_WriteData_Frame_t
             * @brief Provides a new datatype for the content of a "SPI Write Data Frame".
             */
            typedef struct __attribute__ ((__packed__)) {

                uint16_t DATA:1;        ///< Address to read or write.
                uint16_t NC:1;          ///< Always low.
                uint16_t PARD:1;        ///< Parity bit (even)

            } SPI_WriteData_Frame_values_t;

            SPI_WriteData_Frame_values_t values;      ///< Register values.

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            SPI_WriteData_Frame_t(uint16_t raw);
            
            /**
             * Constructor.
             * @param ADDR 14 bit data.
             * @param NC Always low (0).
             */
            SPI_WriteData_Frame_t(uint16_t ADDR, uint16_t NC);


            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> SPI_WriteData_Frame_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const SPI_WriteData_Frame_values_t *values) -> uint16_t;

    };

    // -------------------------------------------------------------


    // Volatile Registers ------------------------------------------

    /**
     * @class NOP_t
     * @brief Provides a representation of the no operation register of the AS5047P.
     */
    class NOP_t {
        
        public:
        
            static const uint16_t REG_ADDRESS = 0x0000;     ///< Register address.

    };

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

            ERRFL_values_t values;      ///< Register values.

            /**
             * Default constructor.
             */
            ERRFL_t();

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            ERRFL_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> ERRFL_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const ERRFL_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            PROG_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> PROG_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const PROG_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            DIAAGC_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> DIAAGC_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const DIAAGC_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            MAG_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> MAG_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const MAG_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            ANGLEUNC_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> ANGLEUNC_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const ANGLEUNC_values_t *values) -> uint16_t;

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
            ANGLECOM_t(uint16_t raw);

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            ANGLECOM_t();

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> ANGLECOM_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const ANGLECOM_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            ZPOSM_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> ZPOSM_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const ZPOSM_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            ZPOSL_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> ZPOSL_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const ZPOSL_values_t *values) -> uint16_t;

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
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            SETTINGS1_t(uint16_t raw);


            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> SETTINGS1_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const SETTINGS1_values_t *values) -> uint16_t;

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
                uint16_t ABIRES:3;      ///< Resolution of ABI.

            } SETTINGS2_values_t;

            static const uint16_t REG_ADDRESS = 0x0019;     ///< Register address.
            static const uint16_t REG_DEFAULT = 0x0000;     ///< Register default values.
            
            SETTINGS2_values_t values;      ///< Register values.

            /**
             * Default constructor.
             */
            SETTINGS2_t();

            /**
             * Constructor.
             * @param raw Two bytes of raw data.
             */
            SETTINGS2_t(uint16_t raw);

            /**
             * Converts a raw byte into a register value struct.
             * @param raw Two bytes containing the raw data.
             * @return A new value struct.
             */
            static auto RawToValues(const uint16_t *raw) -> SETTINGS2_values_t;

            /**
             * Converts a value struct into two bytes containing the raw data.
             * @param values A value struct.
             * @return A new byte containing the raw data.
             */
            static auto ValuesToRaw(const SETTINGS2_values_t *values) -> uint16_t;

    };

    // -------------------------------------------------------------
}

#endif // AS5047P_types_h
