# Can_Button_v2

This is a more useful sketch, but still very easy to understand.

----


# I will explain sendMessage()

![void sendMessage](https://github.com/johnmholmes/YouTube-Can-Arduino-Nano/assets/60571002/64575530-bc20-4942-8d3f-54a77cdd3f8b)

1. Function Signiture.

   void sendMessage(const char* message) {

   void: The function does not return any value.

   sendMessage: The name of the function.

   const char* message: The function takes a parameter named message, which is a pointer to a constant character (a string).

2. Initalise Buffer.

   byte msg[16] = {0};

   This line declares an array of 16 bytes named msg and initializes all elements to zero.

3. Copy Message to Buffer.

   strncpy((char*)msg, message, 16);

   strncpy is a function that copies characters from one string to another.

   In this case, it copies characters from the message parameter (which is a C-style string) to the msg buffer.

   The (char*) cast is used to convert the msg buffer from byte to char type, as strncpy works with char arrays.

4. Create CAN Message and Send.

   CAN.sendMsgBuf(0x123, 0, 2, msg);

   CAN.sendMsgBuf is a function from the MCP_CAN library that sends a message on the CAN bus.

   It takes four arguments:

   0x123: The message ID (arbitrary in this example; you can replace it with your desired ID).

   0: The message object (use 0 for standard messages).

   2: The length of the data in bytes (assuming "on" or "off" is a 2-character message).

   msg: The data buffer containing the message.

5. Print to Serial Monitor.

   Serial.print("Message Sent: ");
   Serial.println(message);

   These lines print a confirmation message to the Serial Monitor indicating that the message has been sent.

   It prints both the static text "Message Sent: " and the actual message passed as the parameter (message).
----
# In summary sendMessage()
----
The sendMessage function takes a message as a parameter, copies it to a buffer, sends a CAN message with the specified ID and data length, and then prints a confirmation message to the Serial Monitor. This function is designed to be a convenient way to send messages over the CAN bus with minimal code duplication.

----
   
