/**
 * @file BasicReadAngleAndDebugInfo.ino
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Example program demonstrating how to read the angle position
 *        and diagnostic information from an AS5047P rotary encoder using SPI.
 *
 *        The program reads the current angular position and sensor status
 *        once per second, printing both to the serial console while
 *        toggling the onboard LED to indicate activity.
 *
 * @version 3.0.0
 * @date 2025-10-07
 *
 * @copyright
 * Copyright (c) 2024 Jonas Merkle.
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
 * Initializes the serial interface, configures the LED pin,
 * and initializes communication with the AS5047P sensor.
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
 * Reads the current angle and debug information from the AS5047P sensor,
 * prints both to the serial console, and toggles the LED once per second
 * to indicate system activity.
 */
void loop()
{
  // Turn the LED on to indicate a sensor reading.
  digitalWrite(LED_PIN, HIGH);

  // Read and print the angle in degrees.
  Serial.print("Angle: ");
  Serial.println(as5047p.readAngleDegree());

  // Read and print sensor diagnostic information.
  Serial.println(as5047p.readStatusAsArduinoString());

  // Print a blank line for readability.
  Serial.println();

  // Wait for 500 milliseconds.
  delay(500);

  // Turn the LED off.
  digitalWrite(LED_PIN, LOW);

  // Wait another 500 milliseconds.
  delay(500);
}
