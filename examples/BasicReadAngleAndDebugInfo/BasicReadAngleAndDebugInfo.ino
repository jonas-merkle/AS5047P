/**
 * @file BasicReadAngleAndDebugInfo.ino
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This is a basic example program to read the angle position and debug information from a AS5047 rotary encoder.
 *        The angle postion and debug information gets updated and printed to the serial consol once a second. 
 * @version 2.1.5
 * @date 2021-04-10
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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // initialize the AS5047P sensor and hold if sensor can't be initialized.
  Serial.println(F("Initializing AS5047P sensor..."));
  while (!as5047p.initSPI()) {
    Serial.println(F("Can't connect to the AS5047P sensor! Please check the connection..."));
    delay(5000);
  }
  Serial.println(F("Initializing AS5047P sensor... Done!"));
}

// arduino loop routine
void loop() {

  // read the sensor
  digitalWrite(LED_PIN, HIGH);                    // activate the led.
  Serial.print("Angle: ");                        // print some text to the serial consol.
  Serial.println(as5047p.readAngleDegree());      // read the angle value from the AS5047P sensor an print it to the serial consol.
  #ifdef ARDUINO_ARCH_SAMD
  std::string s = as5047p.readStatusAsStdString();      // get the string containing the debug information.
  for(uint16_t i = 0; i < s.size(); i++) {              // printing the string character by character
    Serial.print(s[i]); 
  }
  Serial.println("");
  #else
  Serial.println(as5047p.readStatusAsArduinoString());  // get the string containing the debug information and print it.
  Serial.println("");
  #endif
  delay(500);                                     // wait for 500 milli seconds.

  // wait
  digitalWrite(LED_PIN, LOW);                     // deactivate the led.
  delay(500);                                     // wait for 500 milli seconds.
}