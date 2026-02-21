#include <SPI.h>
#include <mcp_can.h>   // ← Use coryjfowler/MCP_CAN_lib  (install via Library Manager)

/*
   Test sketch for Arduino Nano + MCP2515 module
   Pins:
     10 = CS
     2  = INT
     11 = MOSI
     12 = MISO
     13 = SCK
     + GND + 5V

   Sends alternating "on" and "of" messages every ~5 seconds
*/

const int SPI_CS_PIN  = 10;
const int CAN_INT_PIN = 2;

MCP_CAN CAN(SPI_CS_PIN);   // Set CS pin

void setup() {
  Serial.begin(115200);
  while (!Serial);           // Wait for serial (good practice on some boards)

  Serial.println("Starting CAN test...");

  // Initialize MCP2515
  //               mode      baud       crystal
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515 - check wiring / crystal freq / module");
    while (1);  // halt
  }

  // Optional: set normal mode explicitly (some versions need this)
  CAN.setMode(MCP_NORMAL);

  // Optional: attach interrupt if you later want to receive messages
  // pinMode(CAN_INT_PIN, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), receiveISR, FALLING);
}

void loop() {
  sendMessage("on");
  delay(5000);
  sendMessage("of");
  delay(5000);
}

void sendMessage(const char* text) {
  byte msg[8] = {0};           // most CAN messages use ≤ 8 bytes
  size_t len = strlen(text);
  if (len > 8) len = 8;
  memcpy(msg, text, len);

  // Send standard frame, ID 0x123, data length = 2 (even if we send more, 2 is fine for "on"/"of")
  byte sndStat = CAN.sendMsgBuf(0x123, 0, 2, msg);

  if (sndStat == CAN_OK) {
    Serial.print("Message sent successfully: ");
  } else {
    Serial.print("Send failed with error code: ");
    Serial.print(sndStat);
    Serial.print(" → ");
  }
  Serial.println(text);
}

void receiveISR() {
  // You can add receive code here later if needed
  // For now it's empty
}


