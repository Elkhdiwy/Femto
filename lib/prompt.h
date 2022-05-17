#ifndef PROMPT_H
#define PROMPT_H

#include <ncurses.h>
#include <string>

using namespace std;

#define PROMPT_STRING_LINES 5
#define PROMPT_STRING_COLS 20

#define PROMPT_YESNO_LINES 5
#define PROMPT_YESNO_COLS 30

#define PROMPT_OFFX 1
#define PROMPT_OFFY 3

void prompt_string(string, string);
int prompt_yesno(string);
int center_x(int);
int center_y(int);
WINDOW *create_prompt(string, int, int);
void dest_prompt(WINDOW *);

#endif
