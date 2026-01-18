# AS5047P – Arduino Library

![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI.yml?branch=master&label=build%20master)
![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI.yml?branch=develop&label=build%20develop)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P)
![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P)
![GitHub issues](https://img.shields.io/github/issues/jonas-merkle/AS5047P)
![GitHub pull requests](https://img.shields.io/github/issues-pr/jonas-merkle/AS5047P)
![Maintenance](https://img.shields.io/maintenance/yes/2026)

High-level, type-safe SPI driver for **ams/TA** **AS5047P** (and compatible AS5x47 parts).
Read 14-bit angles, magnitude, and diagnostics with concise APIs—works on classic Arduino, Feather, Teensy, and other SPI-capable boards.

---

## Table of Contents

- [AS5047P – Arduino Library](#as5047p--arduino-library)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Supported Sensors](#supported-sensors)
  - [Installation](#installation)
    - [Arduino Library Manager](#arduino-library-manager)
    - [Manual](#manual)
    - [PlatformIO](#platformio)
  - [Hardware Setup](#hardware-setup)
    - [SPI Pins \& Power Notes](#spi-pins--power-notes)
    - [Quick Wiring Tables](#quick-wiring-tables)
      - [Arduino Uno](#arduino-uno)
      - [Adafruit Feather M0 (3.3 V logic)](#adafruit-feather-m0-33-v-logic)
  - [Quick Start](#quick-start)
  - [Advanced Usage](#advanced-usage)
    - [Error \& Diagnostic Handling](#error--diagnostic-handling)
    - [Low-level Register Access](#low-level-register-access)
  - [Documentation](#documentation)
  - [Troubleshooting](#troubleshooting)
  - [Project Status](#project-status)
  - [License](#license)
    - [Acknowledgements](#acknowledgements)

---

## Features

- ✅ 14-bit **angle** readout (raw or DAE-compensated)
- ✅ **Magnitude (CMAG)** & **diagnostics** (AGC, CORDIC overflow, field strength)
- ✅ Clean **C++ types** for all registers and SPI frames (with parity helpers)
- ✅ **Even parity** verification over 15 LSBs (MSB parity bit handled for you)
- ✅ Arduino-style, minimal API + detailed status strings
- ✅ Examples for quick bring-up

---

## Supported Sensors

This library targets [**AS5047P**](https://look.ams-osram.com/m/d05ee39221f9857/original/AS5047P-DS000324.pdf) and is compatible with several AS5x47 variants that share the same SPI framing:

- **AS5047P**, **AS5047D**, **AS5147**, **AS5147P**, **AS5247**

Not supported: **AS5047U**, **AS5147U**, **AS5247U** (different protocol/regs).

---

## Installation

### Arduino Library Manager

1. **Sketch → Include Library → Manage Libraries…**
2. Search **`AS5047P`**, then **Install**.

> You’ll need Arduino IDE ≥ 1.6.2 for Library Manager.

### Manual

1. Download the latest **Release** ZIP.
2. Extract to your Arduino `libraries/` folder.
3. Restart the IDE.

### PlatformIO

```sh
pio lib install "jonas-merkle/AS5047P"
```

Or add to `platformio.ini`:

```ini
lib_deps = jonas-merkle/AS5047P
```

---

## Hardware Setup

### SPI Pins & Power Notes

- **SPI mode**: `MODE1` (CPOL=0, CPHA=1), **MSB first**
- **Voltage**:

  - Many dev boards (Feather M0, Teensy 3.x/4.x) are **3.3 V only** → power sensor @ **3.3 V**
  - Classic Arduino Uno/Mega can power at **5 V**, but confirm **logic levels** and your breakout’s level shifting.

- **CS pin** defaults to **D9**, configurable in the constructor.

### Quick Wiring Tables

#### Arduino Uno

| AS5047P | Uno | Notes                      |
| ------: | :-: | -------------------------- |
|     GND | GND | Ground                     |
|     VDD | 5V  | Sensor Vcc                 |
|   VDD3V | NC  | —                          |
|    MOSI | 11  | SPI MOSI                   |
|    MISO | 12  | SPI MISO                   |
|     CLK | 13  | SPI SCK                    |
|     CSn |  9  | Chip Select (configurable) |

#### Adafruit Feather M0 (3.3 V logic)

| AS5047P | Feather M0 | Notes                             |
| ------: | :--------: | --------------------------------- |
|     GND |    GND     | Ground                            |
|     VDD |     3V     | **3.3 V only**                    |
|   VDD3V |     3V     | Tie to 3.3 V if required by board |
|    MOSI |    MOSI    | SPI MOSI                          |
|    MISO |    MISO    | SPI MISO                          |
|     CLK |    SCK     | SPI SCK                           |
|     CSn |     9      | Chip Select (configurable)        |

> ⚠️ **3.3 V ONLY** on Feather/Teensy. Do **not** feed 5 V.

Teensy 3.5/3.6/4.0/4.1 use their standard SPI pins (MOSI/MISO/SCK) and a free GPIO for CS (e.g., 10). Power @ **3.3 V**.

---

## Quick Start

```cpp
#include <SPI.h>
#include <AS5047P.h>

// CS pin 9, SPI speed default from library header (can pass a custom speed)
AS5047P as5047p(9);

void setup() {
  Serial.begin(115200);
  // Initialize SPI via library and verify connectivity
  if (!as5047p.initSPI()) {
    Serial.println("AS5047P init failed. Check wiring and power.");
    while (true) { delay(1000); }
  }
}

void loop() {
  // Read 14-bit angle (degrees) with DAE compensation
  float deg = as5047p.readAngleDegree(true);
  Serial.print("Angle (deg): ");
  Serial.println(deg, 3);

  // Read magnitude
  uint16_t mag = as5047p.readMagnitude();
  Serial.print("Magnitude: ");
  Serial.println(mag);

  delay(500);
}
```

---

## Advanced Usage

### Error & Diagnostic Handling

You can request parity verification and collect communication/sensor diagnostics on each read:

```cpp
AS5047P_Types::ERROR_t err;
float deg = as5047p.readAngleDegree(
  /*withDAEC*/ true,
  /*errorOut*/ &err,
  /*verifyParity*/ true,
  /*checkForComError*/ true,
  /*checkForSensorError*/ true
);

if (!err.noError()) {
  Serial.println(err.toArduinoString()); // nicely formatted error report
}
```

You can also dump a combined status block:

```cpp
Serial.println(as5047p.readStatusAsArduinoString());
```

### Low-level Register Access

Typed wrappers let you work with registers directly:

```cpp
// Read DIAAGC (AGC, LF, COF, MAGH/L)
AS5047P_Types::DIAAGC_t dia = as5047p.read_DIAAGC(/*errorOut*/ nullptr, /*verifyParity*/ true);

// Write to SETTINGS1 (example: toggle DAE compensation disable bit)
AS5047P_Types::SETTINGS1_t s1 = as5047p.read_SETTINGS1();
s1.data.values.DAECDIS = 1; // disable DAE
AS5047P_Types::ERROR_t err;
bool ok = as5047p.write_SETTINGS1(&s1, &err, /*checkForComError*/ true, /*verifyWittenReg*/ true);
if (!ok) Serial.println(err.toArduinoString());
```

> Parity for frames is handled internally by the SPI layer; you can also use `AS5047P_Util::parityCheck()` if you construct frames yourself.

---

## Documentation

- **Master**: [https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html)
- **Develop**: [https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html](https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html)

Doxygen is generated from the extensively commented headers and sources.

---

## Troubleshooting

- **`initSPI()` fails**

  - Check **power** (3.3 V vs 5 V board), **common ground**, and **CS pin** number.
  - Verify **SPI mode 1** (the library sets this), and that no other library reconfigures SPI mid-flight.
  - If multiple SPI users exist, consider enabling `AS5047P_SPI_ARDUINO_INIT_ON_COM_ENAB` in `util/AS5047P_Settings.h`.

- **Random read errors**

  - Try disabling the ~100 ns NOP delay (`AS5047P_SPI_ARDUINO_USE_100NS_NOP_DELAY`) or vice versa depending on your MCU clock.
  - Shorten wires; keep SPI lines tight and add GND reference near sensor.

- **Angles look noisy**

  - Check **magnet distance/centering** (MAGH/MAGL flags, AGC value in `DIAAGC`).
  - Consider using **DAE-compensated** angle (`readAngleDegree(true)`).

---

## Project Status

- ✅ Read/write APIs for all relevant registers
- ✅ Parity checking & formatted error/status strings
- ✅ CI, Doxygen docs, Arduino & PlatformIO registry
- 🚧 Broader write-path testing across MCUs/clock rates
- 🚧 More examples (DAE tuning, ABI/U VW config)
- ❌ STM32 HAL backend (PRs welcome)

---

## License

Licensed under **GNU GPLv3**. See [LICENSE](./LICENSE).

---

### Acknowledgements

Thanks to contributors and users testing across different boards. Issues and PRs are welcome!
