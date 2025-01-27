This is a simple implementation of a bluetooth to NRF24L01 transmitter using a ESP32 DevkitC v4. 
It expects any bluepad32 compatible controller, receives the commands from it once connected, then it sends it accordingly via an NRF24L01.

# Setup
**You need to include the following libraries in your IDE:**
- Bluepad32 https://bluepad32.readthedocs.io/
- RF24
- SPI

**IMPORTANT:**
- Change CE_PIN and CSN_PIN according to the pin numbers you wired for CE pin and CSN pin of NRF24L01 to your ESP32.
- Ensure the const uint8_t address defined for openWritingPipe is the SAME as the one you are going to use in openReadingPipe->The transmitter address MUST match the receiver address

# Testing Bluetooth Controller Functionality
- If u wish to test the bluetooth controller functionality ONLY, NRF24 code will block u from debugging controller's outputs as it will get stuck on "NRF24 failed to initialize".
- Hence, a seperate .ino file labeled "Controller-Debugging" is provided for this exact purpose.

  **Troubleshooting controller connectivity**
  
- If your controller doesn't conenct automatically, it is probably trying to connect to another previous device.
- Hence, you need to force it to forget that device and be ready to pair to a new one (In this case, your ESP32)
- Follow the guides for each controller:
  - XBOX One: https://support.xbox.com/en-US/help/hardware-network/accessories/connect-and-troubleshoot-xbox-one-bluetooth-issues
  - PS5: https://www.playstation.com/en-us/support/hardware/pair-dualsense-controller-bluetooth/#:~:text=How%20to%20pair
  - PS4: https://www.playstation.com/en-us/support/hardware/ps4-pair-dualshock-4-wireless-with-pc-or-mac/#:~:text=How%20to%20pair
