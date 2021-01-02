# AS5047P - Arduino Library

## Tl;Dr

An Arduino library for the AS5047P high-resolution rotary position sensor.

## Contents

- [AS5047P - Arduino Library](#as5047p---arduino-library)
  - [Tl;Dr](#tldr)
  - [Contents](#contents)
  - [Project Status & ToDo's](#project-status--todos)
  - [About the AS5047P](#about-the-as5047p)

## Project Status & ToDo's

:heavy_check_mark: Read / Write functions for all registers implemented.

:heavy_check_mark: Doxygen comments added.

:heavy_check_mark: [BasicReadAngle.ino](examples/BasicReadAngle/BasicReadAngle.ino) successfully tested on an Arduino Mega & Adafruit Feather M0

:heavy_check_mark: [keywords.txt](keywords.txt) updated for main library functions.

:x: [keywords.txt](keywords.txt) updated for all library functions.

:x: Parity check on incoming data.

:x: Sensor status output as string.

:x: Adding a CI pipline.

:x: Build & deploy doxygen documentation for the library.

:x: [Readme.md](README.md) update.

:x: Additional examples.

:x: Implementation & test of programming the one time programmable register of the AS5047P.

## About the AS5047P

The AS5047P datesheet can be found [here](https://ams.com/documents/20143/36005/AS5047P_DS000324_2-00.pdf/a7d44138-51f1-2f6e-c8b6-2577b369ace8).
