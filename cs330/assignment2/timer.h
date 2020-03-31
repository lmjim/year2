#ifndef TIMER_H_
#define TIMER_H_

#include "clock.h"

// Initialize the timer with the user-provided input
void initTimer(ClockType *clock, int minutes, int seconds);

// Run the timer -- print out the time each second
void runTimer();

// Clean up memory (as needed)
void cleanTimer(ClockType  *clock);

#endif /* CLOCK_H_ */
