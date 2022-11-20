/**
 * @file PrintAllSettings.ino
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief This is a example prints out the settings of the AS5047P sensor.
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

  // read the settings from the sensor
  auto settings1 = as5047p.read_SETTINGS1();
  auto settings2 = as5047p.read_SETTINGS2();
  
  // print the settings
  Serial.print("SETTINGS1.values.FactorySetting: "); Serial.println(settings1.data.values.FactorySetting);
  Serial.print("SETTINGS1.values.NOISESET:       "); Serial.println(settings1.data.values.NOISESET);
  Serial.print("SETTINGS1.values.DIR:            "); Serial.println(settings1.data.values.DIR);
  Serial.print("SETTINGS1.values.UVW_ABI:        "); Serial.println(settings1.data.values.UVW_ABI);
  Serial.print("SETTINGS1.values.DAECDIS:        "); Serial.println(settings1.data.values.DAECDIS);
  Serial.print("SETTINGS1.values.ABIBIN:         "); Serial.println(settings1.data.values.ABIBIN);
  Serial.print("SETTINGS1.values.Dataselect:     "); Serial.println(settings1.data.values.Dataselect);
  Serial.print("SETTINGS1.values.PWMon:          "); Serial.println(settings1.data.values.PWMon);

  Serial.print("SETTINGS2.values.UVWPP:          "); Serial.println(settings2.data.values.UVWPP);
  Serial.print("SETTINGS2.values.HYS:            "); Serial.println(settings2.data.values.HYS);
  Serial.print("SETTINGS2.values.ABIRES:         "); Serial.println(settings2.data.values.ABIRES);

  Serial.println("");
  delay(5000);
}