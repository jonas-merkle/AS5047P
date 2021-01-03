#include "AS5047P_Types.h"

#include "util/AS5047P_Util.h"

namespace AS5047P_types {

    // Errors ------------------------------------------------------

    ERROR_t::ERROR_t(uint8_t sensorSideErrorsRaw, uint8_t controllerSideErrorsRaw) {
        sensorSideErrors.raw = sensorSideErrorsRaw;
        controllerSideErrors.raw = controllerSideErrorsRaw;
    }

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

        data.values.PARC = AS5047P_Util::isEvenParityBitNoSet(data.raw);
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

        data.values.PARD = AS5047P_Util::isEvenParityBitNoSet(data.raw);
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

        data.values.PARD = AS5047P_Util::isEvenParityBitNoSet(data.raw);
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