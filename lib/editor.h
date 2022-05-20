#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include <stack>
#include "../lib/buffer.h"

enum modes
{
    QUIT = 0,
    NORMAL = 1,
    INSERT = 2,
    VISUAL = 3
};

class Editor
{
private:
    int row, column, startIndex, LINE_NUMBER_SIZE, lastKey;
    Buffer *buffer;
    modes mode;
    string status, fileName, savedStatus, visualString;
    bool savedFlag, markdownFlag, visualModeFlag;
    stack <vector<string>> history;
    stack<pair<int,int>>cursorHistory;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void saveFile();
    void printLineNumber(string);
    void selfClosingBrackets(char);
    int getMax(int, int);
    void undo();
    void updateHistory();

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
    void printVisual();
};

#endif