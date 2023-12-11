# Fundamentals of Servo Control

In the realm of model railway layouts, the SG90 servos have gained popularity for their affordability. These servos employ pulse width modulation (PWM) to precisely define angles. Consequently, it's imperative to connect the servo to a pin on the Arduino Nano that supports PWM.

Among the available pins on the Arduino Nano—namely, 3, 5, 6, 9, 10, and 11—pins 10 and 11 are typically allocated for the Mcp2515 module. This configuration allows for the simultaneous control of up to four servos. However, for optimal performance, I recommend limiting each Arduino Nano to a maximum of two attached servos.
