#ifndef AS5047P_h
#define AS5047P_h

#include <inttypes.h>

#include "AS5047P_types.h"
#include "AS5047P_SPI.h"


class AS5047P {
    
    public:

    AS5047P(uint8_t chipSelectPinNo, uint32_t spiSpeed = 100000);

    uint16_t readMagnitude();
    uint16_t readAngleRaw(bool withDAEC = true);
    float readAngleDegree(bool withDAEC = true);

    auto read_ERRFL() -> AS5047P_types::ERRFL_t;
    auto read_PROG() -> AS5047P_types::PROG_t;
    auto read_DIAAGC() -> AS5047P_types::DIAAGC_t;
    auto read_MAG() -> AS5047P_types::MAG_t;
    auto read_ANGLEUNC() -> AS5047P_types::ANGLEUNC_t;
    auto read_ANGLECOM() -> AS5047P_types::ANGLECOM_t;
        
    void write_PROG(const AS5047P_types::PROG_t *regData);

    auto read_ZPOSM() -> AS5047P_types::ZPOSM_t;
    auto read_ZPOSL() -> AS5047P_types::ZPOSL_t;
    auto read_SETTINGS1() -> AS5047P_types::SETTINGS1_t;
    auto read_SETTINGS2() -> AS5047P_types::SETTINGS2_t;

    void write_ZPOSM(const AS5047P_types::ZPOSM_t *regData);
    void write_ZPOSL(const AS5047P_types::ZPOSL_t *regData);
    void write_SETTINGS1(const AS5047P_types::SETTINGS1_t *regData);
    void write_SETTINGS2(const AS5047P_types::SETTINGS2_t *regData);

    private:

    AS5047P_ComBackend::AS5047P_SPI spiInterface;

};

#endif // AS5047P_h