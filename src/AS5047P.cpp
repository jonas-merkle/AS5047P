#include "AS5047P.h"


AS5047P::AS5047P(const uint8_t chipSelectPinNo, const uint32_t spiSpeed) : __spiInterface(chipSelectPinNo, spiSpeed) {
}


bool AS5047P::init() {
    
    __spiInterface.init();

    AS5047P_types::DIAAGC_t diagRes = read_DIAAGC();
    
    // Todo: check if ther is a better way to test the connection...
    return (AS5047P_types::DIAAGC_t::ValuesToRaw(&diagRes.values) != 0);

}

std::string AS5047P::readStatusAsString() {

    AS5047P_types::ERRFL_t errorReg = read_ERRFL();
    AS5047P_types::DIAAGC_t diagReg = read_DIAAGC();

    std::string str;
    str.reserve(350);

    str.append("#########################\n");
    str.append(" Error Information:\n");
    str.append("-------------------------\n");
    str.append("- Framing error:   ");
    str.append(std::to_string(errorReg.values.FRERR));
    str.append("\n");
    str.append("- Invalid command: ");
    str.append(std::to_string(errorReg.values.INVCOMM));
    str.append("\n");
    str.append("- Parity error:    ");
    str.append(std::to_string(errorReg.values.PARERR));
    str.append("\n");
    str.append("#########################\n");
    str.append(" Diagnostic Information: \n");
    str.append("-------------------------\n");
    str.append("- AGC Value:       ");
    str.append(std::to_string(diagReg.values.AGC));
    str.append("\n");
    str.append("- Offset comp.:    ");
    str.append(std::to_string(diagReg.values.LF));
    str.append("\n");
    str.append("- CORDIC overflow: ");
    str.append(std::to_string(diagReg.values.COF));
    str.append("\n");
    str.append("- MAG too high:    ");
    str.append(std::to_string(diagReg.values.MAGH));
    str.append("\n");
    str.append("- MAG too low:     ");
    str.append(std::to_string(diagReg.values.MAGL));
    str.append("\n");
    str.append("#########################\n");

    str.shrink_to_fit();

    return str;

}


uint16_t AS5047P::readMagnitude() {
    
    AS5047P_types::MAG_t res = AS5047P::read_MAG();
    return res.values.CMAG;

}

uint16_t AS5047P::readAngleRaw(const bool withDAEC) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM();
        return res.values.DAECANG;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC();
        return res.values.CORDICANG;
    }

}

float AS5047P::readAngleDegree(bool withDAEC) {
    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM();
        return (res.values.DAECANG/(float)0x3FFF)*360;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC();
        return (res.values.CORDICANG/(float)0x3FFF)*360;
    }

}


auto AS5047P::read_ERRFL() -> AS5047P_types::ERRFL_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ERRFL_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::ERRFL_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_PROG() -> AS5047P_types::PROG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::PROG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::PROG_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_DIAAGC() -> AS5047P_types::DIAAGC_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::DIAAGC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::DIAAGC_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_MAG() -> AS5047P_types::MAG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::MAG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::MAG_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_ANGLEUNC() -> AS5047P_types::ANGLEUNC_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLEUNC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::ANGLEUNC_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_ANGLECOM() -> AS5047P_types::ANGLECOM_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLECOM_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::ANGLECOM_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

    
void AS5047P::write_PROG(const AS5047P_types::PROG_t *regData) {

}


auto AS5047P::read_ZPOSM() -> AS5047P_types::ZPOSM_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ZPOSM_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::ZPOSM_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_ZPOSL() -> AS5047P_types::ZPOSL_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ZPOSL_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::ZPOSL_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_SETTINGS1() -> AS5047P_types::SETTINGS1_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::SETTINGS1_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::SETTINGS1_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}

auto AS5047P::read_SETTINGS2() -> AS5047P_types::SETTINGS2_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::SETTINGS2_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(AS5047P_types::SPI_Command_Frame_t::ValuesToRaw(&readCMD.values)));
    
    AS5047P_types::SETTINGS2_t res(AS5047P_types::SPI_ReadData_Frame_t::ValuesToRaw(&recData.values));
    return res;

}


void AS5047P::write_ZPOSM(const AS5047P_types::ZPOSM_t *regData) {

}

void AS5047P::write_ZPOSL(const AS5047P_types::ZPOSL_t *regData) {

}

void AS5047P::write_SETTINGS1(const AS5047P_types::SETTINGS1_t *regData) {

}

void AS5047P::write_SETTINGS2(const AS5047P_types::SETTINGS2_t *regData) {

}
