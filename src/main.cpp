#include <ncurses.h>
#include <string>
#include <iostream>
#include "../lib/editor.h"

#define el '\n'

void init()
{
    // initialize ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    set_escdelay(0);
    curs_set(0);

    if (!has_colors())
    {
        endwin();
        cerr << "Your terminal does not support color" << el;
        exit(1);
    }

    // colors for syntax highlighting
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
}

void quit()
{
    refresh();
    endwin();
}

int main(int argc, char *argv[])
{
    string fileName = "";

    // if a filename is passed
    if (argc > 1)
    {
        fileName = string(argv[1]);
    }

    init();

    int event;
    Editor editor = Editor(fileName);

    while (editor.getMode())
    {
        if (editor.isSplashScreen)
            editor.printSplashScreen();
        editor.updateStatus();
        editor.printStatusBar();
        editor.printBuffer();
        event = getch();
        editor.handleEvent(event);
    }

        quit();

    return 0;
}