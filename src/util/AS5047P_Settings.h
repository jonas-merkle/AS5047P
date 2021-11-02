/**
 * @file AS5047P_Settings.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This headerfile contains settings information for the AS5047P Library.
 * @version 3.0.0
 * @date 2021-20-29
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_Settings_h
#define AS5047P_Settings_h

////////////////////////////////
// Universal library settings //
////////////////////////////////

/**
 * @brief Uncomment this to use this library in the arduino mode. Default: active
 * 
 * This allows the library to be used as a normal arduino compatible library. 
 * 
 */
//#define AS5047P_OP_MODE_Arduino

/**
 * @brief Uncomment this to use this library in the zephyr mode. Default: not active 
 * 
 * THis allows the library to be used within a zephyr project.
 * 
 */
#define AS5047P_OP_MODE_Zephyr


//////////////////////////////////////////////////
// Settings for the AS5047P SPI Arduino Library //
//////////////////////////////////////////////////

#if defined(AS5047P_OP_MODE_Arduino)

/**
 * @brief Uncomment this to use the custom 100 ns delay function based on asm nop operations.
 * 
 * This minimizes the delay while communication with the AS5047P sensor but can lead to an instable communication.
 * 
 */
#define AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY

/**
 * @brief Uncomment this to init the spi bus every time when a communication is startet.
 * 
 * This can become usefull if multiple libraries are using the spi bus with different settings.
 * 
 */
//#define AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB

#endif // AS5047P_OP_MODE_Arduino

#endif // AS5047P_Settings_h