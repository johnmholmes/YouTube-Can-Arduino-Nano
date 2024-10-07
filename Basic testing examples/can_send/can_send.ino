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

The module sends 2 messages on the can bus of "on or of" 
*/

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2; // Interrupt pin for MCP2515

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize MCP2515
  if (CAN.begin(CAN_500KBPS, 8000000) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
    
  } else {
    Serial.println("Error Initializing MCP2515...");
    while (1);
  }

  // Attach interrupt for receiving messages
  attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), receiveISR, FALLING);
}

void loop() {
  // Send "on" message
  sendMessage("on");
  delay(5000); // Send the message every second
  sendMessage("of");
  delay(5000); // Send the message every second
}

void sendMessage(const char* message) {
  byte msg[16] = {0};  // Change char to byte
  strncpy((char*)msg, message, 16); // Copy the message to the buffer

  // Create a CAN message
  CAN.sendMsgBuf(0x123, 0, 2, msg); // Assuming "on" is a 2-character message

  Serial.print("Message Sent: ");
  Serial.println(message);
}

void receiveISR() {
  // Handle the interrupt here if needed
  // Note: In this example, we're just sending messages and not actively receiving them
}



