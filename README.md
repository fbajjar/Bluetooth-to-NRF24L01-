This is a simple implementation of a bluetooth to NRF24L01 transmitter using a ESP32 DevkitC v4. 
It expects any bluepad32 compatible controller, receives the commands from it once connected, then it sends it accordingly via an NRF24L01.

**You need to include the following libraries in your IDE:**
- Bluepad32 https://bluepad32.readthedocs.io/
- RF24
- SPI

**IMPORTANT:**
- Change CE_PIN and CSN_PIN according to the pin numbers you wired for CE pin and CSN pin of NRF24L01 to your ESP32.
- Ensure the const uint8_t address defined for openWritingPipe is the SAME as the one you are going to use in openReadingPipe->The transmitter address MUST match the receiver address

**Testing Bluetooth Controller Functionality**
- If u wish to test the bluetooth controller functionality ONLY, NRF24 code will block u from debugging controller's outputs as it will get stuck on "NRF24 failed to initialize".
- Hence, a seperate .ino file labeled "Controller-Debugging" is provided for this exact purpose.
