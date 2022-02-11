# AS5047P - Arduino Library

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/master?label=build%20master) ![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/develop?label=build%20develop) ![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P) ![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P) ![GitHub issues](https://img.shields.io/github/issues/jonas-merkle/AS5047P) ![GitHub pull requests](https://img.shields.io/github/issues-pr/jonas-merkle/AS5047P) ![Maintenance](https://img.shields.io/maintenance/yes/2022)

## tl;dr

**An Arduino library for the AS5047P high-resolution rotary position sensor. Supporting also the following sensor types: AS5047D, AS5147, AS5147P, AS5247**

## Contents

- [AS5047P - Arduino Library](#as5047p---arduino-library)
  - [tl;dr](#tldr)
  - [Contents](#contents)
  - [Supported Sensors](#supported-sensors)
  - [Documentation](#documentation)
  - [How to install this library](#how-to-install-this-library)
    - [Install the library via the Arduino Library Manager](#install-the-library-via-the-arduino-library-manager)
    - [Manually install a Arduino library](#manually-install-a-arduino-library)
    - [Install the library via the PlattformIO Library Manager](#install-the-library-via-the-plattformio-library-manager)
  - [How to connect the AS5047P to your Arduino](#how-to-connect-the-as5047p-to-your-arduino)
    - [Connect to an Arduino Uno](#connect-to-an-arduino-uno)
    - [Connect to an Arduino Mega](#connect-to-an-arduino-mega)
    - [Connect to an Adafruit Feather M0](#connect-to-an-adafruit-feather-m0)
    - [Connect to Teensy Board](#connect-to-teensy-board)
      - [Connect to a Teensy 3.5](#connect-to-a-teensy-35)
      - [Connect to a Teensy 3.6](#connect-to-a-teensy-36)
      - [Connect to a Teensy 4.0](#connect-to-a-teensy-40)
      - [Connect to a Teensy 4.1](#connect-to-a-teensy-41)
  - [Project Status & ToDo's](#project-status--todos)

## Supported Sensors

The following sensors of the **AS5x47** series of rotary potion sensors are supported by this library:

- [**AS5047P**](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8)
- [**AS5047D**](https://ams.com/documents/20143/36005/AS5047D_DS000394_2-00.pdf/c7225c06-112f-82c5-4471-17a2711a7f0e)
- [**AS5147**](https://ams.com/documents/20143/36005/AS5147_DS000307_2-00.pdf/6921a55b-7cba-bf20-78c0-660d62bd0a5b)
- [**AS5147P**](https://ams.com/documents/20143/36005/AS5147P_DS000328_2-00.pdf/847d41be-7afa-94ad-98c2-8617a5df5b6f)
- [**AS5247**](https://ams.com/documents/20143/36005/AS5247_DS000354_2-00.pdf/db765ebd-b442-4d00-8343-d4f95a847995)

You can get the **AS5047P** sensor preinstalled on a breakout board [here](https://ams.com/as5047padapterboard).

Not supported are the following sensors:

- [AS5047U](https://ams.com/documents/20143/36005/AS5047U_DS000637_1-00.pdf/8639418f-6c3a-1624-4e6f-18f52c962099)
- [AS5147U](https://ams.com/documents/20143/36005/AS5147U_AS5247U_DS000639_4-00.pdf/1141a423-d438-ff83-df65-0adc533d6801)
- [AS5247U](https://ams.com/documents/20143/36005/AS5147U_AS5247U_DS000639_4-00.pdf/1141a423-d438-ff83-df65-0adc533d6801)

## Documentation

Documentation Deployment Status: ![GitHub deployments](https://img.shields.io/github/deployments/jonas-merkle/AS5047P/github-pages)

| Branch | Link |
|--------|------|
| Master | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html) |
| Develop | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html) |

## How to install this library

### Install the library via the Arduino Library Manager

The easiest way to install this library is to use the build in Arduino Library Manager. Just search for `AS5047P` an install the latest version available. You can also upgrade the library to the newest release via the Arduino Library Manager. For detailed infomation please read the section `Using the Library Manager` of [this](https://www.arduino.cc/en/guide/libraries) tutorial. (Pleas keep in mind you need at least version 1.6.2 of the Arduino IDE in order to use the Arduino Library Manager)

### Manually install a Arduino library

You can download the latest version of this library [here](https://github.com/jonas-merkle/AS5047P/releases) as a zip file and follow the section `Importing a .zip Library` or `Manual installation` of [this](https://www.arduino.cc/en/guide/libraries) tutorial about `How to Install a Library`.

### Install the library via the PlattformIO Library Manager

You can find this library [here](https://platformio.org/lib/show/12035/AS5047P) in the PlattformIO Library Manager. To add this library to your plattformIO project you can either use the library manager ui and search for this library or you can use the following platform io cli command: `pio lib install "jonas-merkle/AS5047P"`

## How to connect the AS5047P to your Arduino

### Connect to an [Arduino Uno](https://store.arduino.cc/arduino-uno-rev3)

| AS5047P Pin | Arduino Uno Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 5V | - |
| VDD3V| NC | - |
| MOSI | MOSI (Pin: 11) | - |
| MISO | MISO (Pin: 12) | - |
| CLK | SCK (Pin: 13) | - |
| CSn | 9 | Can be any unused digital pin on the arduino as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

### Connect to an [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3)

| AS5047P Pin | Arduino Mega Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 5V | - |
| VDD3V| NC | - |
| MOSI | MOSI (Pin: 51) | - |
| MISO | MISO (Pin: 50) | - |
| CLK | SCK (Pin: 52) | - |
| CSn | 9 | Can be any unused digital pin on the arduino as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

### Connect to an [Adafruit Feather M0](https://www.adafruit.com/product/2772)

| AS5047P Pin | Adafruit Feather M0 Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI | - |
| MISO | MISO | - |
| CLK | SCK | - |
| CSn | 9 | Can be any unused digital pin on the arduino as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

**Please note that the sensor can no longer be operated with 5V, but must be operated with 3.3V, otherwise there is a risk of damaging the Adafruit Feather M0 board!**

### Connect to [Teensy Board](https://www.pjrc.com/store/index.html)

#### Connect to a [Teensy 3.5](https://www.pjrc.com/store/teensy35.html)

| AS5047P Pin | Teensy Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI0 (Pin: 11) | - |
| MISO | MISO0 (Pin: 12) | - |
| CLK | SCK0 (Pin: 13) | - |
| CSn | CS0 (Pin: 10) | Can be any unused digital pin on the teenys as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

**Please note that the sensor can no longer be operated with 5V, but must be operated with 3.3V, otherwise there is a risk of damaging the Teensy board!**

#### Connect to a [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)

| AS5047P Pin | Teensy Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI0 (Pin: 11) | - |
| MISO | MISO0 (Pin: 12) | - |
| CLK | SCK0 (Pin: 13) | - |
| CSn | CS0 (Pin: 10) | Can be any unused digital pin on the teenys as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

**Please note that the sensor can no longer be operated with 5V, but must be operated with 3.3V, otherwise there is a risk of damaging the Teensy board!**

#### Connect to a [Teensy 4.0](https://www.pjrc.com/store/teensy40.html)

| AS5047P Pin | Teensy Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI (Pin: 11) | - |
| MISO | MISO (Pin: 12) | - |
| CLK | SCK (Pin: 13) | - |
| CSn | CS (Pin: 10) | Can be any unused digital pin on the teenys as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

**Please note that the sensor can no longer be operated with 5V, but must be operated with 3.3V, otherwise there is a risk of damaging the Teensy board!**

#### Connect to a [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)

| AS5047P Pin | Teensy Pin | Comment |
|:-----------:|:-----------:|:--------|
| GND | GND | - |
| VDD | 3V | - |
| VDD3V| 3V | - |
| MOSI | MOSI (Pin: 11) | - |
| MISO | MISO (Pin: 12) | - |
| CLK | SCK (Pin: 13) | - |
| CSn | CS (Pin: 10) | Can be any unused digital pin on the teenys as long as it's configured here `AS5047P as5047p(<ChipSelectPort>);` |

**Please note that the sensor can no longer be operated with 5V, but must be operated with 3.3V, otherwise there is a risk of damaging the Teensy board!**

## Project Status & ToDo's

| Status | Task / ToDo |
|:------:|:------------|
|   ✅   | Read functions for all registers implemented. |
|   ✅   | Doxygen comments added. |
|   ✅   | [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [BasicReadAngleAndDebugInfo.ino](examples/BasicReadAngleAndDebugInfo/BasicReadAngleAndDebugInfo.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [PrintAllSettings.ino](examples/PrintAllSettings/PrintAllSettings.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | Adding a CI pipline. |
|   ✅   | Build & deploy doxygen documentation for the library. |
|   ✅   | Sensor status output as string. |
|   ✅   | [keywords.txt](keywords.txt) updated for main library functions. |
|   ✅   | Switch to unions... |
|   ✅   | Write functions for all registers implemented. |
|   ✅   | Parity check on incoming data. |
|   ✅   | Improve initSPI() |
|   ✅   | ToString() for Error_t |
|   ✅   | Adding Library to Arduino Library Manager 🥳 |
|   ✅   | Adding Library to PlattformIO Library Manager 🥳 |
|   ✅   | Documentation update.|
|   ✅   | [keywords.txt](keywords.txt) updated for all library functions. |
|   🚧   | [Readme.md](README.md) update.|
|   🚧   | Test of all wirte functions |
|   🚧   | Test of all read functions |
|   ❌   | Porting the library to be compatible with the STM32 HAL |
|   ❌   | Additional examples. |
|   ❌   | Unit Tests?! |
|   ❌   | Implementation & test of programming the one time programmable register of the AS5047P. |
