# Can_Button_v2

This is a more useful sketch, but still very easy to understand.

I will explain sendMessage()

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

   
