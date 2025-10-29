# Arduino BLE Smart Lock Project

This project implements a Bluetooth Low Energy (BLE) enabled smart lock system using Arduino. The system allows users to control and monitor a door lock remotely using their smartphone.

## Project Overview

The smart lock system consists of two main components:
1. An Arduino-based hardware setup with BLE capabilities
2. A servo motor mechanism for controlling the physical lock

## Hardware Requirements

- Arduino board (with BLE support)
- Servo motor
- Power supply
- Lock mechanism
- Jumper wires
- Mounting hardware

## Project Structure

```
.
├── NANO SERVO/           # Servo control implementation
│   ├── platformio.ini    # PlatformIO configuration
│   └── src/
│       └── main.cpp      # Servo control code
│
└── Techathon/           # Main BLE implementation
    ├── platformio.ini   # PlatformIO configuration
    └── src/
        └── main.cpp     # Main BLE communication code
```

## Features

- Bluetooth Low Energy (BLE) communication
- Secure authentication system
- Remote lock/unlock capability
- Battery-efficient operation
- Real-time lock status monitoring

## Setup Instructions

1. Install PlatformIO IDE (recommended) or Arduino IDE
2. Clone this repository
3. Open either the NANO SERVO or Techathon project in your IDE
4. Install required dependencies
5. Upload the code to your Arduino board

## Usage

1. Power up the Arduino device
2. Connect to the BLE device from your smartphone
3. Use the companion app to control the lock
4. Monitor lock status and battery level

## Security Considerations

- BLE communication is encrypted
- Authentication required for lock control
- Timeout features for added security
- Regular connection monitoring

## Development

This project is built using PlatformIO, which provides better dependency management and development experience compared to the standard Arduino IDE.

## Authors

Arek Plate
Paras Nijhawan
Po Han Ai
