#ifndef AS5047P_types_h
#define AS5047P_types_h

#include <inttypes.h>

namespace AS5047P_types {

    // Volatile Registers ------------------------------------------
    
    class ERRFL_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t PARERR:1;
                uint16_t INVCOMM:1;
                uint16_t FRERR:1;
                
            } ERRFL_values_t;
    
            ERRFL_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x0001;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> ERRFL_values_t;
            static auto ValuesToRaw(ERRFL_values_t *values) -> uint16_t;
        
    };

    class PROG_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t PROGEN:1;
                uint16_t OTPREF:1;
                uint16_t PROGOTP:1;
                uint16_t PROGVER:1;
                
            } PROG_values_t;
    
            PROG_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x0003;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> PROG_values_t;
            static auto ValuesToRaw(PROG_values_t *values) -> uint16_t;
        
    };

    class DIAAGC_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t AGC:8;
                uint16_t LF:1;
                uint16_t COF:1;
                uint16_t MAGH:1;
                uint16_t MAGL:1;
                
            } DIAAGC_values_t;
    
            DIAAGC_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x3FFC;
            static const uint16_t REG_DEFAULT = 0x0180;
    
            static auto RawToValues(uint16_t *raw) -> DIAAGC_values_t;
            static auto ValuesToRaw(DIAAGC_values_t *values) -> uint16_t;
        
    };

    class MAG_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t CMAG:14;
                
            } MAG_values_t;
    
            MAG_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x3FFD;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> MAG_values_t;
            static auto ValuesToRaw(MAG_values_t *values) -> uint16_t;
        
    };

    class ANGLEUNC_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t CORDICANG:14;
                
            } ANGLEUNC_values_t;
    
            ANGLEUNC_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x3FFE;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> ANGLEUNC_values_t;
            static auto ValuesToRaw(ANGLEUNC_values_t *values) -> uint16_t;
        
    };

    class ANGLECOM_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t DAECANG:14;
                
            } ANGLECOM_values_t;
    
            ANGLECOM_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x3FFF;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> ANGLECOM_values_t;
            static auto ValuesToRaw(ANGLECOM_values_t *values) -> uint16_t;
        
    };

    // -------------------------------------------------------------

    // Non-Volatile Registers --------------------------------------
    
    class ZPOSM_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t ZPOSM:8;
                
            } ZPOSM_values_t;
    
            ZPOSM_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x0016;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> ZPOSM_values_t;
            static auto ValuesToRaw(ZPOSM_values_t *values) -> uint16_t;
        
    };

    class ZPOSL_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t ZPOSL:6;
                uint16_t comp_l_error_en:1;
                uint16_t comp_h_error_en:1;
                
            } ZPOSL_values_t;
    
            ZPOSL_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x0017;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> ZPOSL_values_t;
            static auto ValuesToRaw(ZPOSL_values_t *values) -> uint16_t;
        
    };

    class SETTINGS1_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t FactorySetting:1;
                uint16_t NOISESET:1;
                uint16_t DIR:1;
                uint16_t UVW_ABI:1;
                uint16_t DAECDIS:1;
                uint16_t ABIBIN:1;
                uint16_t Dataselect:1;
                uint16_t PWMon:1;
                
            } SETTINGS1_values_t;
    
            SETTINGS1_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x0018;
            static const uint16_t REG_DEFAULT = 0x0001;
    
            static auto RawToValues(uint16_t *raw) -> SETTINGS1_values_t;
            static auto ValuesToRaw(SETTINGS1_values_t *values) -> uint16_t;
        
    };

    class SETTINGS2_t {

        public:
    
            typedef struct __attribute__ ((__packed__)) {
                
                uint16_t UVWPP:3;
                uint16_t HYS:2;
                uint16_t ABIRES:3;
                
            } SETTINGS2_values_t;
    
            SETTINGS2_values_t values;
    
            static const uint16_t REG_ADDRESS = 0x3FFD;
            static const uint16_t REG_DEFAULT = 0x0000;
    
            static auto RawToValues(uint16_t *raw) -> SETTINGS2_values_t;
            static auto ValuesToRaw(SETTINGS2_values_t *values) -> uint16_t;
        
    };

    // -------------------------------------------------------------
}

#endif // AS5047P_types_h