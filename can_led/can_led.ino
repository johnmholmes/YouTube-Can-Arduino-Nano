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

If the module receives a message on the can bus of "on or of" this will turn on an led on PIN 7
*/

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2; // Interrupt pin for MCP2515
const int LED_PIN = 7;     // led used on pin 7 of the nano

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); //Set the pin as an output

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
  // Nothing to do here since the receiveISR will handle incoming messages
}

void receiveISR() {
  // Declare variables for storing received message data
  unsigned long rxId;
  uint8_t len;
  uint8_t rxBuf[16];

  // Check if there's a message available
  if (CAN.checkReceive()) {
    // Read the message
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    // Mask out extended bits to get the standard 11-bit identifier
    unsigned int standardId = rxId & 0x7FF;

    // Print the received message to the Serial Monitor
    Serial.print("Received Message ID: 0x");
    Serial.print(standardId, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < len; i++) {
      Serial.print((char)rxBuf[i]);
    }
    Serial.println();

    // Check if the received message is "on"
    if (len == 3 && rxBuf[0] == 'o' && rxBuf[1] == 'n') {
      // Turn on the LED
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED Turned On!");
    }

        // Check if the received message is "of"
    if (len == 3 && rxBuf[0] == 'o' && rxBuf[1] == 'f'  && rxBuf[2] == 'f') {
      // Turn off the LED
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED Turned Off!");
    }
  }
}

