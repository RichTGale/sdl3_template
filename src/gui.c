/**
 * gui.c
 *
 * This file contains the function definitions for the gui library.
 * The gui library is a graphical application that uses SDL3.
 *
 * Date written was 14 December 2025
 * Written by Richard Gale..
 */

#include "gui.h"

/**
 * This function returns the number of bytes a string will need to be
 * allocated based on the variable argument list and a format string that are
 * provided to this function.
 */
size_t vbytesfmt(va_list lp, char* fmt)
{
    va_list lp_cpy; /* A Copy of the list of arguments. */
    size_t bytes;   /* The number of bytes the string needs. */

    /* Copying the argument list. */
    va_copy(lp_cpy, lp);

    /* Getting the number of bytes the string will need. Adding an extra
     * 1 char worth of bytes for the null character. */
    bytes = vsnprintf(NULL, 0, fmt, lp_cpy) + sizeof(char);

    /* Assuring a clean finish to the copy. */
    va_end(lp_cpy);

    /* Returning the number of bytes the string will need. */
    return bytes;
}

/**
 * This function dynamically allocates only the needed amount of memory to a
 * string based on the argument list, then concatenates the argument list into 
 * the supplied format and stores it in the supplied string pointer.
 */
char* strfmt(char* buf, char *fmt, ...)
{
    va_list lp;     /* Pointer to the list of arguments. */
    size_t bytes;   /* The number of bytes the string needs. */

    /* Pointing to the first argument. */
    va_start(lp, fmt);

    /* Getting the number of bytes the string will need to be allocated. */
    bytes = vbytesfmt(lp, fmt);

    /* Allocating memory to the string. */
    buf = (char*) malloc(bytes);

    /* Creating the string. */
    vsprintf(buf, fmt, lp);

    /* Assuring a clean finish to the argument list. */
    va_end(lp);

    return buf;
}

/**
 * This function removes the char element from the string provided to it which
 * is at the element number/index provided to it.
 */
char* sdelelem(char* sp, unsigned elem)
{
    char* to_elem;      /* Chars from start of string to element to delete. */
    char* from_elem;    /* Chars from element to delete to end of string. */
    unsigned c;         /* The current char in the string. */

    /* Allocating memory. */
    to_elem     = (char*) malloc(sizeof(char) * (elem + 1));
    from_elem   = (char*) malloc(sizeof(char) * (strlen(sp) - elem));

    /* Storing the two sections of the string. */
    for (c = 0; c < strlen(sp); c++)
    {
        if (c < elem)
            to_elem[c] = sp[c];
        if (c > elem)
            from_elem[c] = sp[c];
    }
    to_elem[elem] = '\0';
    from_elem[strlen(sp) - elem - 1] = '\0';

    /* Recreating the string. */
    free(sp);
    sp = strfmt(sp, "%s%s", to_elem, from_elem);

    /* Cleaning up. */
    free(to_elem);
    free(from_elem);

    return sp;
}

/**
 * This function removes all cases of the provided char from the string at the
 * provided pointer.
 */
void sdelchar(char* sp, char remove)
{
    unsigned c;     /* Index of current char in the string. */

    /* Overwriting the unwanted characters. */
	for (c = 0; c < strlen(sp); c++)
	{
        if (sp[c] == remove)
        {
            sp = sdelelem(sp, c);

            /* Decrementing the index so we will check the replacement 
             * character. */
            c--;
        }
    }
}

/**
 * This function returns a string that represent the current time.
 * For reasons detailed in a comment within this function, you must
 * free() the string that this function returns.
 */
