# AS5047P - Arduino Library

![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI.yml?branch=master&label=build%20master) ![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI.yml?branch=develop&label=build%20develop) ![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P) ![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P) ![GitHub issues](https://img.shields.io/github/issues/jonas-merkle/AS5047P) ![GitHub pull requests](https://img.shields.io/github/issues-pr/jonas-merkle/AS5047P) ![Maintenance](https://img.shields.io/maintenance/yes/2024)

## Overview

The **AS5047P Arduino Library** provides an easy way to interface with the AS5047P high-resolution rotary position sensor, as well as several other sensors from the AS5x47 series. This library supports reading the angular position and other diagnostic information using SPI communication, and is designed to work with a variety of microcontrollers, including Arduino, Adafruit Feather, and Teensy boards.

The AS5047P sensor provides high-resolution rotary position sensing with a 14-bit resolution, making it ideal for applications that require accurate angular measurements, such as robotics, motor control, and industrial automation.

## Features

- Support for multiple sensor models: AS5047P, AS5047D, AS5147, AS5147P, and AS5247.
- Easy-to-use interface for reading angular position.
- SPI communication for reliable data transmission.
- Example sketches to help get started quickly.
- Compatibility with Arduino, Adafruit Feather, Teensy, and other boards.

## Contents

- [AS5047P - Arduino Library](#as5047p---arduino-library)
  - [Overview](#overview)
  - [Features](#features)
  - [Contents](#contents)
  - [Supported Sensors](#supported-sensors)
  - [Documentation](#documentation)
  - [Installation Instructions](#installation-instructions)
    - [Install via Arduino Library Manager](#install-via-arduino-library-manager)
    - [Manual Installation](#manual-installation)
    - [Install via PlatformIO Library Manager](#install-via-platformio-library-manager)
  - [Connecting the AS5047P to Your Arduino](#connecting-the-as5047p-to-your-arduino)
    - [Arduino Uno](#arduino-uno)
    - [Arduino Mega](#arduino-mega)
    - [Adafruit Feather M0](#adafruit-feather-m0)
    - [Teensy Board Connections](#teensy-board-connections)
      - [Teensy 3.5](#teensy-35)
      - [Teensy 3.6](#teensy-36)
      - [Teensy 4.0](#teensy-40)
      - [Teensy 4.1](#teensy-41)
  - [Usage Guide](#usage-guide)
    - [Basic Example](#basic-example)
    - [Advanced Usage](#advanced-usage)
  - [License](#license)
  - [Project Status \& To-Do's](#project-status--to-dos)

## Supported Sensors

The following sensors of the **AS5x47** series of rotary position sensors are supported by this library:

- [**AS5047P**](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8)
- [**AS5047D**](https://ams.com/documents/20143/36005/AS5047D_DS000394_2-00.pdf/c7225c06-112f-82c5-4471-17a2711a7f0e)
- [**AS5147**](https://ams.com/documents/20143/36005/AS5147_DS000307_2-00.pdf/6921a55b-7cba-bf20-78c0-660d62bd0a5b)
- [**AS5147P**](https://ams.com/documents/20143/36005/AS5147P_DS000328_2-00.pdf/847d41be-7afa-94ad-98c2-8617a5df5b6f)
- [**AS5247**](https://ams.com/documents/20143/36005/AS5247_DS000354_2-00.pdf/db765ebd-b442-4d00-8343-d4f95a847995)

Not supported are the following sensors:

- [AS5047U](https://ams.com/documents/20143/36005/AS5047U_DS000637_1-00.pdf/8639418f-6c3a-1624-4e6f-18f52c962099)
- [AS5147U](https://ams.com/documents/20143/36005/AS5147U_AS5247U_DS000639_4-00.pdf/1141a423-d438-ff83-df65-0adc533d6801)
- [AS5247U](https://ams.com/documents/20143/36005/AS5147U_AS5247U_DS000639_4-00.pdf/1141a423-d438-ff83-df65-0adc533d6801)

## Documentation

The library documentation is deployed on GitHub Pages. For detailed reference on the API, examples, and usage guides, check the links below:

| Branch | Link |
|--------|------|
| Master | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html) |
| Develop | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html) |

## Installation Instructions

### Install via Arduino Library Manager

The easiest way to install this library is to use the built-in Arduino Library Manager:

1. Open the Arduino IDE.
2. Go to **Sketch > Include Library > Manage Libraries...**
3. In the Library Manager, type `AS5047P` in the search bar.
4. Install the latest version of the library.

You can also upgrade the library to the newest release via the Arduino Library Manager. For more information, refer to the [Arduino Libraries Guide](https://www.arduino.cc/en/guide/libraries). Note that you need at least version 1.6.2 of the Arduino IDE to use the Library Manager.

### Manual Installation

1. Download the latest version of the library from [GitHub Releases](https://github.com/jonas-merkle/AS5047P/releases).
2. Extract the downloaded ZIP file.
3. Copy the extracted folder to your Arduino libraries directory (e.g., `Documents/Arduino/libraries`).

Follow the [Arduino Libraries Guide](https://www.arduino.cc/en/guide/libraries) for more detailed instructions.

### Install via PlatformIO Library Manager

To add this library to your PlatformIO project, follow these steps:

1. Open PlatformIO IDE.
2. Search for `AS5047P` in the Library Manager UI, or run the following command in the PlatformIO CLI:
   ```
   pio lib install "jonas-merkle/AS5047P"
   ```

## Connecting the AS5047P to Your Arduino

### Arduino Uno

| AS5047P Pin | Arduino Uno Pin | Comment |
|:-----------:|:---------------:|:--------|
| GND         | GND             | Ground connection |
| VDD         | 5V              | Power supply (5V) |
| VDD3V       | NC              | Not connected     |
| MOSI        | MOSI (Pin: 11)  | SPI Data Out      |
| MISO        | MISO (Pin: 12)  | SPI Data In       |
| CLK         | SCK (Pin: 13)   | SPI Clock         |
| CSn         | 9               | Chip select (configurable pin) |

### Arduino Mega

| AS5047P Pin | Arduino Mega Pin | Comment |
|:-----------:|:----------------:|:--------|
| GND         | GND              | Ground connection |
| VDD         | 5V               | Power supply (5V) |
| VDD3V       | NC               | Not connected     |
| MOSI        | MOSI (Pin: 51)   | SPI Data Out      |
| MISO        | MISO (Pin: 50)   | SPI Data In       |
| CLK         | SCK (Pin: 52)    | SPI Clock         |
| CSn         | 9                | Chip select (configurable pin) |

### Adafruit Feather M0

| AS5047P Pin | Adafruit Feather M0 Pin | Comment |
|:-----------:|:-----------------------:|:--------|
| GND         | GND                     | Ground connection |
| VDD         | 3V                      | Power supply (3.3V) |
| VDD3V       | 3V                      | Power supply (3.3V) |
| MOSI        | MOSI                    | SPI Data Out       |
| MISO        | MISO                    | SPI Data In        |
| CLK         | SCK                     | SPI Clock          |
| CSn         | 9                       | Chip select (configurable pin) |

**Warning: Ensure the sensor is powered with 3.3V to avoid damage to the Adafruit Feather M0 board.**

### Teensy Board Connections

#### Teensy 3.5

| AS5047P Pin | Teensy Pin      | Comment |
|:-----------:|:---------------:|:--------|
| GND         | GND             | Ground connection |
| VDD         | 3V              | Power supply (3.3V) |
| VDD3V       | 3V              | Power supply (3.3V) |
| MOSI        | MOSI0 (Pin: 11) | SPI Data Out       |
| MISO        | MISO0 (Pin: 12) | SPI Data In        |
| CLK         | SCK0 (Pin: 13)  | SPI Clock          |
| CSn         | CS0 (Pin: 10)   | Chip select (configurable pin) |

**Warning: Ensure the sensor is powered with 3.3V to avoid damage to the Teensy board.**

#### Teensy 3.6

| AS5047P Pin | Teensy Pin      | Comment |
|:-----------:|:---------------:|:--------|
| GND         | GND             | Ground connection |
| VDD         | 3V              | Power supply (3.3V) |
| VDD3V       | 3V              | Power supply (3.3V) |
| MOSI        | MOSI0 (Pin: 11) | SPI Data Out       |
| MISO        | MISO0 (Pin: 12) | SPI Data In        |
| CLK         | SCK0 (Pin: 13)  | SPI Clock          |
| CSn         | CS0 (Pin: 10)   | Chip select (configurable pin) |

**Warning: Ensure the sensor is powered with 3.3V to avoid damage to the Teensy board.**

#### Teensy 4.0

| AS5047P Pin | Teensy Pin      | Comment |
|:-----------:|:---------------:|:--------|
| GND         | GND             | Ground connection |
| VDD         | 3V              | Power supply (3.3V) |
| VDD3V       | 3V              | Power supply (3.3V) |
| MOSI        | MOSI (Pin: 11)  | SPI Data Out       |
| MISO        | MISO (Pin: 12)  | SPI Data In        |
| CLK         | SCK (Pin: 13)   | SPI Clock          |
| CSn         | CS (Pin: 10)    | Chip select (configurable pin) |

**Warning: Ensure the sensor is powered with 3.3V to avoid damage to the Teensy board.**

#### Teensy 4.1

| AS5047P Pin | Teensy Pin      | Comment |
|:-----------:|:---------------:|:--------|
| GND         | GND             | Ground connection |
| VDD         | 3V              | Power supply (3.3V) |
| VDD3V       | 3V              | Power supply (3.3V) |
| MOSI        | MOSI (Pin: 11)  | SPI Data Out       |
| MISO        | MISO (Pin: 12)  | SPI Data In        |
| CLK         | SCK (Pin: 13)   | SPI Clock          |
| CSn         | CS (Pin: 10)    | Chip select (configurable pin) |

**Warning: Ensure the sensor is powered with 3.3V to avoid damage to the Teensy board.**

## Usage Guide

### Basic Example

The following example demonstrates how to read the angle from the AS5047P sensor using an Arduino board.

```cpp
#include <SPI.h>
#include <AS5047P.h>

AS5047P as5047p(9); // Chip select pin 9

void setup() {
  Serial.begin(9600);
  SPI.begin();
  as5047p.initSPI();
}

void loop() {
  uint16_t angle = as5047p.readAngle();
  Serial.print("Angle: ");
  Serial.println(angle);
  delay(500);
}
```

### Advanced Usage

The library provides several functions for advanced interaction with the sensor, including reading diagnostic registers and status flags. Refer to the [documentation](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html) for a complete API reference and usage examples.

## License

This project is licensed under the **GNU General Public License v3.0**. You can find the full license text in the [LICENSE](./LICENSE) file or visit the [GPL v3.0 License page](https://www.gnu.org/licenses/gpl-3.0.en.html) for more information.

## Project Status & To-Do's

| Status | Task / ToDo |
|:------:|:------------|
|   ✅   | Read functions for all registers implemented. |
|   ✅   | Doxygen comments added. |
|   ✅   | [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [BasicReadAngleAndDebugInfo.ino](examples/BasicReadAngleAndDebugInfo/BasicReadAngleAndDebugInfo.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [PrintAllSettings.ino](examples/PrintAllSettings/PrintAllSettings.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | Adding a CI pipeline. |
|   ✅   | Build & deploy Doxygen documentation for the library. |
|   ✅   | Sensor status output as string. |
|   ✅   | [keywords.txt](keywords.txt) updated for main library functions. |
|   ✅   | Switch to unions... |
|   ✅   | Write functions for all registers implemented. |
|   ✅   | Parity check on incoming data. |
|   ✅   | Improve initSPI() |
|   ✅   | ToString() for Error_t |
|   ✅   | Adding Library to Arduino Library Manager 🥳 |
|   ✅   | Adding Library to PlatformIO Library Manager 🥳 |
|   ✅   | Documentation update. |
|   ✅   | [keywords.txt](keywords.txt) updated for all library functions. |
|   🚧   | [Readme.md](README.md) update. |
|   🚧   | Test of all write functions |
|   🚧   | Test of all read functions |
|   ❌   | Porting the library to be compatible with the STM32 HAL |
|   ❌   | Additional examples. |
|   ❌   | Unit Tests?! |
|   ❌   | Implementation & test of programming the one-time programmable register of the AS5047P. |

