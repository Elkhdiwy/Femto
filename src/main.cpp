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

    if (!has_colors())
    {
        endwin();
        cerr << "Your terminal does not support color" << el;
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
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

    int event;
    Editor EventListener = Editor(fileName);

    init();

    while (EventListener.getMode())
    {
        EventListener.updateStatus();
        EventListener.printStatusBar();
        EventListener.printBuffer();
        event = getch();
        EventListener.handleEvent(event);
    }

    quit();

    return 0;
}