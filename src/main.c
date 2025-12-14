/**
 * main.c
 *
 * This file is the entry point for a graphical application template that uses
 * SDL3.
 *
 * Date written was 14 December 2025
 * Written by Richard Gale.
 */

#include "gui.h"

/**
 * This function is the entry point for the program.
 */
int main(int argc, char *argv[])
{
    /* Create and initialise a gui. */
    gui* g = init_gui();

    /* Run the gui. */
    exec_gui(g);

    /* Clean up. */
    term_gui(g);

    /* Exit the program. */
    return 0;
}
