#include "AS5047P.h"

#include "util/AS5047P_Util.h"

// Constructors ------------------------------------------------

AS5047P::AS5047P(const uint8_t chipSelectPinNo, const uint32_t spiSpeed) : __spiInterface(chipSelectPinNo, spiSpeed) {
}

// -------------------------------------------------------------

// Init --------------------------------------------------------

bool AS5047P::initSPI() {
    
    __spiInterface.init();

    AS5047P_types::DIAAGC_t diagRes = read_DIAAGC();
    
    // @Todo: check if ther is a better way to test the connection...
    return (diagRes.data.raw != 0);

}

// -------------------------------------------------------------

// Util --------------------------------------------------------

bool AS5047P::checkForComErrorF(AS5047P_types::ERROR_t *errorOut) {

    // read the error reg
    auto errorReg = AS5047P::read_ERRFL();

    // verify parity bit
    if (!AS5047P_Util::parityCheck(errorReg.data.raw)) {
        errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
    }

    // write the ERRFL register content in errorOut
    errorOut->sensorSideErrors.flags.SPI_FRAMING_ERROR |= errorReg.data.values.FRERR;
    errorOut->sensorSideErrors.flags.SPI_INVALID_CMD |= errorReg.data.values.INVCOMM;
    errorOut->sensorSideErrors.flags.SPI_PARITY_ERROR |= errorReg.data.values.PARERR;

    // check for no errors
    if (!errorReg.data.values.FRERR &&
        !errorReg.data.values.INVCOMM &&
        !errorReg.data.values.PARERR &&
        !errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR) {
        return true;
    }
    else {
        return false;
    }
}

bool AS5047P::checkForSensorErrorF(AS5047P_types::ERROR_t *errorOut) {

    // read the diag reg
    auto diagReg = AS5047P::read_DIAAGC();

    // verify parity bit
    if (!AS5047P_Util::parityCheck(diagReg.data.raw)) {
        errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
    }

    // write the ERRFL register content in errorOut
    errorOut->sensorSideErrors.flags.CORDIC_OVERFLOW_ERROR |= diagReg.data.values.COF;
    errorOut->sensorSideErrors.flags.OFFSET_COMPENSATION_ERROR |= diagReg.data.values.LF;
    errorOut->sensorSideErrors.flags.MAG_TOO_HIGH |= diagReg.data.values.MAGH;
    errorOut->sensorSideErrors.flags.MAG_TOO_LOW |= diagReg.data.values.MAGL;

    // check for no errors
    if (!diagReg.data.values.COF &&
        !diagReg.data.values.LF &&
        !diagReg.data.values.MAGH &&
        !diagReg.data.values.MAGL &&
        !errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR) {
        return true;
    }
    else {
        return false;
    }
}

bool AS5047P::verifyWittenRegF(uint16_t regAddress, uint16_t expectedData) {

    // check parity of expected data
    if (!AS5047P_Util::parityCheck(expectedData)) {
        return false;
    }
    
    // send read command
    AS5047P_types::SPI_Command_Frame_t readCMD(regAddress, AS5047P_TYPES_READ_CMD);

    // read register content
    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));

    // check parity of received data
    if (!AS5047P_Util::parityCheck(recData.data.raw)) {
        return false;
    }
    
    // check read reg data and expected data and return the result
    return recData.data.raw == expectedData;
}

#ifdef ARDUINO_ARCH_SAMD
std::string AS5047P::readStatusAsStdString() {

    AS5047P_types::ERRFL_t errorReg = read_ERRFL();
    AS5047P_types::DIAAGC_t diagReg = read_DIAAGC();

    std::string str;
    str.reserve(AS5047P_INFO_STRING_BUFFER_SIZE);

    str.append("#########################\n");
    str.append(" Error Information:\n");
    str.append("-------------------------\n");
    str.append("- Framing error:   ");
    str.append(std::to_string(errorReg.data.values.FRERR));
    str.append("\n");
    str.append("- Invalid command: ");
    str.append(std::to_string(errorReg.data.values.INVCOMM));
    str.append("\n");
    str.append("- Parity error:    ");
    str.append(std::to_string(errorReg.data.values.PARERR));
    str.append("\n");
    str.append("#########################\n");
    str.append(" Diagnostic Information: \n");
    str.append("-------------------------\n");
    str.append("- AGC Value:       ");
    str.append(std::to_string(diagReg.data.values.AGC));
    str.append("\n");
    str.append("- Offset comp.:    ");
    str.append(std::to_string(diagReg.data.values.LF));
    str.append("\n");
    str.append("- CORDIC overflow: ");
    str.append(std::to_string(diagReg.data.values.COF));
    str.append("\n");
    str.append("- MAG too high:    ");
    str.append(std::to_string(diagReg.data.values.MAGH));
    str.append("\n");
    str.append("- MAG too low:     ");
    str.append(std::to_string(diagReg.data.values.MAGL));
    str.append("\n");
    str.append("#########################\n");

    str.shrink_to_fit();

    return str;

}
#endif

