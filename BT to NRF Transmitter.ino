#include <Bluepad32.h>
#include <RF24.h>
#include <SPI.h>

// Pin definitions for the NRF24L01 module
#define CE_PIN 22
#define CSN_PIN 21

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the NRF24L01 communication pipe
const uint8_t address[5] = {'0', '0', '0', '0', '1'};

// Struct to hold controller states
struct MyControllerData {
  int16_t leftStickX;
  int16_t leftStickY;
  int16_t rightStickX;
  int16_t rightStickY;
  bool buttonCross;
  bool buttonCircle;
  bool buttonSquare;
  bool buttonTriangle;
};

MyControllerData controllerData;

// Global pointer to the connected gamepad
GamepadPtr myGamepad = nullptr;

// Callback when a gamepad connects
void onGamepadConnected(GamepadPtr gp) {
  Serial.println("Gamepad connected!");
  myGamepad = gp;
}

// Callback when a gamepad disconnects
void onGamepadDisconnected(GamepadPtr gp) {
  Serial.println("Gamepad disconnected.");
  myGamepad = nullptr;
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize Bluepad32
  BP32.setup(&onGamepadConnected, &onGamepadDisconnected);
  Serial.println("Waiting for PS3 Controller...");

  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();

  Serial.println("NRF24L01 initialized.");
}

void loop() {
  // Process gamepad updates
  BP32.update();

  if (myGamepad) {
    // Read stick values
    controllerData.leftStickX = myGamepad->axisX();
    controllerData.leftStickY = myGamepad->axisY();
    controllerData.rightStickX = myGamepad->axisRX();
    controllerData.rightStickY = myGamepad->axisRY();

    // Read button states using the `buttons()` method
    uint16_t buttons = myGamepad->buttons(); // Retrieve the button states as a bitmask
    controllerData.buttonCross = buttons & BUTTON_X; // Cross
    controllerData.buttonCircle = buttons & BUTTON_B; // Circle
    controllerData.buttonSquare = buttons & BUTTON_Y; // Square
    controllerData.buttonTriangle = buttons & BUTTON_A; // Triangle

    // Debug output
    Serial.print("LX: ");
    Serial.print(controllerData.leftStickX);
    Serial.print(" LY: ");
    Serial.print(controllerData.leftStickY);
    Serial.print(" RX: ");
    Serial.print(controllerData.rightStickX);
    Serial.print(" RY: ");
    Serial.println(controllerData.rightStickY);

    // Send controller data via NRF24L01
    if (!radio.write(&controllerData, sizeof(controllerData))) {
      Serial.println("Error: Failed to send data.");
    } else {
      Serial.println("Data sent successfully.");
    }
  }
}
