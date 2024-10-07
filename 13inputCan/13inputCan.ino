/*
This sketch is designed to give you a total of 13 inputs that could be used 
for a mimic panel.

This node has the Can Id of 001 which will give it the highest priority on the bus.

If you need another module to add more inputs reuse this sketch but change the Can Id to 002

Pins A6 & A7 are analog pins so are not used.

Also pins 0 & 1 are not used as they are used for the usb normally so I avoid using them.
*/

#include <SPI.h>
#include <mcp_can.h>

// Global variable for CAN ID
unsigned int canId = 0x001;

const int SPI_CS_PIN = 10;   // Chip Select pin for MCP2515
const int CAN_INT_PIN = 2;   // Interrupt pin for MCP2515
const int PIN_3 = 3;         // Input pin 3
const int PIN_4 = 4;         // Input pin 4
const int PIN_5 = 5;         // Input pin 5
const int PIN_6 = 6;         // Input pin 6
const int PIN_7 = 7;         // Input pin 7
const int PIN_8 = 8;         // Input pin 8
const int PIN_9 = 9;         // Input pin 9
const int PIN_10 = A0;       // Input pin A0
const int PIN_11 = A1;       // Input pin A1
const int PIN_12 = A2;       // Input pin A2
const int PIN_13 = A3;       // Input pin A3
const int PIN_14 = A4;       // Input pin A4
const int PIN_15 = A5;       // Input pin A5

MCP_CAN CAN(SPI_CS_PIN);

int previousState3 = HIGH;
int previousState4 = HIGH;
int previousState5 = HIGH;
int previousState6 = HIGH;
int previousState7 = HIGH;
int previousState8 = HIGH;
int previousState9 = HIGH;
int previousState10 = HIGH;
int previousState11 = HIGH;
int previousState12 = HIGH;
int previousState13 = HIGH;
int previousState14 = HIGH;
int previousState15 = HIGH;

void setup() {
  Serial.begin(115200);

  Serial.println("This is a 13 input Can Node");
  Serial.println("Its Can ID is set to 0x001");
  Serial.println("Created by John Holmes");

  pinMode(PIN_3, INPUT_PULLUP);
  pinMode(PIN_4, INPUT_PULLUP);
  pinMode(PIN_5, INPUT_PULLUP);
  pinMode(PIN_6, INPUT_PULLUP);
  pinMode(PIN_7, INPUT_PULLUP);
  pinMode(PIN_8, INPUT_PULLUP);
  pinMode(PIN_9, INPUT_PULLUP);
  pinMode(PIN_10, INPUT_PULLUP);
  pinMode(PIN_11, INPUT_PULLUP);
  pinMode(PIN_12, INPUT_PULLUP);
  pinMode(PIN_13, INPUT_PULLUP);
  pinMode(PIN_14, INPUT_PULLUP);
  pinMode(PIN_15, INPUT_PULLUP);

  if (CAN.begin(CAN_125KBPS, 8000000) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
    
  } else {
    Serial.println("Error Initializing MCP2515...");
    while (1);
  }

  attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), receiveISR, FALLING);
}

void loop() {
  int state3 = digitalRead(PIN_3);
  int state4 = digitalRead(PIN_4);
  int state5 = digitalRead(PIN_5);
  int state6 = digitalRead(PIN_6);
  int state7 = digitalRead(PIN_7);
  int state8 = digitalRead(PIN_8);
  int state9 = digitalRead(PIN_9);
  int state10 = digitalRead(PIN_10);
  int state11 = digitalRead(PIN_11);
  int state12 = digitalRead(PIN_12);
  int state13 = digitalRead(PIN_13);
  int state14 = digitalRead(PIN_14);
  int state15 = digitalRead(PIN_15);

  if (state3 != previousState3) {
    sendState(3, state3);
    previousState3 = state3;
  }

  if (state4 != previousState4) {
    sendState(4, state4);
    previousState4 = state4;
  }

  if (state5 != previousState5) {
    sendState(5, state5);
    previousState5 = state5;
  }

  if (state6 != previousState6) {
    sendState(6, state6);
    previousState6 = state6;
  }

  if (state7 != previousState7) {
    sendState(7, state7);
    previousState7 = state7;
  }

  if (state8 != previousState8) {
    sendState(8, state8);
    previousState8 = state8;
  }

  if (state9 != previousState9) {
    sendState(9, state9);
    previousState9 = state9;
  }

  if (state10 != previousState10) {
    sendState(10, state10);
    previousState10 = state10;
  }

  if (state11 != previousState11) {
    sendState(11, state11);
    previousState11 = state11;
  }

  if (state12 != previousState12) {
    sendState(12, state12);
    previousState12 = state12;
  }

  if (state13 != previousState13) {
    sendState(13, state13);
    previousState13 = state13;
  }

  if (state14 != previousState14) {
    sendState(14, state14);
    previousState14 = state14;
  }

  if (state15 != previousState15) {
    sendState(15, state15);
    previousState15 = state15;
  }

  delay(50);
}

void sendState(int pin, int state) {
  char msg[8];
  snprintf(msg, sizeof(msg), "%d:%d", pin, state);

  CAN.sendMsgBuf(canId, 0, strlen(msg), (byte*)msg);

  Serial.print("Message Sent - CAN ID: 0x");
  Serial.print(canId, HEX);
  Serial.print(", Data: ");
  Serial.println(msg);
}

void receiveISR() {
  // Handle the interrupt here if needed
  // Note: In this example, we're just sending messages and not actively receiving them
}
