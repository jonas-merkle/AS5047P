/**
 * @file PrintAllSettings.ino
 * @author Jonas Merkle [JJM]
 * @email jonas@jjm.one
 * @brief Example program demonstrating how to read and print all configuration
 *        register settings from an AS5047P rotary encoder using SPI.
 *
 *        The program continuously reads both SETTINGS1 and SETTINGS2 registers
 *        from the AS5047P sensor and prints each bit field to the serial console
 *        every five seconds.
 *
 * @version 3.0.1
 * @date 2026-01-18
 *
 * @copyright
 * Copyright (c) 2026 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 *
 * @see https://github.com/jonas-merkle/AS5047P
 */

#include <AS5047P.h> // Include the AS5047P sensor library.

// Define the onboard LED pin (usually pin 13 on most Arduino boards).
#define LED_PIN 13

// Define the chip select (CS) pin used for SPI communication.
#define AS5047P_CHIP_SELECT_PORT 9

// Define the SPI bus speed (in Hz).
#define AS5047P_CUSTOM_SPI_BUS_SPEED 100000

// Create an instance of the AS5047P sensor.
AS5047P as5047p(AS5047P_CHIP_SELECT_PORT, AS5047P_CUSTOM_SPI_BUS_SPEED);

/**
 * @brief Arduino setup function.
 *
 * Initializes serial communication, configures the LED pin,
 * and establishes communication with the AS5047P sensor.
 */
void setup()
{
  // Configure the LED pin as an output.
  pinMode(LED_PIN, OUTPUT);

  // Start serial communication at 115200 baud.
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10); // Wait for Serial to be ready
  }
  Serial.println(F("Initializing AS5047P sensor..."));

  // Attempt to initialize the AS5047P sensor.
  // Retry every 5 seconds if initialization fails.
  while (!as5047p.initSPI())
  {
    Serial.println(F("Error: Unable to connect to AS5047P sensor!"));
    Serial.println(F("Please check wiring and power connections."));
    delay(5000);
  }

  Serial.println(F("AS5047P sensor successfully initialized."));
}

/**
 * @brief Arduino loop function.
 *
 * Reads the configuration registers SETTINGS1 and SETTINGS2 from the AS5047P,
 * then prints the individual bit fields to the serial console.
 */
void loop()
{
  // Read the configuration registers from the sensor.
  auto settings1 = as5047p.read_SETTINGS1();
  auto settings2 = as5047p.read_SETTINGS2();

  // Print SETTINGS1 register values.
  Serial.println(F("\n--- SETTINGS1 ---"));
  Serial.print(F("FactorySetting: "));
  Serial.println(settings1.data.values.FactorySetting);
  Serial.print(F("NOISESET:       "));
  Serial.println(settings1.data.values.NOISESET);
  Serial.print(F("DIR:            "));
  Serial.println(settings1.data.values.DIR);
  Serial.print(F("UVW_ABI:        "));
  Serial.println(settings1.data.values.UVW_ABI);
  Serial.print(F("DAECDIS:        "));
  Serial.println(settings1.data.values.DAECDIS);
  Serial.print(F("ABIBIN:         "));
  Serial.println(settings1.data.values.ABIBIN);
  Serial.print(F("Dataselect:     "));
  Serial.println(settings1.data.values.Dataselect);
  Serial.print(F("PWMon:          "));
  Serial.println(settings1.data.values.PWMon);

  // Print SETTINGS2 register values.
  Serial.println(F("\n--- SETTINGS2 ---"));
  Serial.print(F("UVWPP:          "));
  Serial.println(settings2.data.values.UVWPP);
  Serial.print(F("HYS:            "));
  Serial.println(settings2.data.values.HYS);
  Serial.print(F("ABIRES:         "));
  Serial.println(settings2.data.values.ABIRES);

  // Add an empty line for readability and wait 5 seconds before repeating.
  Serial.println();
  delay(5000);
}
