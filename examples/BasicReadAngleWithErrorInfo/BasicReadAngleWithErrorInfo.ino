/**
 * @file BasicReadAngleWithErrorInfo.ino
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This is a basic example program to read the angle position from a AS5047 rotary encoder.
 *        The angle postion gets updated and printed to the serial consol once a second.
 *        In addition to the angle value the error information gets displayed.
 * @version 2.2.0
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2021 Jonas Merkle. This project is released under the GPL-3.0 License License.
 * 
 * More Information can be found here:
 * https://github.com/jonas-merkle/AS5047P
 */

// include the library for the AS5047P sensor.
#include <AS5047P.h>

// define a led pin.
#define LED_PIN 13

// define the chip select port.
#define AS5047P_CHIP_SELECT_PORT 9 

// define the spi bus speed 
#define AS5047P_CUSTOM_SPI_BUS_SPEED 100000

// initialize a new AS5047P sensor object.
AS5047P as5047p(AS5047P_CHIP_SELECT_PORT, AS5047P_CUSTOM_SPI_BUS_SPEED);

// arduino setup routine
void setup() {

  // set the pinmode of the led pin to output.
  pinMode(LED_PIN, OUTPUT);

  // initialize the serial bus for the communication with your pc.
  Serial.begin(115200);

  // initialize the AS5047P sensor and hold if sensor can't be initialized.
  while (!as5047p.initSPI()) {
    Serial.println(F("Can't connect to the AS5047P sensor! Please check the connection..."));
    delay(5000);
  }

}

// arduino loop routine
void loop() {

  /////////////////////
  // read the sensor //
  /////////////////////
  digitalWrite(LED_PIN, HIGH);    // activate the led.

  auto errorInfo = AS5047P_Types::ERROR_t();                                    // new error object.
  float angle = as5047p.readAngleDegree(true, &errorInfo, true, true, true);    // read the angle value from the AS5047P sensor.

  Serial.println("");         // print new line.
  Serial.print("Angle: ");    // print some text to the serial consol.
  Serial.println(angle);      // print the angle value.

  Serial.println(errorInfo.toArduinoString());    // print the error infomation.
  
  delay(500);   // wait for 500 milli seconds.


  //////////
  // wait //
  //////////
  digitalWrite(LED_PIN, LOW);   // deactivate the led.
  delay(500);                   // wait for 500 milli seconds.

}