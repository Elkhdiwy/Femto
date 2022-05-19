#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include "../lib/buffer.h"

enum modes
{
    QUIT = 0,
    NORMAL = 1,
    INSERT = 2
};

class Editor
{
private:
    int row, column, startIndex, LINE_NUMBER_SIZE;
    Buffer *buffer;
    modes mode;
    string status, fileName, savedStatus;
    bool savedFlag = false;
    bool markdownFlag = false;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void saveFile();
    void printLineNumber(string);
    void selfClosingBrackets(char);
    int getMax(int, int);

public:
    Editor(string);
    bool isSplashScreen = true;
    int getMode();
    bool validColumn(int);
    bool validRow(int);
    void handleEvent(int);
    void printBuffer();
    void printStatusBar();
    void printSplashScreen();
    void updateStatus();
};

#endif