#include <Bluepad32.h>

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

    // Debug output
    Serial.print("LeftStick X:");
    Serial.print(controllerData.leftStickX);
    Serial.print(" LeftStick Y:");
    Serial.print(controllerData.leftStickY);
    Serial.print(" RightStick X:");
    Serial.print(controllerData.rightStickX);
    Serial.print(" RightStick Y:");
    Serial.print(controllerData.rightStickY);
    Serial.print(" Button A Cross:");
    Serial.print(controllerData.buttonCross);
    Serial.print(" Button X Square:");
    Serial.print(controllerData.buttonSquare);
    Serial.print(" Button B Circle:" );
    Serial.print(controllerData.buttonCircle);
    Serial.print(" Button Y Triangle:" );
    Serial.println(controllerData.buttonTriangle);

  }
}
