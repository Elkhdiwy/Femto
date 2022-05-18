#include "../lib/prompt.h"

int centerX(int width)
{
    return (COLS - width) / 2;
}

int centerY(int height)
{
    return (LINES - height) / 2;
}

WINDOW *initPrompt(string message, int height, int width)
{
    WINDOW *prompt = subwin(stdscr, height, width, centerY(height), centerX(width));
    werase(prompt);
    mvwprintw(prompt, 1, 1, message.c_str());
    wmove(prompt, 2, 0);
    whline(prompt, ACS_HLINE, 1000);
    box(prompt, 0, 0);
    wmove(prompt, PROMPT_OFFY, PROMPT_OFFX);
    return prompt;
}

void destPrompt(WINDOW *prompt)
{
    wborder(prompt, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    werase(prompt);
    wrefresh(prompt);
    delwin(prompt);
}

void messagePrompt(string message, char *name, int size)
{
    echo();
    WINDOW *prompt = initPrompt(message, PROMPT_STRING_LINES, PROMPT_STRING_COLS);
    wattron(prompt, A_REVERSE);
    wprintw(prompt, "                  ");
    wmove(prompt, PROMPT_OFFY, PROMPT_OFFX);
    wgetnstr(prompt, name, size);
    wattroff(prompt, A_REVERSE);

    destPrompt(prompt);
    noecho();
}

int boolPrompt(string message)
{
    int prompt_width = message.length() + 2;
    int yes_x = prompt_width / 2 - 8;
    int yes_y = 3;
    int no_x = prompt_width / 2 + 6;
    int no_y = 3;

    WINDOW *prompt = initPrompt(message, PROMPT_YESNO_LINES, prompt_width);

    curs_set(0);
    keypad(prompt, TRUE);

    int choice = 0;

    while (1)
    {
        if (choice == 0)
        {
            wattron(prompt, A_REVERSE);
            mvwprintw(prompt, yes_y, yes_x, "YES");
            wattroff(prompt, A_REVERSE);
            mvwprintw(prompt, no_y, no_x, "NO");
        }
        else
        {
            mvwprintw(prompt, yes_y, yes_x, "YES");
            wattron(prompt, A_REVERSE);
            mvwprintw(prompt, no_y, no_x, "NO");
            wattroff(prompt, A_REVERSE);
        }

        int ch = wgetch(prompt);
        switch (ch)
        {
        case KEY_LEFT:
        case KEY_RIGHT:
            choice = !choice;
            break;
        case 'y':
        case 'Y':
            choice = 0;
            goto end;
            break;
        case 'n':
        case 'N':
            choice = 1;
            goto end;
            break;
        case '\n':
            goto end;
            break;
        default:
            break;
        }
    }

end:
    destPrompt(prompt);
    curs_set(1);
    return !choice;
}
