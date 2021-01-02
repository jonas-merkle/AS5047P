# AS5047P - Arduino Library

![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/master?label=build%20master) ![GitHub Workflow Status (branch)](https://img.shields.io/github/workflow/status/jonas-merkle/AS5047P/Arduino-Library-CI/develop?label=build%20develop) ![GitHub release (latest by date)](https://img.shields.io/github/v/release/jonas-merkle/AS5047P) ![GitHub](https://img.shields.io/github/license/jonas-merkle/AS5047P) ![GitHub issues](https://img.shields.io/github/issues/jonas-merkle/AS5047P) ![GitHub pull requests](https://img.shields.io/github/issues-pr/jonas-merkle/AS5047P) ![Maintenance](https://img.shields.io/maintenance/yes/2021)

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

| Status | Task / ToDo |
|:------:|:------------|
|   ✅   | Read / Write functions for all registers implemented. |
|   ✅   | Doxygen comments added. |
|   ✅   | [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | [BasicReadAngleAndDebugInfo.ino](examples/BasicReadAngleAndDebugInfo/BasicReadAngleAndDebugInfo.ino) successfully tested on an Arduino Mega & Adafruit Feather M0 |
|   ✅   | Adding a CI pipline. |
|   ✅   | Build & deploy doxygen documentation for the library. |
|   ✅   | Sensor status output as string. |
|   ✅   | [keywords.txt](keywords.txt) updated for main library functions. |
|   🚧   | [keywords.txt](keywords.txt) updated for all library functions. |
|   🚧   | [Readme.md](README.md) update.|
|   🚧   | Parity check on incoming data. |
|   ❌   | Additional examples. |
|   ❌   | Unit Tests?! |
|   ❌   | Implementation & test of programming the one time programmable register of the AS5047P. |

## About the AS5047P

The AS5047P datesheet can be found [here](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8).