char* timestamp()
{
    time_t current_time;    /* The current time. */
    char* stamp;            /* The time stamp. */
    char* stamp_cpy;        /* A Copy of the time stamp. */

    /* Obtaining the current time. */
    if ((current_time = time(NULL)) == ((time_t) - 1))
    {
        /* An error occured so we're printing an error message to and exiting
         * the program. */
        fprintf(
                stderr, 
                "ERROR: In function timestamp(): "
                "Calender time is not available\n");

        exit(EXIT_FAILURE);
    }

    /* Converting time to local time format. */
    if ((stamp = ctime(&current_time)) == NULL)
    {
        /* An error occured converting so we're printing an error message
         * and exiting the program. */
        fprintf(
                stderr,
                "ERROR: In function timestamp(): "
                "Failure to convert the current time to a string.\n");

        exit(EXIT_FAILURE);
    }

    /* The string that ctime() returns is not one that should be be freed
     * with free() because the memory it uses was not allocated with malloc()
     * or a similar function. Because we are going to use sdelchar() to remove
     * the newline character that ctime() added to our timestamp, and
     * sdelchar() uses free() to remove chars from strings, we have to make
     * a copy of our stamp.
     * If this copy is not freed by the calling function, it will create a 
     * memory leak.
     */
    stamp_cpy = strfmt(stamp_cpy, "%s", stamp);

    /* Removing the newline character that was added by ctime(). */
    sdelchar(stamp_cpy, '\n');

    /* Returning the copy of the time stamp. */
    return stamp_cpy;
}

/**
 * This function outputs to a filestream.
 * It dynamically allocates the neccessary amount of memory to an internal
 * buffer that is based on the format string and argument list
 * parameters, then outputs the buffer to the filestream parameter.
 */
void fsout(FILE* fs, char *fmt, ...)
{
    char* _timestamp;
    char* buf;
    va_list lp;     /* Pointer to the list of arguments. */
    size_t bytes;   /* The number of bytes the string needs. */

    /* Pointing to the first argument. */
    va_start(lp, fmt);

    /* Getting the number of bytes the string will need to be allocated. */
    bytes = vbytesfmt(lp, fmt);

    /* Allocating memory to the string. */
    buf = (char*) malloc(bytes);

    /* Creating the string. */
    vsprintf(buf, fmt, lp);

    /* Assuring a clean finish to the argument list. */
    va_end(lp);

    _timestamp = timestamp();

    fprintf(fs, "[ %s ] %s", _timestamp, buf);

    free(_timestamp);
    free(buf);
}

/**
 * This function returns an intialised gui.
 */
gui* init_gui()
{
    /* Allocate memory. */
    gui* g = (gui*) malloc(sizeof(struct gui_data));

    /* Initialise SDL3. */
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fsout(stdout, "SDL init success\n");
    }
    else
    {
        fsout(stdout, "SDL init failure: %s\n", SDL_GetError());
    }

    /* Create an SDL3 window. */
    if ((g->w = SDL_CreateWindow("mywindow", 1250, 720, 0)) != NULL)
    {
        fsout(stdout, "SDL window creation success\n");
    }
    else
    {
        fsout(stdout, "SDL window creation failure: %s\n", SDL_GetError());
    }

    /* Create an SDL3 renderer. */
    if ((g->r = SDL_CreateRenderer(g->w, NULL)) != NULL)
    {
        fsout(stdout, "SDL renderer creation success\n");
    }
    else
    {
        fsout(stdout, "Create renderer failure: %s\n", SDL_GetError());
    }

    /* Return the gui. */
    return g;
}

/**
 * This function runs the gui supplied to it.
 */
gui* exec_gui(gui* g)
{
    SDL_Event event; // Stores input
    bool running = true; // Whether the program should be running.

    /* Run the program. */
    while (running)
    {
        /* Store input events. */
	    while(SDL_PollEvent(&event))
	    {
            /* Determine what type of event happened. */
	        switch (event.type)
	        {
                /* Exit the program if the mouse button is released. */
	            case SDL_EVENT_MOUSE_BUTTON_UP:
	                running = false;
	                break;
	        }
	    }

        /* Render the program. */
	    SDL_RenderClear(g->r);
	    SDL_RenderPresent(g->r);
    }

    /* Return the gui. */
    return g;
}

/**
 * This function cleans up and exits the gui supplied to it.
 */
void term_gui(gui* g)
{
    /* Print status message. */
    fsout(stdout, "Exiting gui\n");

    /* Clean everything up. */
    SDL_DestroyRenderer(g->r);
    SDL_DestroyWindow(g->w);
    SDL_Quit();
}
