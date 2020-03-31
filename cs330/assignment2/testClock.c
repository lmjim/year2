#include <stdio.h>
#include <time.h>
#include "clock.h"

void main(){
        time_t cur_time;
        time(&cur_time); // Record current time to pass into print function
        ClockType *clock; // Initialize pointer to struct that is empty
        initClock(clock); // This function does nothing
        printClock(cur_time, clock); // Print 'current' time recorded above
        cleanClock(clock); // This function does nothing
        return;
}

