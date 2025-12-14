
#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


/**
 * This function returns the number of bytes a string will need to be
 * allocated based on the variable argument list and a format string that are
 * provided to this function.
 */
size_t vbytesfmt(va_list lp, char* fmt);

/**
 * This function dynamically allocates only the needed amount of memory to a
 * string based on the argument list, then concatenates the argument list into 
 * the supplied format and stores it in the supplied string pointer.
 */
char* strfmt(char* buf, char *fmt, ...);

/**
 * This function removes the char element from the string provided to it which
 * is at the element number/index provided to it.
 */
char* sdelelem(char* sp, unsigned elem);

/**
 * This function removes the char element from the string provided to it which
 * is at the element number/index provided to it.
 */
char* sdelelem(char* sp, unsigned elem);

/**
 * This function removes all cases of the provided char from the string at the
 * provided pointer.
 */
void sdelchar(char* sp, char remove);


/**
 * This function returns a string that represent the current time.
 * For reasons detailed in a comment within this function, you must
 * free() the string that this function returns.
 */
char* timestamp();

/**
 * This function outputs to a filestream.
 * It dynamically allocates the neccessary amount of memory to an internal
 * buffer that is based on the format string and argument list
 * parameters, then outputs the buffer to the filestream parameter.
 */
void fsout(FILE* fs, char *fmt, ...);


#endif
