/**
 * @file AS5047P_SPI_Zephyr.cpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This sourefile contains the implementation of the Zephyr SPI bus handler for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#include "AS5047P_SPI_Zephyr.h"

// disable in non Zephyr op mode
#if defined(AS5047P_OP_MODE_Zephyr)

// as5047p libraries
#include "./../types/AS5047P_Types.h"

// zephyr libraries
#include <kernel.h>

// log
LOG_MODULE_REGISTER(as5047p_lib_spi, LOG_LEVEL_INF);

namespace AS5047P_ComBackend {

    AS5047P_SPI_Zephyr::AS5047P_SPI_Zephyr(const struct spi_dt_spec *spiDevSpec) {

        _spiDevSpec = spiDevSpec;
    }

    void AS5047P_SPI_Zephyr::init() {

        LOG_INF("Initializing AS5047P SPI");

        if (_spiDev == nullptr) {
            _spiDev = device_get_binding(_spiDevName);
            if (_spiDev == nullptr) {
                LOG_ERR("AS5047P SPI device binding not available!");
                return;
            }
        }

        if (!device_is_ready(_spiDev)) {
            LOG_ERR("AS5047P SPI not ready!");
            return;
        }

        LOG_INF("AS5047P SPI initialization done!");

    }

    void AS5047P_SPI_Zephyr::write(const uint16_t regAddress, const uint16_t data) const {

        int32_t error = 0;

        // define tx buffer
        static uint16_t txBuffer[1] = {0};
        const struct spi_buf txBuf = {
                .buf = txBuffer,
                .len = sizeof(txBuffer)
        };
        const struct spi_buf_set tx = {
                .buffers = &txBuf,
                .count = 1
        };

        // set register address
        txBuffer[0] = regAddress;
        error = spi_write_dt(to_spi_dt_spec(_spiDev), &tx);
        if (error != 0) {
            LOG_ERR("AS5047P SPI error while sending the register address!");
            return;
        }
        // @ToDo: thread sleep?
        k_busy_wait(K_NSEC(100));

        // write data
        txBuffer[0] = data;
        error = spi_write_dt(to_spi_dt_spec(_spiDev), &tx);
        if (error != 0) {
            LOG_ERR("AS5047P SPI error while sending the register data!");
            return;
        }
        // @ToDo: thread sleep?
        k_busy_wait(K_NSEC(100));

    }

    uint16_t AS5047P_SPI_Zephyr::read(const uint16_t regAddress) const {

        int32_t error = 0;

        // define tx & rx buffer
        static uint16_t txBuffer[1] = {0};
        static uint16_t rxBuffer[1] = {0};
        const struct spi_buf txBuf = {
                .buf = txBuffer,
                .len = sizeof(txBuffer)
        };
        const struct spi_buf rxBuf = {
                .buf = rxBuffer,
                .len = sizeof(rxBuffer)
        };
        const struct spi_buf_set tx = {
                .buffers = &txBuf,
                .count = 1
        };
        const struct spi_buf_set rx = {
                .buffers = &rxBuf,
                .count = 1
        };

        // set register address
        txBuffer[0] = regAddress;
        error = spi_write_dt(to_spi_dt_spec(_spiDev), &tx);
        if (error != 0) {
            LOG_ERR("AS5047P SPI error while sending the register address!");
            return 0;
        }
        // @ToDo: thread sleep?
        k_busy_wait(K_NSEC(100));

        // write nop & reading data
        static AS5047P_Types::SPI_Command_Frame_t nopFrame(AS5047P_Types::NOP_t::REG_ADDRESS, AS5047P_TYPES_READ_CMD);
        txBuffer[0] = nopFrame.data.raw;
        error = spi_transceive_dt(to_spi_dt_spec(_spiDev), &tx, &rx);
        if (error != 0) {
            LOG_ERR("AS5047P SPI error while transceiving the register data!");
            return 0;
        }
        // @ToDo: thread sleep?
        k_busy_wait(K_NSEC(100));

        return rxBuffer[0];
    }
}

#endif // AS5047P_OP_MODE_Zephyr
