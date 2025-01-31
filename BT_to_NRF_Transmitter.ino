#include <Bluepad32.h>
#include <RF24.h>
#include <SPI.h>

// Pin definitions for the NRF24L01 module
#define CE_PIN 22
#define CSN_PIN 21

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Define the NRF24L01 communication pipe
const uint8_t address[5] = {'0', '0', '0', '0', '3'};

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

// Struct to hold drone information
struct TelemetryData {
  float altitude;        // Altitude in meters
  float accelerationX;   // Acceleration in X-axis (m/s²)
  float accelerationY;   // Acceleration in Y-axis (m/s²)
  float accelerationZ;   // Acceleration in Z-axis (m/s²)
  float motorCurrents[4]; // Current in 4 motors (amps)
  float batteryVoltage;   // Battery voltage (volts)
};

// Create a new structure to be used
MyControllerData controllerData;

// Global pointer to the connected gamepad, set to null pointer by default
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
  
  // Initialize Serial Monitor, 115200 baud rate is NECESSARY for BluePad32 operation
  Serial.begin(115200);

  // Initialize Bluepad32
  BP32.setup(&onGamepadConnected, &onGamepadDisconnected);
  Serial.println("Waiting for Bluetooth Controller...");

  // Initialize NRF24L01
  if (!radio.begin()) {
    Serial.println("NRF24L01 initialization failed!");
    while (1);
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
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
    controllerData.buttonCross = buttons & BUTTON_A; // Cross
    controllerData.buttonCircle = buttons & BUTTON_B; // Circle
    controllerData.buttonSquare = buttons & BUTTON_X; // Square
    controllerData.buttonTriangle = buttons & BUTTON_Y; // Triangle

    
  }

// Send controller data via NRF24L01
    if (!radio.write(&controllerData, sizeof(controllerData))) {
      Serial.println("Error: Failed to send data.");

    } 
    else {
      Serial.println("Data sent successfully.");
    }
}