String AS5047P::readStatusAsArduinoString() {
    AS5047P_types::ERRFL_t errorReg = read_ERRFL();
    AS5047P_types::DIAAGC_t diagReg = read_DIAAGC();

    char buf[AS5047P_INFO_STRING_BUFFER_SIZE] = {0};

    sprintf(buf,
        "#########################\n Error Information:\n-------------------------\n- Framing error:   %d\n- Invalid command: %d\n- Parity error:    %d\n#########################\n Diagnostic Information: \n-------------------------\n- AGC Value:       %d\n- Offset comp.:    %d\n- CORDIC overflow: %d\n- MAG too high:    %d\n- MAG too low:     %d\n#########################\n",
        errorReg.data.values.FRERR, errorReg.data.values.INVCOMM, errorReg.data.values.PARERR,
        diagReg.data.values.AGC, diagReg.data.values.LF, diagReg.data.values.COF, diagReg.data.values.MAGH, diagReg.data.values.MAGL
    );

    return String(buf);
}

// -------------------------------------------------------------

// Read High-Level ---------------------------------------------

uint16_t AS5047P::readMagnitude() {
    
    AS5047P_types::MAG_t res = AS5047P::read_MAG();
    return res.data.values.CMAG;

}

uint16_t AS5047P::readMagnitude(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) {

    AS5047P_types::MAG_t res = AS5047P::read_MAG(errorOut, verifyParity, checkForComError, checkForSensorError);
    return res.data.values.CMAG;

}

uint16_t AS5047P::readAngleRaw(const bool withDAEC) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM();
        return res.data.values.DAECANG;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC();
        return res.data.values.CORDICANG;
    }

}

uint16_t AS5047P::readAngleRaw(AS5047P_types::ERROR_t *errorOut, bool withDAEC, bool verifyParity, bool checkForComError, bool checkForSensorError) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM(errorOut, verifyParity, checkForComError, checkForSensorError);
        return res.data.values.DAECANG;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC(errorOut, verifyParity, checkForComError, checkForSensorError);
        return res.data.values.CORDICANG;
    }

}

float AS5047P::readAngleDegree(bool withDAEC) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM();
        return (res.data.values.DAECANG/(float)0x3FFF)*360;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC();
        return (res.data.values.CORDICANG/(float)0x3FFF)*360;
    }

}

float AS5047P::readAngleDegree(AS5047P_types::ERROR_t *errorOut, bool withDAEC, bool verifyParity, bool checkForComError, bool checkForSensorError) {

    if (withDAEC) {
        AS5047P_types::ANGLECOM_t res = AS5047P::read_ANGLECOM(errorOut, verifyParity, checkForComError, checkForSensorError);
        return (res.data.values.DAECANG/(float)0x3FFF)*360;
    }
    else {
        AS5047P_types::ANGLEUNC_t res = AS5047P::read_ANGLEUNC(errorOut, verifyParity, checkForComError, checkForSensorError);
        return (res.data.values.CORDICANG/(float)0x3FFF)*360;
    }

}

// -------------------------------------------------------------

// Read Volatile Registers -------------------------------------

auto AS5047P::read_ERRFL() -> AS5047P_types::ERRFL_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ERRFL_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::ERRFL_t(recData.data.raw);

}

auto AS5047P::read_ERRFL(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::ERRFL_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_ERRFL();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_PROG() -> AS5047P_types::PROG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::PROG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::PROG_t(recData.data.raw);

}

auto AS5047P::read_PROG(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::PROG_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_PROG();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_DIAAGC() -> AS5047P_types::DIAAGC_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::DIAAGC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::DIAAGC_t(recData.data.raw);

}

