# Fundamentals of Servo Control

In the realm of model railway layouts, the SG90 servos have gained popularity for their affordability. These servos employ pulse width modulation (PWM) to precisely define angles. Consequently, it's imperative to connect the servo to a pin on the Arduino Nano that supports PWM.

Among the available pins on the Arduino Nano namely, 3, 5, 6, 9, 10, and 11,  pins 10 and 11 are typically allocated for the Mcp2515 module. This configuration allows for the simultaneous control of up to four servos. However, for optimal performance, I recommend limiting each Arduino Nano to a maximum of two attached servos.

## Servo.h Arduino Library

This library is well documented via the Arduino website. As far as I am currently aware there are no issues when uising it with the Mcp_can or spi libraries.


## Servo Calabration

On a layout each servo would need to be calibrated to ensure that a turnout attached to it would reach its closed and thrown positions. Then you could hard code these setting within the sketch.

You could also use a for loop to add slow motion for a ore realistic action. you would need to think about how long it takes to complete the move, as this could effect other messages either being sent or received by the unit.
