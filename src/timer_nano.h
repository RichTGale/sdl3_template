/**
 * timer_nano.h
 * 
 * This file contains function and type declarations for the timer_nano
 * data type.
 * The timer_nano type is a timer that has nanosecond precision.
 * 
 * Author(s): Richard Gale
 * Version: 1.1
 */

#ifndef TIMER_NANO_H
#define TIMER_NANO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> /* strerror() */
#include <stdarg.h>
#include <time.h>
#include <errno.h>

#include "utils.h"

/**
 * The number of nanoseconds per second.
 */
#define NANOS_PER_SEC 1000000000

/**
 * The timer data structure.
 */
typedef struct timer_nano_data
{
    struct timespec initial;
    struct timespec current;
    struct timespec elapsed;
} timer_nano;

/**
 * This function returns a new instance of a timer_nano.
 */
timer_nano* timer_nano_init();

/**
 * This function resetn a timer_nano.
 */
void timer_nano_reinit(timer_nano* tn);

/**
 * This function will return true upon the timer_nano passed to it
 * has elapsed its waiting time parameter, otherwise it will return false.
 */
bool timer_nano_elapsed(timer_nano tn, long long wait_time);

/**
 * This function destroys/deallocates memory from a timer_nano.
 */
void timer_nano_term(timer_nano* tn);

#endif /* TIMER_NANO_H */
