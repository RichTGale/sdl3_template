#include "gui.h"

int main(int argc, char *argv[])
{
    gui* g = init_gui();

    exec_gui(g);

    term_gui(g);

    return 0;
}
