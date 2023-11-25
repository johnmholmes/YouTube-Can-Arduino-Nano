#include <SPI.h>
#include <mcp_can.h>

/*
This sketch is for testing an Arduino Nano using the MCP2515 module using spi

Pins used for connecting the module are.
PIN 2 = INT
PIN 10 = CS
PIN 11 = SI
PIN 12 = SO
PIN 13 = SCK

GND and 5 volts also required.

we also have a push button on PIN 7

This sketch only sends a message when the state changes it does use a delay of 100ms in its to avoid button debounce
*/

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2; // Interrupt pin for MCP2515
const int BUTTON_PIN = 7;  // Pin to read the state of the button

MCP_CAN CAN(SPI_CS_PIN);

// Variables to track the previous state of the button
int previousButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize MCP2515
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
    CAN.setMode(MCP_NORMAL);
  } else {
    Serial.println("Error Initializing MCP2515...");
    while (1);
  }

  // Attach interrupt for receiving messages
  attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), receiveISR, FALLING);
}

void loop() {
  // Read the state of the button
  int buttonState = digitalRead(BUTTON_PIN);

  // Check for a state change
  if (buttonState != previousButtonState) {
    // Send a message based on the button state
    if (buttonState == HIGH) {
      sendMessage("on");
    } else {
      sendMessage("off");
    }

    // Update the previous state to the current state
    previousButtonState = buttonState;
  }

  delay(100); // Add a small delay to debounce the button (optional)
}

void sendMessage(const char* message) {
  byte msg[16] = {0};
  strncpy((char*)msg, message, 16); // Copy the message to the buffer

  // Create a CAN message
  CAN.sendMsgBuf(0x123, 0, 2, msg); // Assuming "on" or "of" is a 2-character message

  Serial.print("Message Sent: ");
  Serial.println(message);
}

void receiveISR() {
  // Handle the interrupt here if needed
  // Note: In this example, we're just sending messages and not actively receiving them
}

