# GController: ESP32-S3-Based Controller System

## Overview
The **GController** is a feature-rich embedded system designed using the ESP32-S3 microcontroller. It integrates multiple peripherals, sensors, and interfaces, making it an ideal choice for industrial automation, IoT, and control system applications. This repository documents the hardware design, PCB layout, and related details for the GController system.

---

## Hardware Design
### PCB Specifications
- **Multi-layer PCB**:
  - Dedicated power and ground planes for noise reduction
- **Connector Layouts**:
  - Clearly marked connections for peripherals, power, and sensors
  - Separate connectors for high-current and low-current devices
- **Thermal Considerations**:
  - Adequate spacing and heat management for power MOSFETs and regulators

### Key ICs and Components
- ESP32-S3-WROOM-1U-N16R8
- ADM7172 LDO (3.3V regulator)
- XL4015 and XL1507 Buck Converters
- LM74500 Reverse Polarity Protection
- MCP23017 GPIO Expander
- SP485EEN RS485 Transceiver
- GP8413 DAC
- ADS1115 ADC

---

## Documentation
- [Schematic](./Documents/Schematic.pdf)
- [PCB Layout](./Documents/PCB.pdf)

Repository updated successfully.
