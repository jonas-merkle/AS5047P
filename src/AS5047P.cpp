#include "AS5047P.h"

// public functions --------------------------------------------

AS5047P::AS5047P(const uint8_t chipSelectPinNo, const uint32_t spiSpeed = 100000) {
    spiInterface = AS5047P_ComBackend::AS5047P_SPI(chipSelectPinNo, spiSpeed);
}

uint16_t AS5047P::readMagnitude() {
    
    AS5047P_types::MAG_t res = AS5047P::read_MAG();
    return res.values.CMAG;

}

uint16_t AS5047P::readAngle(const bool withDAEC = true) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM();
        return res.values.DAECANG;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC();
        return res.values.CORDICANG;
    }

}


auto AS5047P::read_ERRFL() -> AS5047P_types::ERRFL_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ERRFL_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::ERRFL_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

auto AS5047P::read_PROG() -> AS5047P_types::PROG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::PROG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::PROG_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

auto AS5047P::read_DIAAGC() -> AS5047P_types::DIAAGC_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::DIAAGC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::DIAAGC_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

auto AS5047P::read_MAG() -> AS5047P_types::MAG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::MAG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::MAG_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

auto AS5047P::read_ANGLEUNC() -> AS5047P_types::ANGLEUNC_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLEUNC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::ANGLEUNC_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

auto AS5047P::read_ANGLECOM() -> AS5047P_types::ANGLECOM_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLECOM_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(readCMD.values)));
    
    AS5047P_types::ANGLECOM_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(recData.values));
    return res;

}

    
void AS5047P::write_PROG(AS5047P_types::PROG_t regData) {

}


auto AS5047P::read_ZPOSM() -> AS5047P_types::ZPOSM_t {
    return {};
}

auto AS5047P::read_ZPOSL() -> AS5047P_types::ZPOSL_t {
    return {};
}

auto AS5047P::read_SETTINGS1() -> AS5047P_types::SETTINGS1_t {
    return {};
}

auto AS5047P::read_SETTINGS2() -> AS5047P_types::SETTINGS2_t {
    return {};
}


void AS5047P::write_ZPOSM(AS5047P_types::ZPOSM_t regData) {

}

void AS5047P::write_ZPOSL(AS5047P_types::ZPOSL_t regData) {

}

void AS5047P::write_SETTINGS1(AS5047P_types::SETTINGS1_t regData) {

}

void AS5047P::write_SETTINGS2(AS5047P_types::SETTINGS2_t regData) {

}


// -------------------------------------------------------------

// private functions -------------------------------------------

// -------------------------------------------------------------