auto AS5047P::read_DIAAGC(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::DIAAGC_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_DIAAGC();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_MAG() -> AS5047P_types::MAG_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::MAG_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::MAG_t(recData.data.raw);

}

auto AS5047P::read_MAG(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::MAG_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_MAG();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_ANGLEUNC() -> AS5047P_types::ANGLEUNC_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLEUNC_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::ANGLEUNC_t(recData.data.raw);

}

auto AS5047P::read_ANGLEUNC(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::ANGLEUNC_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_ANGLEUNC();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_ANGLECOM() -> AS5047P_types::ANGLECOM_t {
    
    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ANGLECOM_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::ANGLECOM_t(recData.data.raw);

}

auto AS5047P::read_ANGLECOM(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::ANGLECOM_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_ANGLECOM();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

// -------------------------------------------------------------

// Write Volatile Registers ------------------------------------
    
void AS5047P::write_PROG(const AS5047P_types::PROG_t *regData) {

}

void AS5047P::write_PROG(const AS5047P_types::PROG_t *regData, AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool verifyWittenReg) {

}

// -------------------------------------------------------------

// Read Non-Volatile Registers ---------------------------------

auto AS5047P::read_ZPOSM() -> AS5047P_types::ZPOSM_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ZPOSM_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::ZPOSM_t(recData.data.raw);

}

auto AS5047P::read_ZPOSM(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::ZPOSM_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_ZPOSM();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_ZPOSL() -> AS5047P_types::ZPOSL_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::ZPOSL_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::ZPOSL_t(recData.data.raw);

}

auto AS5047P::read_ZPOSL(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::ZPOSL_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_ZPOSL();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_SETTINGS1() -> AS5047P_types::SETTINGS1_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::SETTINGS1_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::SETTINGS1_t(recData.data.raw);

}

auto AS5047P::read_SETTINGS1(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::SETTINGS1_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_SETTINGS1();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

auto AS5047P::read_SETTINGS2() -> AS5047P_types::SETTINGS2_t {

    AS5047P_types::SPI_Command_Frame_t readCMD(AS5047P_types::SETTINGS2_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);

    AS5047P_types::SPI_ReadData_Frame_t recData(__spiInterface.read(readCMD.data.raw));
    
    return AS5047P_types::SETTINGS2_t(recData.data.raw);

}

auto AS5047P::read_SETTINGS2(AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool checkForSensorError) -> AS5047P_types::SETTINGS2_t {
    
    // reset error data
    *errorOut = AS5047P_types::ERROR_t();

    // read base register
    auto res = read_SETTINGS2();

    // verify parity bit
    if (verifyParity) {
        if (!AS5047P_Util::parityCheck(res.data.raw)) {
            errorOut->controllerSideErrors.flags.SPI_PARITY_ERROR = true;
        }
    }

    // check for communication error
    if (checkForComError) {
        checkForComErrorF(errorOut);
    }

    // check for sensor error
    if (checkForSensorError) {
        checkForSensorErrorF(errorOut);

        // check for communication error
        if (checkForComError) {
            checkForComErrorF(errorOut);
        }
    }

    return res;

}

// -------------------------------------------------------------

// Write Non-Volatile Registers --------------------------------

void AS5047P::write_ZPOSM(const AS5047P_types::ZPOSM_t *regData) {

}

void AS5047P::write_ZPOSM(const AS5047P_types::ZPOSM_t *regData, AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool verifyWittenReg) {

}

void AS5047P::write_ZPOSL(const AS5047P_types::ZPOSL_t *regData) {

}

void AS5047P::write_ZPOSL(const AS5047P_types::ZPOSL_t *regData, AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool verifyWittenReg) {

}

void AS5047P::write_SETTINGS1(const AS5047P_types::SETTINGS1_t *regData) {

}

void AS5047P::write_SETTINGS1(const AS5047P_types::SETTINGS1_t *regData, AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool verifyWittenReg) {

}

void AS5047P::write_SETTINGS2(const AS5047P_types::SETTINGS2_t *regData) {

}

void AS5047P::write_SETTINGS2(const AS5047P_types::SETTINGS2_t *regData, AS5047P_types::ERROR_t *errorOut, bool verifyParity, bool checkForComError, bool verifyWittenReg) {

}

// -------------------------------------------------------------
