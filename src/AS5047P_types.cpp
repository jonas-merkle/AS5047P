#include "AS5047P_types.h"

namespace AS5047P_types {

    // Volatile Registers ------------------------------------------

    ERRFL_t::ERRFL_t() {
        values = ERRFL_t::RawToValues(ERRFL_t::REG_DEFAULT);
    }

    auto ERRFL_t::RawToValues(const uint16_t raw) -> ERRFL_t::ERRFL_values_t {
        return {
            .FRERR = (uint16_t) ((raw & 0x0001) >> 0),
            .INVCOMM = (uint16_t) ((raw & 0x0002) >> 1),
            .PARERR = (uint16_t) ((raw & 0x0004) >> 2)
        };
    }

    auto ERRFL_t::ValuesToRaw(const ERRFL_t::ERRFL_values_t values) -> uint16_t {
        return (
            (values.FRERR << 0) +
            (values.INVCOMM << 1) +
            (values.PARERR << 2)
        );
    }

    PROG_t::PROG_t() {
        values = PROG_t::RawToValues(PROG_t::REG_DEFAULT);
    }

    auto PROG_t::RawToValues(const uint16_t raw) -> PROG_t::PROG_values_t {
        return {
            .PROGEN = (uint16_t) ((raw & 0x0001) >> 0),
            .OTPREF = (uint16_t) ((raw & 0x0004) >> 2),
            .PROGOTP = (uint16_t) ((raw & 0x0008) >> 3),
            .PROGVER = (uint16_t) ((raw & 0x0040) >> 6)
        };
    }

    auto PROG_t::ValuesToRaw(const PROG_t::PROG_values_t values) -> uint16_t {
        return (
            (values.PROGEN << 0) +
            (values.OTPREF << 2) +
            (values.PROGOTP << 3) +
            (values.PROGVER << 6)
        );
    }

    DIAAGC_t::DIAAGC_t() {
        values = DIAAGC_t::RawToValues(DIAAGC_t::REG_DEFAULT);
    }

    auto DIAAGC_t::RawToValues(const uint16_t raw) -> DIAAGC_t::DIAAGC_values_t {
        return {
            .AGC = (uint16_t) ((raw & 0x00FF) >> 0),
            .LF = (uint16_t) ((raw & 0x0100) >> 8),
            .COF = (uint16_t) ((raw & 0x0200) >> 9),
            .MAGH = (uint16_t) ((raw & 0x0400) >> 10),
            .MAGL = (uint16_t) ((raw & 0x0800) >> 11),
        };
    }

    auto DIAAGC_t::ValuesToRaw(const DIAAGC_t::DIAAGC_values_t values) -> uint16_t {
        return (
            (values.AGC << 0) +
            (values.LF << 8) +
            (values.COF << 9) +
            (values.MAGH << 10) +
            (values.MAGL << 11)
        );
    }

    MAG_t::MAG_t() {
        values = MAG_t::RawToValues(MAG_t::REG_DEFAULT);
    }

    auto MAG_t::RawToValues(const uint16_t raw) -> MAG_t::MAG_values_t {
        return {
            .CMAG = (uint16_t) ((raw & 0x3FFF) >> 0)
        };
    }

    auto MAG_t::ValuesToRaw(const MAG_t::MAG_values_t values) -> uint16_t {
        return (
            (values.CMAG << 0)
        );
    }

    ANGLEUNC_t::ANGLEUNC_t() {
        values = ANGLEUNC_t::RawToValues(ANGLEUNC_t::REG_DEFAULT);
    }

    auto ANGLEUNC_t::RawToValues(const uint16_t raw) -> ANGLEUNC_t::ANGLEUNC_values_t {
        return {
            .CORDICANG = (uint16_t) ((raw & 0x3FFF) >> 0)
        };
    }

    auto ANGLEUNC_t::ValuesToRaw(const ANGLEUNC_t::ANGLEUNC_values_t values) -> uint16_t {
        return (
            (values.CORDICANG << 0)
        );
    }

    ANGLECOM_t::ANGLECOM_t() {
        values = ANGLECOM_t::RawToValues(ANGLECOM_t::REG_DEFAULT);
    }

