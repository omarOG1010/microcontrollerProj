#ifndef CLOCK_H
#define CLOCK_H 1

// size in bits of some types
#define INT_BITS   (sizeof(int)*8)
#define SHORT_BITS (sizeof(short)*8)
#define CHAR_BITS  (sizeof(char)*8)

////////////////////////////////////////////////////////////////////////////////
// clock_update.c structs/functions

// Breaks time down into 12-hour format
typedef struct{
  int   day_secs;    // seconds from start of day
  short time_secs;   // seconds in current hour
  short time_mins;   // minutes in current hour
  short time_hours;  // current hour of day
  char ampm;         // 1 for am, 2 for pm
} tod_t;

// Functions to implement for CLOCK Clock Problem
int set_tod_from_ports(tod_t *tod);
int set_display_from_tod(tod_t tod, int *display);
int clock_update();


////////////////////////////////////////////////////////////////////////////////
// clock_clock.c structs/functions; do not modify

extern int TIME_OF_DAY_PORT;
// Time of day in units of 1/16th of a second. Tied to a hardware
// clock that automatically increments it 16 times per second starting
// at midnight. The simulatator provides a C global variable to
// emulate this part of the hardware. This variable is present when
// #include "clock.h" is used and should not be declared in any user
// code.

extern int CLOCK_DISPLAY_PORT;
// Global variable used to control the LCD display on the
// clock. Making changes to this variable will change the lighting
// patternon the LCD display.


// Use the global CLOCK_DISPLAY_PORT to print the time 
void print_clock_display();

// utility to show the bits of an integer
char *bitstr(int x, int bits);
char *bitstr_index(int bits);

#endif
