# YouTube-Can-Arduino-Nano
A simple set of Can Sketches for an Arduino Nano using a MCP 2515 can module

This will be used during my learning before moving on to using Cbus protocol for a model railway aplication.

On the Arduino Nano the MCP2515 requires the use of 7 pins on the Nano.

You will need to install the <mcp_can.h> library for this to compile.

The Arduino Nano requires the following pins to supply the MCP_2515 module

Pins used for connecting the module are.

PIN 2 = INT

PIN 10 = CS

PIN 11 = SI

PIN 12 = SO

PIN 13 = SCK

GND and 5 volts also required and the GND should be joined between units.

Also remember the ends of the bus need the termination resister connected on the MCP 2515 boards

![Screenshot 2023-11-25 083645](https://github.com/johnmholmes/YouTube-Can-Arduino-Nano/assets/60571002/53089285-e6ed-4b93-a4d2-de7615801de3)

----

# I now have some videos available.

Can Bus Introduction Keeping it Simple Part 1 Can_send  https://youtu.be/nReYv7AuRKM

Can Bus Introduction Keeping it Simple Part 2 Can_led https://youtu.be/QWkKpsVkfYs

----

# Latest software added

 25 Novemeber
 
can_buttons_v1 - this allows for to inputs on pins 6 & 7 to send data on the bus.

can_led2 - This will toggle the leds on pins 6 & 7 when the data is recived.

----

# Next sketch to be added

Can_Button_led - this will be a consumer as well as a producer.


