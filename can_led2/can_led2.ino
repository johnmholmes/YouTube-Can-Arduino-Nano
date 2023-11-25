#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2;  // Interrupt pin for MCP2515
const int LED_PIN_6 = 6;    // LED pin for pin 6
const int LED_PIN_7 = 7;    // LED pin for pin 7

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN_6, OUTPUT);
  pinMode(LED_PIN_7, OUTPUT);

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
  // Your main code can go here if needed
}

void receiveISR() {
  // Handle the interrupt here
  // Note: In this example, we're actively receiving and processing messages
  // You can add your own logic here based on the received messages
  receiveMessages();
}

void receiveMessages() {
  unsigned long rxId;
  byte len;
  byte rxBuf[8];

  if (CAN.checkReceive()) {
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    // Print received message details
    Serial.print("Received Message ID: 0x");
    Serial.print(rxId, HEX);
    Serial.print(" Data: ");

    // Print message data
    for (int i = 0; i < len; i++) {
      Serial.print((char)rxBuf[i]);
    }

    Serial.println();

    // Process the received message
    processMessage(rxId, rxBuf, len);
  }
}

void processMessage(unsigned long rxId, byte* rxBuf, byte len) {
  // Extract pin and state information from the message
  int pin;
  int state;
  sscanf((char*)rxBuf, "%d:%d", &pin, &state);

  // Act on the received information
  if (pin == 6) {
    digitalWrite(LED_PIN_6, state);
  } else if (pin == 7) {
    digitalWrite(LED_PIN_7, state);
  }
}


