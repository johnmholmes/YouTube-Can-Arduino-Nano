# Arduino CAN Bus Introduction Series Using MCP_CAN Library

The idea is to demonstrate how quickly you can get started using the well-documented Arduino library for controlling the general input and output pins of an Arduino Nano in these examples. This can be easily adapted to other versions of Arduino or even ESP32 when using the MCP2515 modules readily available from various vendors.

There are other libraries available with their own protocols, as mentioned in video 1. However, these require additional libraries to implement some of the advanced features deemed important by their creators.

Learning Structure:

By taking small steps, you will see how, with little knowledge of using CAN, you can send a message to another Arduino on the 2-wire bus.

While the first few sketches may seem pointless, they provide a starting point for building your own knowledge in this useful bus protocol.

Other tutorials often delve straight into the arbitration of CAN Bus and the message frame, which can be challenging to grasp initially. That's why I've kept it quite simple.

----

# Take a look at the Wiki

I have added a Wiki page for this repository which is easier to work with and present stuff in the future.

----

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

I would use these connectors and once tested I hot glue them to ensure they do not get knocked loose during working on the layout.

![Screenshot 2023-12-10 041615](https://github.com/johnmholmes/YouTube-Can-Arduino-Nano/assets/60571002/3804aa74-2c97-42f4-8cb1-6f1d14a9fdfb)

----

# I now have some videos available.

Can Bus Introduction Keeping it Simple Part 1 can_send  https://youtu.be/nReYv7AuRKM

Can Bus Introduction Keeping it Simple Part 2 can_led https://youtu.be/QWkKpsVkfYs

Can Bus Introduction Part 3 can_buttonv1 https://youtu.be/UP8DhyaETAk

Can Bus Introduction Part 4 Cables and Frequencies  https://youtu.be/fLdaum8oW4s

Can Bus Introduction Part 5 can_buttonv2 https://youtu.be/KHAcO5UrAmc

Can Bus Introduction Part 6 can_buttonsv 1 2 input producer https://youtu.be/iX94LOcw23w

Can Bus Introduction Part 7 can_led2 2 led consumer https://youtu.be/4tY41bF1wNc

Can Bus Introduction Part 8 prod_consumer_v1 https://youtu.be/Bwbq02Fw1-k

Can Bus Introduction Part 9 Arbitration https://youtu.be/fJrD0e44Bxg

----

# Latest software added

1 December 

prod_consumer_v1 - This builds on the buttons_v1 sketch to toggle an led on pin 5 when a messaage is recived from a can id of 0x124 with the data 7:0 or 7:1 

25 Novemeber

can_led show how to read the message recieved
 
can_buttons_v1 - this allows for to inputs on pins 6 & 7 to send data on the bus.

can_led2 - This will toggle the leds on pins 6 & 7 when the data is received.

----

# Next sketch to be added

A simple servo sketch see the servo folder


