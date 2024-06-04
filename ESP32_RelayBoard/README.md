# ESP32 Relay Board

## Overview

This repository contains the design and documentation for an ESP32 relay board created using EasyEDA. It comprises various components such as AC to DC converter, voltage regulator, ESP32 microcontroller, USB to UART interface, relay control, RGB LED control, and miscellaneous components.

## Components

### AC to DC Converter

- **Module:** HLK-PM01
- **Output:** 5V from AC mains

### Voltage Regulator (AMS1117-3.3)

- **Function:** Converts 5V to 3.3V
- **Usage:** Provides power to the ESP32 and other 3.3V components

### Capacitors

- **Types:** Decoupling capacitors (220 µF, 10 µF, and 100 nF)
- **Purpose:** Stabilize the voltage supply around the voltage regulator

### ESP32 Microcontroller

- **Model:** ESP32-S3-WROOM-1 (U3)
- **Functionality:** Central microcontroller unit
- **Features:**
  - GPIO Connections for various components
  - Reset and Boot Buttons for manual control

### USB to UART Interface

- **Model:** CP2102-GMR (U16)
- **Functionality:** USB to UART bridge for programming and serial communication
- **Components:**
  - Includes RTS, DTR signals, and USB data lines (D+, D-)

### Relay Control

- **Relays:** ALQ105
- **Control:** GPIO pins through transistors (MMSS8050-H-TP) and optocouplers (CYPC817)
- **Supporting Components:** Transistors, resistors, and optocouplers for relay coil control and isolation

### RGB LED Control

- **LED Type:** WS2812B
- **Control:** Connected to a GPIO pin for RGB LED control

### Miscellaneous Components

- **Test Points:** Provided for 3.3V, 5V, and ground for easy debugging
- **Indicator LEDs:** With current limiting resistors to indicate power status and other signals
- **Mounting Holes:** For securing the PCB

## License

This project is licensed under no-one you can freely use the schematics and pcb layout.

And remember, when life throws you a relay, just switch it on and keep the circuit flowing! 😉🔌

