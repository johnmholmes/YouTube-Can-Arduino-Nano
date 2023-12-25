#include <mcp_can.h>
#include <SPI.h>

// Define the CAN bus pins
const int CAN_CS_PIN = 10;
const int CAN_INT_PIN = 2;

// Create MCP_CAN object
MCP_CAN CAN(CAN_CS_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ; // Wait for Serial to be ready

  // Initialize the SPI bus
  SPI.begin();

  // Initialize the CAN bus
  if (CAN.begin(MCP_ANY, CAN_125KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("CAN bus initialized");
    CAN.setMode(MCP_NORMAL);
  } else {
    Serial.println("Error initializing CAN bus");
    while (1)
      ;
  }
}

void loop() {
  // Send CAN message 7:1
  sendCANMessage(0x0123, 2, 7, 1);
  Serial.println("Sent CAN message: 7:1");

  delay(20000); // Wait for 5 seconds

  // Send CAN message 7:0
  sendCANMessage(0x0123, 2, 7, 0);
  Serial.println("Sent CAN message: 7:0");

  delay(20000); // Wait for 5 seconds
}

void sendCANMessage(unsigned long id, byte length, byte data0, byte data1) {
  // Prepare the CAN message data
  byte messageData[] = {data0, data1};

  // Send the CAN message
  int sendResult = CAN.sendMsgBuf(id, 0, length, messageData);

  if (sendResult == CAN_OK) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending message");
  }
}
