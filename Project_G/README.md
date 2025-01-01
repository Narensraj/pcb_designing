# GController: ESP32-S3-Based Controller System

## Overview
The **GController** is a feature-rich embedded system designed using the **ESP32-S3** microcontroller. It integrates multiple peripherals, sensors, and interfaces, making it an ideal choice for industrial automation, IoT, and control system applications. This repository documents the hardware design, PCB layout, and related details for the GController system.

---

## Hardware Design

### PCB Specifications
- **Multi-layer PCB**:
  - Dedicated power and ground planes for noise reduction.
- **Connector Layouts**:
  - Clearly marked connections for peripherals, power, and sensors.
  - Separate connectors for high-current and low-current devices.
- **Thermal Considerations**:
  - Adequate spacing and heat management for power MOSFETs and regulators.

### Key ICs and Components

1. **Core Controller**:
   - **ESP32-S3-WROOM-1U-N16R8**: Dual-core processor with Wi-Fi, Bluetooth 5.0, and extensive GPIO support for SPI, I2C, UART, ADC, and DAC.  
     16 MB Flash and 8 MB PSRAM for seamless multitasking and data handling.

2. **Power Management**:
   - **XL4015**: High-efficiency buck converter for 12V output.
   - **XL1507 & B0505S**: 5V buck converter for powering isolated systems.
   - **ADM7172**: Low-dropout regulator for 3.3V output.
   - **LM74500**: Reverse polarity protection for stable operation.

3. **Communication Interfaces**:
   - **RS485** communication with **SP485EEN-L/TR** transceiver.
   - LoRa header for long-range wireless communication.
   - USB Type-C interface with ESD protection.

4. **Peripheral Interfaces**:
   - **Analog Inputs**: 4 channels (4-20mA) with **ADS1115** (16-bit ADC).
   - **Analog Outputs**: 2 channels (0-10V) driven by **GP8413** (15-bit DAC).
   - **Digital Inputs**: 6 optocoupler-based channels (EL357N), supporting 3-32V input.
   - **Digital Outputs**: 8 MOSFET-driven channels (IRF5305STRLPBF), handling 5-36V @ 5A, and 2 **ALQ105** Relay channels.

5. **Integrated Sensors and Storage**:
   - **BMP280**: Onboard temperature and pressure monitoring.
   - **DS3231 RTC**: Real-time clock for precise scheduling.
   - **Storage**:
     - **W25N01GVZEIG** SPI NAND Flash.
     - SD card slot for extended storage.

6. **User Interface**:
   - 7-inch touchscreen support with dedicated connector.
   - RGB LED indicators (WS2812B) for system status.
   - Built-in buzzer for notifications.

7. **Pilot Lamps and Headers**:
   - Pilot lamps for "Running," "Alarm," and "Stopped" statuses.
   - Dedicated headers for power, UART, and LoRa.

---

## Documentation
- [Schematic](./Documents/Schematic.pdf)
- [PCB Layout](./Documents/PCB.pdf)
