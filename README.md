This is a simple implementation of a bluetooth to NRF24L01 transmitter done with an ESP32 DevkitC v4. 
It expects any bluepad32 compatible controller, receives the commands from it once connected, then it sends it accordingly via an NRF24L01.
**You need to include the following libraries in your IDE:**
- Bluepad32 https://bluepad32.readthedocs.io/
- RF24
- SPI
**IMPORTANT:**
- Change CE_PIN and CSN_PIN according to where you wired the CE pin and CSN pin of the NRF24L01 to your ESP32.
- Ensure the const uint8_t address defined for openWritingPipe is the SAME as the one you are going to use in openReadingPipe->The transmitter address MUST match the receiver address
