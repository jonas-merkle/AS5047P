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
#define AS5047P_SPI_USE_100NS_NOP_DELAY

/**
 * @brief Uncomment this to init the spi bus every time when a communication is startet.
 * 
 * This can become usefull if multiple libraries are using the spi bus with different settings.
 * 
 */
//#define AS5047P_SPI_INIT_ON_COM_ENAB

#endif // AS5047P_Settings_h