#include "AS5047P_types.h"

namespace AS5047P_types {

    // Volatile Registers ------------------------------------------

    auto ERRFL_t::RawToValues(uint16_t *raw) -> ERRFL_t::ERRFL_values_t {
        return {};
    }

    auto ERRFL_t::ValuesToRaw(ERRFL_t::ERRFL_values_t *values) -> uint16_t {
        return 0;
    }

    auto PROG_t::RawToValues(uint16_t *raw) -> PROG_t::PROG_values_t {
        return {};
    }

    auto PROG_t::ValuesToRaw(PROG_t::PROG_values_t *values) -> uint16_t {
        return 0;
    }

    auto DIAAGC_t::RawToValues(uint16_t *raw) -> DIAAGC_t::DIAAGC_values_t {
        return {};
    }

    auto DIAAGC_t::ValuesToRaw(DIAAGC_t::DIAAGC_values_t *values) -> uint16_t {
        return 0;
    }

    auto MAG_t::RawToValues(uint16_t *raw) -> MAG_t::MAG_values_t {
        return {};
    }

    auto MAG_t::ValuesToRaw(MAG_t::MAG_values_t *values) -> uint16_t {
        return 0;
    }

    auto ANGLEUNC_t::RawToValues(uint16_t *raw) -> ANGLEUNC_t::ANGLEUNC_values_t {
        return {};
    }

    auto ANGLEUNC_t::ValuesToRaw(ANGLEUNC_t::ANGLEUNC_values_t *values) -> uint16_t {
        return 0;
    }

    auto ANGLECOM_t::RawToValues(uint16_t *raw) -> ANGLECOM_t::ANGLECOM_values_t {
        return {};
    }

    auto ANGLECOM_t::ValuesToRaw(ANGLECOM_t::ANGLECOM_values_t *values) -> uint16_t {
        return 0;
    }

    // -------------------------------------------------------------

    // Non-Volatile Registers --------------------------------------

    auto ZPOSM_t::RawToValues(uint16_t *raw) -> ZPOSM_t::ZPOSM_values_t {
        return {};
    }

    auto ZPOSM_t::ValuesToRaw(ZPOSM_t::ZPOSM_values_t *values) -> uint16_t {
        return 0;
    }

    auto ZPOSL_t::RawToValues(uint16_t *raw) -> ZPOSL_t::ZPOSL_values_t {
        return {};
    }

    auto ZPOSL_t::ValuesToRaw(ZPOSL_t::ZPOSL_values_t *values) -> uint16_t {
        return 0;
    }

    auto SETTINGS1_t::RawToValues(uint16_t *raw) -> SETTINGS1_t::SETTINGS1_values_t {
        return {};
    }

    auto SETTINGS1_t::ValuesToRaw(SETTINGS1_t::SETTINGS1_values_t *values) -> uint16_t {
        return 0;
    }

    auto SETTINGS2_t::RawToValues(uint16_t *raw) -> SETTINGS2_t::SETTINGS2_values_t {
        return {};
    }

    auto SETTINGS2_t::ValuesToRaw(SETTINGS2_t::SETTINGS2_values_t *values) -> uint16_t {
        return 0;
    }

    // -------------------------------------------------------------

}