FOTA (Firmware Over-The-Air) Self-Programming Microcontroller Project
This project demonstrates a Firmware Over-The-Air (FOTA) system for updating the firmware of a microcontroller wirelessly. The system is built around an ARM Cortex-M4 STM32F401CC microcontroller and the ESP8266 Wi-Fi module. It checks for new firmware versions from a server and updates the microcontroller if a newer version is available. The current firmware version is stored in flash memory to ensure persistence even during power outages or resets.

Project Overview
FOTA allows devices to remotely update their firmware without requiring physical access, making it ideal for embedded systems in IoT, automotive, and industrial applications. This project performs the following tasks:

Version Checking: The microcontroller connects to a remote server and compares the available firmware version with the one currently installed.
Firmware Update: If a newer version is available, it downloads the firmware in the form of a hex file and flashes it to the microcontroller.
Persistence: The current version number is stored in flash memory to ensure that it remains even in case of power loss or system reset.
Bootloader: The system can jump from the bootloader section to the application sector once the new firmware has been successfully flashed.
Features
ESP8266 Integration: The microcontroller uses the ESP8266 Wi-Fi module to communicate with a remote server to check for new firmware and download updates.
Version Control: The current and online firmware versions are compared, ensuring that updates only happen when necessary.
Self-Programming: The microcontroller can program itself by writing the received firmware update to its own flash memory.
Persistent Storage: The current version number is stored in flash memory at a specific address so that it is not lost during resets or power outages.

##Hardware Requirements
STM32F401CC ARM Cortex-M4 microcontroller
ESP8266 Wi-Fi Module
LED (for status indication)
External power supply
Push-button for manual reset 

##Software Components
Clock Initialization: Sets up the RCC (Reset and Clock Control) for peripheral management.
Wi-Fi Connection: The ESP8266 is initialized and connects to the specified Wi-Fi network.
Server Communication: The ESP8266 communicates with a remote server to check for the latest firmware version and downloads it if needed.
Memory Management: The firmware is stored in flash memory, and the memory is managed by sector. The application sector is erased before the new firmware is written.
Jump to Application: After flashing the new firmware, the bootloader jumps to the application section.
How It Works
1. Initial Setup
The system initializes the microcontroller clock, GPIO pins for UART, and LED status indicators. The microcontroller communicates with the ESP8266 module to connect to a Wi-Fi network.

2. Checking for Updates
The microcontroller checks for firmware updates by sending an HTTP request to the server. The server contains a version file (Version.txt) that holds the latest available firmware version.
The microcontroller compares the server version with the current firmware version stored in flash memory.
3. Downloading and Flashing the Firmware
If the server has a newer version, the microcontroller sends a request to download the new firmware (Application.hex).
The firmware is received as hex records and written to flash memory using a flash driver.
4. Flash Memory Management
The application sector in the flash memory is erased before new firmware is written.
The system handles hex file parsing to ensure each record is correctly written to the appropriate flash memory location.
5. Running the Updated Firmware
Once the new firmware has been flashed, the microcontroller updates the current version in flash memory.
It then jumps to the application section of the flash and executes the new firmware.

##Project Structure
/include
   /LIB
      - BIT_MATH.h
      - STD_TYPES.h
      - ARM_Delay.h
   /MCAL
      - MRCC_Interface.h
      - MGPIO_Interface.h
      - MNVIC_Interface.h
      - MFDI_Interface.h
      - USART_INTERFACE.h
   /HAL
      - ESP8266_INTERFACE.h
   /APP
      - AHEXAPARSING_Interface.h

/src
   - main.c
##Main Functions
Fota_CheckForUpdate(): Connects to the server, retrieves the latest firmware version, and compares it with the current version stored in flash.

Fota_Update(): Downloads the new firmware (hex file) and flashes it to the microcontroller’s application sector.

App_voidToBurn(): Once the firmware update is complete, the function jumps to the new application in the microcontroller’s flash memory.

MUSART_CallBack(): Handles UART communication between the microcontroller and ESP8266. It processes incoming data, such as version information and hex file records.

##Flash Memory Mapping
Bootloader Sector: 0x08000000
Version number sector: 0x08004000
Application Sector: 0x08008000

##How to Use
Prerequisites
ARM development environment (e.g.,Eclipse, STM32CubeIDE)
Wi-Fi network credentials
Server address

##Building the Project
Clone the repository to your local machine.
Import the project into your ARM IDE (e.g.,Eclipse, STM32CubeIDE).
Modify Wi-Fi network credentials and server address
Build the project and upload it to the STM32 microcontroller using a programmer (e.g., ST-Link).

##Running the Project
Power on the microcontroller.
It will connect to the Wi-Fi network specified in the code.
The system will check for firmware updates from the specified server.
If a new update is available, it will download and flash the new firmware.
The microcontroller will automatically switch to the updated firmware after flashing.

##Future Improvements
Add encryption to the firmware update process to improve security.
Implement a rollback feature in case of a failed update.
Add support for multiple Wi-Fi networks and automatic failover.

## Video Demo on LinkeIn post
https://www.linkedin.com/posts/marwan-aboulfath_embeddedsystems-fota-iot-activity-7242167690268725249-znGK?utm_source=share&utm_medium=member_desktop
Feel free to share your thoughts and feedback on the LinkedIn post!

License
This project is licensed under the MIT License.
