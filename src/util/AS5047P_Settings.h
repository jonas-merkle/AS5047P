/**
 * @file AS5047P_Settings.h
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This headerfile contains settings information for the AS5047P Library.
 * @version 2.2.0
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 */

#ifndef AS5047P_Settings_h
#define AS5047P_Settings_h

//////////////////////////////////////////////////
// Settings for the AS5047P SPI Arduino Library //
//////////////////////////////////////////////////

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

/**
 * @brief Uncomment this to use std::string compatible text output. 
 * 
 * This way of string handling is currently not supported by the default Arduino IDE an will result in errors during compilation.
 * Pleas use an alternative IDE like PlatformIO + VSCode.
 * 
 */
//#define AS5047P_STD_STRING_SUPPORT


#endif // AS5047P_Settings_h