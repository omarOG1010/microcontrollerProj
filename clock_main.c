// DO NOT MODIFY
// 
// LCD Clock simulator. Read time since the beginning of the
// day from the command line and show the results of running functions
// from clock_update.c on the screen. Makes use of functions from
// clock_clock.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clock.h"

int main(int argc, char **argv){

  if(argc < 2){                 // Set TIME_OF_DAY_SEC to the actual time
    time_t rawtime;             // Get raw time with system calls
    time( &rawtime );
    struct tm *info;              // Store broken down time
    info = localtime( &rawtime ); // Get a broken down time

    // Calculate the seconds since the beginning of the day
    TIME_OF_DAY_PORT = (info->tm_sec + 60*info->tm_min + 60*60*info->tm_hour)*16;
  }
  else{                         // Set time based on argument given
    TIME_OF_DAY_PORT = atoi(argv[1]);
  }
  printf("TIME_OF_DAY_PORT set to: %d\n", TIME_OF_DAY_PORT);

  tod_t tod;
  int result;

  printf("result = set_tod_from_ports(&tod );\n");
  result = set_tod_from_ports(&tod);
  printf("result: %d\n",result);
  printf("tod = {\n"); 
  printf("  .day_secs   = %d\n",tod.day_secs);
  printf("  .time_hours = %d\n",tod.time_hours);
  printf("  .time_mins  = %d\n",tod.time_mins);
  printf("  .time_secs  = %d\n",tod.time_secs);
  printf("  .ampm       = %d\n",tod.ampm);
  printf("}              \n");
  printf("Simulated time is: %02d : %02d : %02d %s\n",
         tod.time_hours,tod.time_mins,tod.time_secs,(tod.ampm==1 ? "am" : "pm"));

  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  int display = 0;
  printf("result = set_display_from_tod(tod, &display);\n");
  result = set_display_from_tod(tod, &display);
  printf("result: %d\n", result);
  printf("display is\n");
  printf("bits:  %s\n",bitstr(display, INT_BITS));
  printf("index: %s\n",bitstr_index(INT_BITS));

  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  printf("\n");

  printf("result = clock_update();\n");
  result = clock_update();
  printf("result: %d\n", result);
  printf("CLOCK_DISPLAY_PORT is\n");
  printf("bits:  %s\n",bitstr(CLOCK_DISPLAY_PORT, INT_BITS));
  printf("index: %s\n",bitstr_index(INT_BITS));

  printf("%s", (result == 0) ? "" : "WARNING: Non-zero value returned\n");

  printf("\n");

  printf("Clock Display:\n");
  print_clock_display();

  return 0;
}
