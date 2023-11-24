# YouTube-Can-Arduino-Nano
A simple set of Can Sketches for an Arduino Nano using a MCP 2515 can module

This will be used during my learning before moving on to using MERG Cbus protocol for a model railway aplication.

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

----

# For explanations of certain functions

See the readme files in the can_button_v2

----
