#include "clock.h"
#include <stdio.h>

#include<math.h>

int set_tod_from_ports(tod_t *tod){
    if(TIME_OF_DAY_PORT<0 || TIME_OF_DAY_PORT> 16*86400){
        return 1;
    }


    int mask = 0b1111;
    
    int day_s = TIME_OF_DAY_PORT>>4; // divide by 16 
    int rem = TIME_OF_DAY_PORT & mask;
    if(rem >= 8){ // rounds up depending on the remainder
        day_s++;
    }
    tod->day_secs = day_s;

    if (day_s< 43200) { // sets the am/pm
        tod->ampm = 1;
    }
    else {
        tod->ampm = 2;
    }
    tod->time_hours = day_s / 3600;
    if (tod->time_hours > 12) {
        tod->time_hours -= 12;
    }
    else if (tod->time_hours == 0) {
        tod->time_hours = 12;
    }

    tod->time_mins = (day_s % 3600)/60; 
    tod->time_secs= day_s % 60;    

    return 0;

    
}

// Reads the time of day from the TIME_OF_DAY_PORT global variable. If
// the port's value is invalid (negative or larger than 16 times the
// number of seconds in a day) does nothing to tod and returns 1 to
// indicate an error. Otherwise, this function uses the port value to
// calculate the number of seconds from start of day (port value is
// 16*number of seconds from midnight). Rounds seconds up if there at
// least 8/16 have passed. Uses shifts and masks for this calculation
// to be efficient. Then uses division on the seconds since the
// begining of the day to calculate the time of day broken into hours,
// minutes, seconds, and sets the AM/PM designation with 1 for AM and
// 2 for PM. By the end, all fields of the `tod` struct are filled in
// and 0 is returned for success.
 // 




int set_display_from_tod(tod_t tod, int *display){
    if(tod.time_hours < 0||tod.time_mins < 0||tod.time_secs < 0||tod.time_mins > 59||tod.time_secs > 59||tod.time_hours>12||(tod.ampm < 0 && tod.ampm > 3)){
        return 1;
        // checks out of bounds
    }
    
    int arr_bit[10] = {0b1110111, 0b0100100, 0b1011101, 0b1101101, 0b0101110, 0b1101011, 0b1111011, 0b0100101, 0b1111111, 0b1101111}; // array of bits that rep nums

    int min_ones = tod.time_mins % 10;
    int min_tens = (tod.time_mins - min_ones)/10;
    int hour_ones = tod.time_hours % 10;
    int hour_tens = (tod.time_hours - hour_ones)/10;
    int time_conv = 0b1;

    *display = 0b0000000;
    min_ones = arr_bit[min_ones];
    min_tens = arr_bit[min_tens] << 7; // shifting inorder for it to fit once all are combined ie line97
    hour_ones = arr_bit[hour_ones] << 14; // shifting inorder for it to fit once all are combined ie line97

    if (hour_tens == 1) {
        hour_tens = arr_bit[1] << 21;
    }
    else {
        hour_tens = 0b0000000 << 21;
    }
    if (tod.ampm == 2) { // sets the am/pm
        time_conv = time_conv << 29;
    }else{
        time_conv = time_conv << 28;
    }
    *display = time_conv|hour_tens|hour_ones|min_tens|min_ones;
    return 0;
}
// Accepts a tod and alters the bits in the int pointed at by display
// to reflect how the LCD clock should appear. If any time_** fields
// of tod are negative or too large (e.g. bigger than 12 for hours,
// bigger than 59 for min/sec) or if the AM/PM is not 1 or 2, no
// change is made to display and 1 is returned to indicate an
// error. The display pattern is constructed via shifting bit patterns
// representing digits and using logical operations to combine them.
// May make use of an array of bit masks corresponding to the pattern
// for each digit of the clock to make the task easier.  Returns 0 to
// indicate success. This function DOES NOT modify any global
// variables
// 



int clock_update(){
    if(TIME_OF_DAY_PORT < 0 || TIME_OF_DAY_PORT > 86400*16){ // checks if the port is out of bounds
        return 1;
    }
    tod_t tod_v;
    if(set_tod_from_ports(&tod_v)==1){ // checks if method ran properly 
        return 1;
    }
    if(set_display_from_tod(tod_v,&CLOCK_DISPLAY_PORT)==1){ // checks if method ran properly 
        return 1;
    }

    return 0;
}
// Examines the TIME_OF_DAY_PORT global variable to determine hour,
// minute, and am/pm.  Sets the global variable CLOCK_DISPLAY_PORT bits
// to show the proper time.  If TIME_OF_DAY_PORT appears to be in error
// (to large/small) makes no change to CLOCK_DISPLAY_PORT and returns 1
// to indicate an error. Otherwise returns 0 to indicate success.
//

