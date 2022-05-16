#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include "../lib/buffer.h"

enum modes{
    QUIT = 0,
    NORMAL = 1,
    INSERT = 2
};

class Editor
{
private:
    int row, column;
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

public:
    Editor(string);
    int getMode();
    void handleEvent(int);
    void printBuffer();
    void printStatusBar();
    void updateStatus();
};

#endif