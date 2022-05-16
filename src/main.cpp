#include <ncurses.h>
#include "../lib/editor.h"
#include <string>
#include <iostream>

#define el '\n'

void init()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    set_escdelay(0);

    if(!has_colors())
	{	endwin();
		cerr << "Your terminal does not support color" << el;
		exit(1);
	}
    
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

void fini()
{
    refresh();
    endwin();
}

int main(int argc, char *argv[])
{
    string FileName = "";

    if (argc-1)
        FileName = string(argv[1]);

    int event;
    Editor EventListener = Editor(FileName);

    init();

    while (EventListener.getMode())
    {
        EventListener.updateStatus();
        EventListener.printStatusBar();
        EventListener.printBuffer();
        event = getch();
        EventListener.handleEvent(event);
    }

    fini();

    return 0;
}