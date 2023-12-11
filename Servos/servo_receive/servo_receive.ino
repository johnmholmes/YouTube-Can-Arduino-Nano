#include <Servo.h>
#include <SPI.h>
#include <mcp_can.h>

// Define the CAN bus pins
const int CAN_CS_PIN = 10;
const int CAN_INT_PIN = 2;

// Create MCP_CAN object
MCP_CAN CAN(CAN_CS_PIN);

// Define servo pin
const int servoPin = 6;

// Create Servo object
Servo myServo;

// Variables for CAN message
unsigned long rxId;
unsigned char len;
unsigned char rxBuf[8];

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // Wait for Serial to be ready

  // Initialize the SPI bus
  SPI.begin();

  // Initialize the CAN bus
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN bus initialized");
    CAN.setMode(MCP_NORMAL);
  } else {
    Serial.println("Error initializing CAN bus");
    while (1);
  }

  // Attach the servo to the pin
  myServo.attach(servoPin);
}

void loop() {
  // Check if there is a CAN message available
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    // Read the received message
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    // Check if the received message has the expected ID and data
    if (rxId == 0x0123 && len == 2 && rxBuf[0] == 7 && rxBuf[1] == 1) {
      // If the condition is met, move the servo to a specific position
      myServo.write(90);  // Adjust the angle as needed
      Serial.println("Servo moved to position 90 degrees");
    }

    if (rxId == 0x0123 && len == 2 && rxBuf[0] == 7 && rxBuf[1] == 0) {
      // If the condition is met, move the servo to a specific position
      myServo.write(10);  // Adjust the angle as needed
      Serial.println("Servo moved to position 10 degrees");
    }
  }

  // Add other code or functionality here as needed
}
