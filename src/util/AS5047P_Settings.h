/**
 * @file AS5047P_Settings.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Library-wide configuration options for the AS5047P library.
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 */

#ifndef AS5047P_Settings_h
#define AS5047P_Settings_h

//////////////////////////////////////////////////
// Settings for the AS5047P SPI Arduino Library //
//////////////////////////////////////////////////

/**
 * @brief Use a custom ~100 ns delay implemented with inline NOP instructions.
 *
 * This minimizes inter-frame gaps during communication with the AS5047P sensor,
 * but on some platforms/clock settings it may lead to *unstable* communication.
 * Disable this if you encounter sporadic read/write errors.
 */
#define AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY

/**
 * @brief Re-initialize the SPI bus for every transaction.
 *
 * Useful when multiple libraries or devices share the SPI bus with different
 * settings. This adds a bit of overhead but can improve interoperability.
 */
// #define AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB

/**
 * @brief Enable std::string-based text output helpers.
 *
 * Note: This is typically **not** supported by the classic Arduino IDE and may
 * fail to compile there. Use an alternative toolchain such as PlatformIO + VS Code.
 */
// #define AS5047P_STD_STRING_SUPPORT

/**
 * @brief ENABLE debug output via Serial.print*().
 *
 * This is only intended for library development and debugging.
 * It may significantly increase code size and slow down execution.
 */
// #define AS5047P_DEBUG_OUTPUT_ENABLE

#endif // AS5047P_Settings_h
