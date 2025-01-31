#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// nRF24L01 pins
#define CE_PIN 9
#define CSN_PIN 10
const float MAX_CURRENT=30;

RF24 radio(CE_PIN, CSN_PIN);

const uint8_t thisSlaveAddress[6] = "00003";

struct DroneAndDroneControlData {
  int16_t leftStickX, leftStickY, rightStickX, rightStickY; // 8 bytes
  uint8_t buttonCross, buttonCircle, buttonSquare, buttonTriangle; // 4 bytes
  float gyro_pitch, gyro_roll, gyro_yaw; // 12 bytes
  int16_t acc_total_vector; // 2 bytes (keeps sign, avoids unnecessary precision loss)
  uint16_t motorCurrent[4]; // 8 bytes
  uint16_t batteryLevel; // 2 bytes (stored in mV)
}; // **Still 32 bytes**

DroneAndDroneControlData DroneControlData;

void setup() {

  Serial.begin(115200);
  Serial.println("nRF24 Receiver Starting...");

  if (!radio.begin()) {
    Serial.println("nRF24 initialization failed!");
    while (1);
  }
  radio.openReadingPipe(0, thisSlaveAddress);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  Serial.println("nRF24 is listening...");
}

void loop() {
  if (radio.available()) {
    
    // ERROR HANDLER
    radio.read(&DroneControlData, sizeof(DroneControlData));

    Serial.print("Button Cross: "); Serial.print(DroneControlData.buttonCross);
    Serial.print(" Button Circle: "); Serial.print(DroneControlData.buttonCircle);
    Serial.print(" Button Square: "); Serial.print(DroneControlData.buttonSquare);
    Serial.print(" Button Triangle: "); Serial.print(DroneControlData.buttonTriangle);
    Serial.print(" LS X "); Serial.print(DroneControlData.leftStickX);
    Serial.print(" LS Y: "); Serial.print(DroneControlData.leftStickY);
    Serial.print(" RS X: "); Serial.print(DroneControlData.rightStickX);
    Serial.print(" RS Y: "); Serial.println(DroneControlData.rightStickY);
    Serial.print(" Battery Level: "); Serial.print(DroneControlData.batteryLevel);
    Serial.print(" Motor Currents: ");
    for (int i = 0; i < 4; i++) {
    Serial.print(DroneControlData.motorCurrent[i]); Serial.print(" ");
    }
    Serial.print(" Gyro Pitch: "); Serial.print(DroneControlData.gyro_pitch);
    Serial.print(" Gyro Roll: "); Serial.print(DroneControlData.gyro_roll);
    Serial.print(" Gyro Yaw: "); Serial.print(DroneControlData.gyro_yaw);
    Serial.print(" Acc Total Vector: "); Serial.print(DroneControlData.acc_total_vector);
  }
}
