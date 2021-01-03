# AS5047P - Arduino Library

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/master?label=build%20master) ![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/develop?label=build%20develop) ![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P) ![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P) ![GitHub issues](https://img.shields.io/github/issues/jonas-merkle/AS5047P) ![GitHub pull requests](https://img.shields.io/github/issues-pr/jonas-merkle/AS5047P) ![Maintenance](https://img.shields.io/maintenance/yes/2021)

## Tl;Dr

**An Arduino library for the AS5047P high-resolution rotary position sensor.**

## Contents

- [AS5047P - Arduino Library](#as5047p---arduino-library)
  - [Tl;Dr](#tldr)
  - [Contents](#contents)
  - [Documentation !GitHub deployments](#documentation-)
  - [How to install this library](#how-to-install-this-library)
    - [Manually install a Arduino library](#manually-install-a-arduino-library)
    - [Install the library via the Arduino Library Manager](#install-the-library-via-the-arduino-library-manager)
    - [Install the library via the PlattformIO Library Manager](#install-the-library-via-the-plattformio-library-manager)
  - [How to connect the AS5047P to your Arduino](#how-to-connect-the-as5047p-to-your-arduino)
    - [Connect to an Arduino Uno](#connect-to-an-arduino-uno)
    - [Connect to an Arduino Mega](#connect-to-an-arduino-mega)
    - [Connect to an Adafruit Feather M0](#connect-to-an-adafruit-feather-m0)
  - [Project Status & ToDo's](#project-status--todos)
  - [About the AS5047P](#about-the-as5047p)

## Documentation ![GitHub deployments](https://img.shields.io/github/deployments/jonas-merkle/AS5047P/github-pages)

| Branch | Link |
|--------|------|
| Master | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html) |
| Develop | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html) |

## How to install this library

### Manually install a Arduino library

You can download the latest version of this library [here](https://github.com/jonas-merkle/AS5047P/releases) as a zip file and use [this](https://www.arduino.cc/en/guide/libraries) tutorial to install the library.

### Install the library via the Arduino Library Manager

Sorry, this Feature is currently not supported. 😭

### Install the library via the PlattformIO Library Manager

Sorry, this Feature is currently not supported. 😭

## How to connect the AS5047P to your Arduino

### Connect to an [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3)

| AS5047P Pin | Arduino Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 5V | - |
| VDD3V| NC | - |
| MOSI | MOSI (Pin: 11) | - |
| MISO | MISO (Pin: 12) | - |
| CLK | SCK (Pin: 13) | - |
| CSn | 9 | Can be any unused digital pin on the arduino as log as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

### Connect to an [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3)

| AS5047P Pin | Arduino Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 5V | - |
| VDD3V| NC | - |
| MOSI | MOSI (Pin: 51) | - |
| MISO | MISO (Pin: 50) | - |
| CLK | SCK (Pin: 52) | - |
| CSn | 9 | Can be any unused digital pin on the arduino as log as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

### Connect to an [Adafruit Feather M0](https://www.adafruit.com/product/2772)

| AS5047P Pin | Arduino Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI | - |
| MISO | MISO | - |
| CLK | SCK | - |
| CSn | 9 | Can be any unused digital pin on the arduino as log as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

## Project Status & ToDo's

| Status | Task / ToDo |
|:------:|:------------|
|   ✅   | Read functions for all registers implemented. |
|   ✅   | Doxygen comments added. |
|   ✅   | [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [BasicReadAngleAndDebugInfo.ino](examples/BasicReadAngleAndDebugInfo/BasicReadAngleAndDebugInfo.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | Adding a CI pipline. |
|   ✅   | Build & deploy doxygen documentation for the library. |
|   ✅   | Sensor status output as string. |
|   ✅   | [keywords.txt](keywords.txt) updated for main library functions. |
|   🚧   | Write functions for all registers implemented. |
|   🚧   | [keywords.txt](keywords.txt) updated for all library functions. |
|   🚧   | [Readme.md](README.md) update.|
|   🚧   | Parity check on incoming data. |
|   🚧   | Adding Library to Arduino Library Manager |
|   🚧   | Adding Library to PlattformIO Library Manager |
|   ❌   | Switch to unions... |
|   ❌   | Additional examples. |
|   ❌   | Unit Tests?! |
|   ❌   | Implementation & test of programming the one time programmable register of the AS5047P. |

## About the AS5047P

The AS5047P datesheet can be found [here](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8).

You can get this sensor preinstalled on a breakout board [here](https://ams.com/as5047padapterboard).
