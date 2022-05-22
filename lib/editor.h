#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include <cstring>
#include <stack>
#include "../lib/buffer.h"

#define TEXT_LIMIT 256

enum modes
{
    QUIT = 0,
    NORMAL = 1,
    INSERT = 2,
    VISUAL = 3,
    FOUND = 4
};

class Editor
{
private:
    int row, column, startIndex, LINE_NUMBER_SIZE, lastKey, indexFound;
    char text[TEXT_LIMIT];
    Buffer *buffer;
    modes mode;
    string status, fileName, savedStatus, visualString, copiedString;
    bool savedFlag, markdownFlag, visualModeFlag, visualEdgeCaseFlag, foundFlag, yankedFlag;
    stack<vector<string>> undoHistory;
    stack<vector<string>> redoHistory;
    stack<pair<int, int>> undoCursorHistory;
    stack<pair<int, int>> redoCursorHistory;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void saveFile();
    void printLineNumber(string);
    void selfClosingBrackets(char);
    void undo();
    void redo();
    void updateHistory();
    void handleVisual(int);
    int getMax(int, int);
    int getMin(int, int);
    bool validColumn(int);
    bool validRow(int);
    int size(char *);

public:
    Editor(string);
    bool isSplashScreen;
    int getMode();
    void handleEvent(int);
    void printBuffer();
    void printStatusBar();
    void printSplashScreen();
    void updateStatus();
    void printVisual();
};

#endif