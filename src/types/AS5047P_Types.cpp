/**
 * @file AS5047P_Types.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This sourcefile contains the implementation of the type definitions for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#include "AS5047P_Types.h"

#include "./../util/AS5047P_Util.h"

namespace AS5047P_Types {

    // Errors ------------------------------------------------------

    ERROR_t::ERROR_t(uint8_t sensorSideErrorsRaw, uint8_t controllerSideErrorsRaw) {

        sensorSideErrors.raw = sensorSideErrorsRaw;
        controllerSideErrors.raw = controllerSideErrorsRaw;
    }

    bool ERROR_t::noError() const {
        return (
            sensorSideErrors.raw == 0 &&
            controllerSideErrors.raw == 0
        );
    }

    
    #if (defined(AS5047P_OP_MODE_Arduino) && (defined(ARDUINO_ARCH_SAMD) || defined(CORE_TEENSY))) || defined(AS5047P_OP_MODE_Zephyr)
    std::string ERROR_t::toString() {
        
        std::string str;
        str.reserve(AS5047P__TYPES_ERROR_STRING_BUFFER_SIZE);

        str.append("##################################\n");
        str.append(" Sensor Side Errors:\n");
        str.append("----------------------------------\n");
        str.append("- SENS_SPI_FRAMING_ERROR:     ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_SPI_FRAMING_ERROR));
        str.append("\n");
        str.append("- SENS_SPI_INVALID_CMD:       ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_SPI_INVALID_CMD));
        str.append("\n");
        str.append("- SENS_SPI_PARITY_ERROR:      ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_SPI_PARITY_ERROR));
        str.append("\n");
        str.append("- SENS_OFFSET_COMP_ERROR:     ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_OFFSET_COMP_ERROR));
        str.append("\n");
        str.append("- SENS_CORDIC_OVERFLOW_ERROR: ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_CORDIC_OVERFLOW_ERROR));
        str.append("\n");
        str.append("- SENS_CORDIC_OVERFLOW_ERROR: ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_MAG_TOO_HIGH));
        str.append("\n");
        str.append("- SENS_MAG_TOO_LOW:           ");
        str.append(AS5047P_Util::to_string(sensorSideErrors.flags.SENS_MAG_TOO_LOW));
        str.append("\n");
        str.append("##################################\n");
        str.append(" Controller Side Errors: \n");
        str.append("----------------------------------\n");
        str.append("- CONT_SPI_PARITY_ERROR:      ");
        str.append(AS5047P_Util::to_string(controllerSideErrors.flags.CONT_SPI_PARITY_ERROR));
        str.append("\n");
        str.append("- CONT_GENERAL_COM_ERROR:     ");
        str.append(AS5047P_Util::to_string(controllerSideErrors.flags.CONT_GENERAL_COM_ERROR));
        str.append("\n");
        str.append("- CONT_WRITE_VERIFY_FAILED:   ");
        str.append(AS5047P_Util::to_string(controllerSideErrors.flags.CONT_WRITE_VERIFY_FAILED));
        str.append("\n");
        str.append("##################################\n");

        str.shrink_to_fit();

        return str;

    }
    #endif // (AS5047P_OP_MODE_Arduino && (ARDUINO_ARCH_SAMD || CORE_TEENSY)) || AS5047P_OP_MODE_Zephyr

    #if defined(AS5047P_OP_MODE_Arduino)
    String ERROR_t::toArduinoString() {

        char buf[AS5047P__TYPES_ERROR_STRING_BUFFER_SIZE] = {0};

        sprintf(buf,
            "##################################\n Sensor Side Errors:\n----------------------------------\n- SENS_SPI_FRAMING_ERROR:     %d\n- SENS_SPI_INVALID_CMD:       %d\n- SENS_SPI_PARITY_ERROR:      %d\n- SENS_OFFSET_COMP_ERROR:     %d\n- SENS_CORDIC_OVERFLOW_ERROR: %d\n- SENS_CORDIC_OVERFLOW_ERROR: %d\n- SENS_MAG_TOO_LOW:           %d\n##################################\n Controller Side Errors: \n----------------------------------\n- CONT_SPI_PARITY_ERROR:      %d\n- CONT_GENERAL_COM_ERROR:     %d\n- CONT_WRITE_VERIFY_FAILED:   %d\n##################################\n",
            sensorSideErrors.flags.SENS_SPI_FRAMING_ERROR, sensorSideErrors.flags.SENS_SPI_INVALID_CMD, sensorSideErrors.flags.SENS_SPI_PARITY_ERROR,
            sensorSideErrors.flags.SENS_OFFSET_COMP_ERROR, sensorSideErrors.flags.SENS_CORDIC_OVERFLOW_ERROR, sensorSideErrors.flags.SENS_MAG_TOO_HIGH, 
            sensorSideErrors.flags.SENS_MAG_TOO_LOW,

            controllerSideErrors.flags.CONT_SPI_PARITY_ERROR, controllerSideErrors.flags.CONT_GENERAL_COM_ERROR, controllerSideErrors.flags.CONT_WRITE_VERIFY_FAILED
        );

        return String(buf);

    }
    #endif // AS5047P_OP_MODE_Arduino

    // -------------------------------------------------------------

    // SPI Frames --------------------------------------------------

    SPI_Command_Frame_t::SPI_Command_Frame_t(const uint16_t raw) {
        data.raw = raw;
    }

    SPI_Command_Frame_t::SPI_Command_Frame_t(const uint16_t ADDR, const uint16_t RW) {
        data.values = {
            .ADDR = ADDR,
            .RW = RW,
            .PARC = 0
        };

        data.values.PARC = !AS5047P_Util::hasEvenNoOfBits(data.raw);
    }

    SPI_ReadData_Frame_t::SPI_ReadData_Frame_t(const uint16_t raw) {
        data.raw = raw;
    }

    SPI_ReadData_Frame_t::SPI_ReadData_Frame_t(const uint16_t DATA, const uint16_t EF) {
        data.values = {
            .DATA = DATA,
            .EF = EF,
            .PARD = 0
        };

        data.values.PARD = !AS5047P_Util::hasEvenNoOfBits(data.raw);
    }

    SPI_WriteData_Frame_t::SPI_WriteData_Frame_t(const uint16_t raw) {
        data.raw = raw;
    }

    SPI_WriteData_Frame_t::SPI_WriteData_Frame_t(const uint16_t DATA, const uint16_t NC) {
        data.values = {
            .DATA = DATA,
            .NC = NC,
            .PARD = 0
        };

        data.values.PARD = !AS5047P_Util::hasEvenNoOfBits(data.raw);
    }

    // -------------------------------------------------------------

    // Volatile Registers ------------------------------------------

    ERRFL_t::ERRFL_t() {
        data.raw = ERRFL_t::REG_DEFAULT;
    }

    ERRFL_t::ERRFL_t(uint16_t raw) {
        data.raw = raw;
    }

    PROG_t::PROG_t() {
        data.raw = PROG_t::REG_DEFAULT;
    }

    PROG_t::PROG_t(uint16_t raw) {
        data.raw = raw;
    }

    DIAAGC_t::DIAAGC_t() {
        data.raw = DIAAGC_t::REG_DEFAULT;
    }

    DIAAGC_t::DIAAGC_t(uint16_t raw) {
        data.raw = raw;
    }

    MAG_t::MAG_t() {
        data.raw = MAG_t::REG_DEFAULT;
    }

    MAG_t::MAG_t(uint16_t raw) {
        data.raw = raw;
    }

    ANGLEUNC_t::ANGLEUNC_t() {
        data.raw = ANGLEUNC_t::REG_DEFAULT;
    }

    ANGLEUNC_t::ANGLEUNC_t(uint16_t raw) {
        data.raw = raw;
    }

    ANGLECOM_t::ANGLECOM_t() {
        data.raw = ANGLECOM_t::REG_DEFAULT;
    }

    ANGLECOM_t::ANGLECOM_t(uint16_t raw) {
        data.raw = raw;
    }

    // -------------------------------------------------------------

    // Non-Volatile Registers --------------------------------------

    ZPOSM_t::ZPOSM_t() {
        data.raw = ZPOSM_t::REG_DEFAULT;
    }

    ZPOSM_t::ZPOSM_t(uint16_t raw) {
        data.raw = raw;
    }

    ZPOSL_t::ZPOSL_t() {
        data.raw = ZPOSL_t::REG_DEFAULT;
    }

    ZPOSL_t::ZPOSL_t(uint16_t raw) {
        data.raw = raw;
    }

    SETTINGS1_t::SETTINGS1_t() {
        data.raw = SETTINGS1_t::REG_DEFAULT;
    }

    SETTINGS1_t::SETTINGS1_t(uint16_t raw) {
        data.raw = raw;
    }

    SETTINGS2_t::SETTINGS2_t() {
        data.raw = SETTINGS2_t::REG_DEFAULT;
    }

    SETTINGS2_t::SETTINGS2_t(uint16_t raw) {
        data.raw = raw;
    }

    // -------------------------------------------------------------
}
