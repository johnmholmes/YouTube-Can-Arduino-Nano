#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 10;  // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2;  // Interrupt pin for MCP2515
const int PIN_5 = 5;        // Output pin 5
const int PIN_6 = 6;        // Input pin 6
const int PIN_7 = 7;        // Input pin 7

MCP_CAN CAN(SPI_CS_PIN);

int previousState6 = HIGH; // hold the previous states
int previousState7 = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_5, OUTPUT);      // Setup the pin as an output
  pinMode(PIN_6, INPUT_PULLUP); // Setup the pins as inputs
  pinMode(PIN_7, INPUT_PULLUP);

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
  int state6 = digitalRead(PIN_6);
  int state7 = digitalRead(PIN_7);

  // Check for state change on pin 6
  if (state6 != previousState6) {
    sendState(6, state6);
    previousState6 = state6;
  }

  // Check for state change on pin 7
  if (state7 != previousState7) {
    sendState(7, state7);
    previousState7 = state7;
  }

  delay(100);  // Add a small delay for stability and to reduce bus traffic
}

void sendState(int pin, int state) {
  char msg[8];
  snprintf(msg, sizeof(msg), "%d:%d", pin, state);

  CAN.sendMsgBuf(0x123, 0, strlen(msg), (byte*)msg);

  Serial.print("Message Sent: ");
  Serial.println(msg);
}

void receiveISR() {
  // Read the received message
  unsigned char len = 0;
  unsigned char buf[8];

  if (CAN.checkReceive() == CAN_MSGAVAIL) {
    // Only pass the length and buffer to readMsgBuf
    CAN.readMsgBuf(&len, buf);

    // Get the CAN ID separately
    unsigned long canId = CAN.getCanId();

    // Print received message details
    Serial.print("Received Message: ID=");
    Serial.print(canId, HEX);
    Serial.print(", Data=");
    Serial.println((char*)buf);

    // Check if the received message has ID 0x124 and data "7:0" or "7:1"
    if (canId == 0x124) {
      int pin, state;
      if (sscanf((char*)buf, "%d:%d", &pin, &state) == 2) {
        if (pin == 7) {
          // Toggle the LED on pin 5 based on the state
          digitalWrite(PIN_5, state);
          Serial.print("LED Set to: ");
          Serial.println(state);
        }
      }
    }
  }
}
