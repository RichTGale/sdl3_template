/**
 * main.c
 *
 * This file is the entry point for a graphical application template that uses
 * SDL3.
 *
 * Date written was 14 December 2025
 * Written by Richard Gale.
 */

#include <stdbool.h>
#include <string.h>

#include "gui.h"


/**
 * This function is the entry point for the program.
 */
int main(int argc, char* argv[])
{
    gui* g;
    int w = 1250;
    int h = 720;
    bool valid_args = true;
    bool use_ttf = false;

    /* Parse program arguments. */
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--width"))
        {
            if (!(w = atoi(argv[i + 1])))
            {
                fsout(stdout, "Arg conversion failure\n");
                valid_args = false;
            }
        }
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--height"))
        {
            if (!(h = atoi(argv[i + 1])))
            {
                fsout(stdout, "Arg conversion failure\n");
                valid_args = false;
            }
        }
        if (!strcmp(argv[i], "--ttf"))
        {
            use_ttf = true;
        }
    }

    if (valid_args)
    {
	    /* Create and initialise a gui. */
	    g = init_gui(w, h);
        
        if (use_ttf)
        {
            g = init_ttf(g);
        }
	
	    /* Run the gui. */
	    exec_gui(g);
	
	    /* Clean up. */
	    term_gui(g);
    }

    /* Exit the program. */
    return 0;
}