    auto ANGLECOM_t::RawToValues(const uint16_t raw) -> ANGLECOM_t::ANGLECOM_values_t {
        return {
            .DAECANG = (uint16_t) ((raw & 0x3FFF) >> 0)
        };
    }

    auto ANGLECOM_t::ValuesToRaw(const ANGLECOM_t::ANGLECOM_values_t values) -> uint16_t {
        return (
            (values.DAECANG << 0)
        );
    }

    // -------------------------------------------------------------

    // Non-Volatile Registers --------------------------------------

    ZPOSM_t::ZPOSM_t() {
        values = ZPOSM_t::RawToValues(ZPOSM_t::REG_DEFAULT);
    }

    auto ZPOSM_t::RawToValues(const uint16_t raw) -> ZPOSM_t::ZPOSM_values_t {
        return {
            .ZPOSM = (uint16_t) ((raw & 0x00FF) >> 0)
        };
    }

    auto ZPOSM_t::ValuesToRaw(const ZPOSM_t::ZPOSM_values_t values) -> uint16_t {
        return (
            (values.ZPOSM << 0)
        );
    }

    ZPOSL_t::ZPOSL_t() {
        values = ZPOSL_t::RawToValues(ZPOSL_t::REG_DEFAULT);
    }

    auto ZPOSL_t::RawToValues(const uint16_t raw) -> ZPOSL_t::ZPOSL_values_t {
        return {
            .ZPOSL = (uint16_t) ((raw & 0x003F) >> 0),
            .comp_l_error_en = (uint16_t) ((raw & 0x0040) >> 6),
            .comp_h_error_en = (uint16_t) ((raw & 0x0080) >> 7)
        };
    }

    auto ZPOSL_t::ValuesToRaw(const ZPOSL_t::ZPOSL_values_t values) -> uint16_t {
        return (
            (values.ZPOSL << 0) +
            (values.comp_l_error_en << 6),
            (values.comp_h_error_en << 7)
        );
    }

    SETTINGS1_t::SETTINGS1_t() {
        values = SETTINGS1_t::RawToValues(SETTINGS1_t::REG_DEFAULT);
    }

    auto SETTINGS1_t::RawToValues(const uint16_t raw) -> SETTINGS1_t::SETTINGS1_values_t {
        return {
            .FactorySetting = (uint16_t) ((raw & 0x0001) >> 0),
            .NOISESET = (uint16_t) ((raw & 0x0002) >> 1),
            .DIR = (uint16_t) ((raw & 0x0004) >> 2),
            .UVW_ABI = (uint16_t) ((raw & 0x0008) >> 3),
            .DAECDIS = (uint16_t) ((raw & 0x0010) >> 4),
            .ABIBIN = (uint16_t) ((raw & 0x0020) >> 5),
            .Dataselect = (uint16_t) ((raw & 0x0040) >> 6),
            .PWMon = (uint16_t) ((raw & 0x0080) >> 7),
        };
    }

    auto SETTINGS1_t::ValuesToRaw(const SETTINGS1_t::SETTINGS1_values_t values) -> uint16_t {
        return (
            (values.FactorySetting << 0) +
            (values.NOISESET << 1) +
            (values.DIR << 2) +
            (values.UVW_ABI << 3) +
            (values.DAECDIS << 4) +
            (values.ABIBIN << 5) +
            (values.Dataselect << 6) +
            (values.PWMon << 7)
        );
    }

    SETTINGS2_t::SETTINGS2_t() {
        values = SETTINGS2_t::RawToValues(SETTINGS2_t::REG_DEFAULT);
    }

    auto SETTINGS2_t::RawToValues(const uint16_t raw) -> SETTINGS2_t::SETTINGS2_values_t {
        return {
            .UVWPP = (uint16_t) ((raw & 0x0007) >> 0),
            .HYS = (uint16_t) ((raw & 0x0018) >> 3),
            .ABIRES = (uint16_t) ((raw & 0x00E0) >> 5),
        };
    }

    auto SETTINGS2_t::ValuesToRaw(const SETTINGS2_t::SETTINGS2_values_t values) -> uint16_t {
        return (
            (values.UVWPP << 0) +
            (values.HYS << 3) +
            (values.ABIRES << 5)
        );
    }

    // -------------------------------------------------------------

}