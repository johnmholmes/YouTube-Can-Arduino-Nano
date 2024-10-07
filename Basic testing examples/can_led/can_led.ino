#include <SPI.h>
#include <mcp_can.h>

/*
This sketch is for testing an Arduino Nano using the MCP2515 module using SPI

Pins used for connecting the module are:
PIN 2 = INT
PIN 10 = CS
PIN 11 = SI
PIN 12 = SO
PIN 13 = SCK

GND and 5 volts also required.

If the module receives a message on the CAN bus of "on" or "of", this will turn on/off an LED on PIN 7.
*/

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2;  // Interrupt pin for MCP2515
const int LED_PIN = 7;      // LED used on pin 7 of the Nano

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); // Set the pin as an output

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
  // Nothing to do here since the receiveISR will handle incoming messages
}

void receiveISR() {
  // Declare variables for storing received message data
  uint8_t len;
  uint8_t rxBuf[16];

  // Check if there's a message available
  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    // Read the message
    CAN.readMsgBuf(&len, rxBuf);  // Only length and data buffer are needed

    // Get the message ID (optional, not always needed for simple tasks)
    unsigned long rxId = CAN.getCanId();

    // Print the received message to the Serial Monitor
    Serial.print("Received Message ID: 0x");
    Serial.print(rxId, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print((char)rxBuf[i]);
    }
    Serial.println();

    // Check if the received message is "on"
    if (len == 2 && rxBuf[0] == 'o' && rxBuf[1] == 'n') {
      // Turn on the LED
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED Turned On!");
    }

    // Check if the received message is "of"
    if (len == 2 && rxBuf[0] == 'o' && rxBuf[1] == 'f') {
      // Turn off the LED
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED Turned Off!");
    }
  }
}
