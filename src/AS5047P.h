#ifndef AS5047P_h
#define AS5047P_h

#include <inttypes.h>

#include "types/AS5047P_Types.h"
#include "spi/AS5047P_SPI.h"


/**
 * @class AS5047P
 * @brief The main class for the AS5047P sensor.
 */
class AS5047P {
    
    public:

        /**
         * Constructor.
         * @param chipSelectPinNo The pin number of the chip select pin (default: 12);
         * @param spiSpeed The spi bus speed (default: 8000000, on Feather M0 tested up to 32000000)
         */
        AS5047P(uint8_t chipSelectPinNo = 12, uint32_t spiSpeed = 100000);

        /**
         * Read the current magnitude value.
         * @return The current magnitude value.
         */
        uint16_t readMagnitude();

        /**
         * Read the current raw angle value.
         * @param withDAEC Flag to select if the value with or without dynamic angle error correction should be returned.
         * @return The current raw angle value.
         */
        uint16_t readAngleRaw(bool withDAEC = true);

        /**
         * Read the current angle value in degree value.
         * @param withDAEC Flag to select if the value with or without dynamic angle error correction should be returned.
         * @return The current angle value in degree value.
         */
        float readAngleDegree(bool withDAEC = true);


        /**
         * Read the ERRFL register.
         * @return The contet of the ERRFL register.
         */
        auto read_ERRFL() -> AS5047P_types::ERRFL_t;

        /**
         * Read the PROG register.
         * @return The contet of the PROG register.
         */
        auto read_PROG() -> AS5047P_types::PROG_t;

        /**
         * Read the DIAAGC register.
         * @return The contet of the DIAAGC register.
         */
        auto read_DIAAGC() -> AS5047P_types::DIAAGC_t;

        /**
         * Read the MAG register.
         * @return The contet of the MAG register.
         */
        auto read_MAG() -> AS5047P_types::MAG_t;

        /**
         * Read the ANGLEUNC register.
         * @return The contet of the ANGLEUNC register.
         */
        auto read_ANGLEUNC() -> AS5047P_types::ANGLEUNC_t;

        /**
         * Read the ANGLECOM register.
         * @return The contet of the ANGLECOM register.
         */
        auto read_ANGLECOM() -> AS5047P_types::ANGLECOM_t;


        /**
         * Write into the PROG register.
         * @param regDat The new contet of the PROG register.
         */            
        void write_PROG(const AS5047P_types::PROG_t *regData);

        
        /**
         * Read the ZPOSM register.
         * @return The contet of the ZPOSM register.
         */
        auto read_ZPOSM() -> AS5047P_types::ZPOSM_t;

        /**
         * Read the ZPOSL register.
         * @return The contet of the ZPOSL register.
         */ 
        auto read_ZPOSL() -> AS5047P_types::ZPOSL_t;

        /**
         * Read the SETTINGS1 register.
         * @return The contet of the SETTINGS1 register.
         */
        auto read_SETTINGS1() -> AS5047P_types::SETTINGS1_t;

        /**
         * Read the SETTINGS2 register.
         * @return The contet of the SETTINGS2 register.
         */
        auto read_SETTINGS2() -> AS5047P_types::SETTINGS2_t;


        /**
         * Write into the ZPOSM register.
         * @param regDat The new contet of the ZPOSM register.
         */
        void write_ZPOSM(const AS5047P_types::ZPOSM_t *regData);

        /**
         * Write into the ZPOSL register.
         * @param regDat The new contet of the ZPOSL register.
         */
        void write_ZPOSL(const AS5047P_types::ZPOSL_t *regData);

        /**
         * Write into the SETTINGS1 register.
         * @param regDat The new contet of the SETTINGS1 register.
         */
        void write_SETTINGS1(const AS5047P_types::SETTINGS1_t *regData);

        /**
         * Write into the ETTINGS2 register.
         * @param regDat The new contet of the ETTINGS2 register.
         */
        void write_SETTINGS2(const AS5047P_types::SETTINGS2_t *regData);

        private:

        AS5047P_ComBackend::AS5047P_SPI __spiInterface;       ///< The instance of the spi interface for the sensor communication.

};

#endif // AS5047P_h