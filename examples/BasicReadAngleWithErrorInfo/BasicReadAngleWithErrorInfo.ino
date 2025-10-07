/**
 * @file BasicReadAngleWithErrorInfo.ino
 * @autor Jonas Merkle [JJM] (jonas@jjm.one)
 * @brief Example program demonstrating how to read the angular position
 *        from an AS5047P rotary encoder and print associated error information.
 *
 *        The program outputs the current angle and any reported error details
 *        to the serial console once per second while toggling the onboard LED.
 *
 * @version 2.3.0
 * @date 2025-10-07
 *
 * @copyright
 * Copyright (c) 2024 Jonas Merkle.
 * This project is released under the GPL-3.0 License.
 *
 * @see https://github.com/jonas-merkle/AS5047P
 */

#include <AS5047P.h> // Include the AS5047P sensor library.

// Define the onboard LED pin (usually pin 13 on many Arduino boards).
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
  Serial.println("Initializing AS5047P sensor...");

  // Attempt to initialize the AS5047P sensor.
  // Retry every 5 seconds if initialization fails.
  while (!as5047p.initSPI())
  {
    Serial.println(F("Error: Unable to connect to AS5047P sensor!"));
    Serial.println(F("Please check wiring and power connections."));
    delay(5000);
  }

  Serial.println("AS5047P sensor successfully initialized.");
}

/**
 * @brief Arduino loop function.
 *
 * Reads the current angle and associated error information from the AS5047P,
 * prints both to the serial console, and toggles the LED once per second
 * to indicate system activity.
 */
void loop()
{
  /////////////////////
  // Read the sensor //
  /////////////////////

  // Turn the LED on to indicate a sensor reading.
  digitalWrite(LED_PIN, HIGH);

  // Prepare an error object to be populated by the read operation.
  auto errorInfo = AS5047P_Types::ERROR_t();

  // Read the angle value (in degrees). This call also fills errorInfo.
  // The boolean parameters request a fresh read and enable additional checks,
  // while providing a pointer to collect error details (implementation-specific).
  float angle = as5047p.readAngleDegree(true, &errorInfo, true, true, true);

  // Print a blank line to separate readings for readability.
  Serial.println();

  // Print the angle.
  Serial.print("Angle: ");
  Serial.println(angle);

  // Print error/diagnostic information as a single Arduino-friendly string.
  Serial.println(errorInfo.toArduinoString());

  // Wait for 500 milliseconds.
  delay(500);

  //////////
  // Wait //
  //////////

  // Turn the LED off.
  digitalWrite(LED_PIN, LOW);

  // Wait another 500 milliseconds.
  delay(500);
}
