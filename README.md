# microcontrollerProj


Overview


This is code which will be run by a microcontroller in a digital clock. The hardware has the following relevant features:
An internal clock that increments 16 time per second. The value reported by the clock is stored in a special hardware location that is presented as a global variable.
A digital display with a control port; setting certain global variable will change the display to show information to a user of the clock.
User code that you will need to write to update the display based on the value reported by the internal clock.


files clock_main.c and clock_sim allow you to simulate the output of the microcontroller in order to debug the code. 
