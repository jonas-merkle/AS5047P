# AS5047P - Arduino Library

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/master?label=build%20master) ![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/develop?label=build%20develop) ![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P) ![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P)

## Tl;Dr

An Arduino library for the AS5047P high-resolution rotary position sensor.

## Contents

- [AS5047P - Arduino Library](#as5047p---arduino-library)
  - [Tl;Dr](#tldr)
  - [Contents](#contents)
  - [Documentation !GitHub deployments](#documentation-)
  - [Project Status & ToDo's](#project-status--todos)
  - [About the AS5047P](#about-the-as5047p)

## Documentation ![GitHub deployments](https://img.shields.io/github/deployments/jonas-merkle/AS5047P/github-pages)

| Branch | Link |
|--------|------|
| Master | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/master/html/index.html) |
| Develop | [Documentation](https://jonas-merkle.github.io/AS5047P/docs/develop/html/index.html) |

## Project Status & ToDo's

:heavy_check_mark: Read / Write functions for all registers implemented.

:heavy_check_mark: Doxygen comments added.

:heavy_check_mark: [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0

:heavy_check_mark: [keywords.txt](keywords.txt) updated for main library functions.

:heavy_check_mark: Adding a CI pipline.

:heavy_check_mark: Build & deploy doxygen documentation for the library.

:x: [keywords.txt](keywords.txt) updated for all library functions.

:x: Parity check on incoming data.

:x: Sensor status output as string.

:x: [Readme.md](README.md) update.

:x: Additional examples.

:x: Implementation & test of programming the one time programmable register of the AS5047P.

## About the AS5047P

The AS5047P datesheet can be found [here](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8).
