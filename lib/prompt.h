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

void messagePrompt(string, char *, int);
int boolPrompt(string);
int centerX(int);
int centerY(int);
WINDOW *initPrompt(string, int, int);
void destPrompt(WINDOW *);

#endif
