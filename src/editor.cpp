#include "../lib/prompt.h"
#include "../lib/editor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <dirent.h>

#define BACKSPACE 127
#define SPACE 32
#define ENTER 10
#define TAB 9
#define ESC 27
#define NAME_LIMIT 256
#define el '\n'

Editor::Editor(string fileName)
{
    row = 0;
    column = 0;
    startIndex = 0;
    LINE_NUMBER_SIZE = 3;
    mode = NORMAL;
    status = " Normal Mode";
    this->fileName = fileName;

    if (this->fileName.size() > 3 && this->fileName.substr(this->fileName.size() - 3) == ".md")
        markdownFlag = true;

    buffer = new Buffer();

    if (!this->fileName.size())
        buffer->appendLine("");
    else
    {
        isSplashScreen = false;
        curs_set(1);

        ifstream inFile(this->fileName.c_str());
        if (inFile.is_open())
        {
            string inLine;
            while (!inFile.eof())
            {
                getline(inFile, inLine);
                buffer->appendLine(inLine);
            }
        }
        else
        {
            cerr << "Cannot open file: '" << this->fileName << "'" << el;
            buffer->appendLine("");
        }
    }    
}

void Editor::undo()
{
    if(!history.empty()) {
        buffer->lines = history.top();
        history.pop();
        row = cursorHistory.top().first;
        column = cursorHistory.top().second;
        cursorHistory.pop();
    }
}

void Editor::updateHistory()
{
    history.push(buffer->lines);
    cursorHistory.push(make_pair(row, column));
}

void Editor::updateStatus()
{
    switch (mode)
    {
    case NORMAL:
        status = " Normal Mode";
        break;
    case INSERT:
        status = " -- INSERT --";
        savedFlag = false;
        break;
    case QUIT:
        status = " Exiting";
        break;
    }

    if (savedFlag)
        status = savedStatus;

    status += "\tROW: " + to_string(row + 1) + "\tCOL: " + to_string(column + 1) + "\tNumber of Lines: " + to_string(buffer->getNumOfLines()) + ' ';
}

int Editor::getMax(int a, int b)
{
    if (a < b)
        return b;

    return a;
}

void Editor::handleEvent(int event)
{
    if (isSplashScreen)
    {
        isSplashScreen = false;
        curs_set(1);
        clear();
        refresh();
    }
    switch (event)
    {
    case KEY_LEFT:
        moveLeft();
        return;
    case KEY_RIGHT:
        moveRight();
        return;
    case KEY_UP:
        moveUp();
        return;
    case KEY_DOWN:
        moveDown();
        return;
    }
    switch (mode)
    {
    case NORMAL:
        switch (event)
        {
        case 'k':
            if (row)
            {
                updateHistory();
                swap(buffer->lines[row], buffer->lines[row - 1]);
                moveUp();
            }
            break;
        case 'j':
            if (row < buffer->lines.size() - 1)
            {
                updateHistory();
                swap(buffer->lines[row], buffer->lines[row + 1]);
                moveDown();
            }
            break;
        case 'q':
            clear();
            refresh();
            if (boolPrompt("Are you sure you want to quit?"))
                mode = QUIT;
            break;
        case 'i':
            mode = INSERT;
            break;
        case 's':
            saveFile();
            savedFlag = true;
            break;
        case 'd':
            updateHistory();
            if (row)
            {
                buffer->deleteLine(row);
                moveUp();
            }
            else
            {
                column = 0;
                buffer->lines[row].erase();
            }
            savedFlag = false;
            break;
        case 'x':
            if (buffer->lines[row].size() > column)
            {
                updateHistory();
                buffer->lines[row].erase(buffer->lines[row].begin() + column);
                savedFlag = false;
            }
            break;
        case KEY_HOME:
            row = 0;
            column = 0;
            startIndex = 0;
            break;
        case KEY_END:
            row = buffer->getNumOfLines() - 1;
            column = getMax(0, buffer->lines[row].size());
            startIndex = row - LINES + 2;
            break;
        case 'u':
            undo();
            break;
        }
        break;
    case INSERT:
        switch (event)
        {
        case ESC:
            mode = NORMAL;
            break;
        case BACKSPACE:
        case KEY_BACKSPACE:
            updateHistory();
            if (!column)
            {
                if (row)
                {
                    column = buffer->lines[row - 1].length();
                    buffer->lines[row - 1] += buffer->lines[row];
                    buffer->deleteLine(row);
                    moveUp();
                }
            }
            else
                buffer->lines[row].erase(--column, 1);

            break;
        case KEY_DC:
            updateHistory();
            if (column == buffer->lines[row].length() && !(row == buffer->lines.size() - 1))
            {
                buffer->lines[row] += buffer->lines[row + 1];
                buffer->deleteLine(row + 1);
            }
            else
            {
                buffer->lines[row].erase(column, 1);
            }
            break;
        case KEY_ENTER:
        case ENTER:
            updateHistory();
            if (column < buffer->lines[row].length())
            {
                buffer->insertLine(buffer->lines[row].substr(column, buffer->lines[row].length() - column), row + 1);
                buffer->lines[row].erase(column, buffer->lines[row].length() - column);
            }
            else
                buffer->insertLine("", row + 1);
            column = 0;
            moveDown();
            break;
        case KEY_RESIZE:
            break;
        case KEY_BTAB:
        case KEY_CTAB:
        case KEY_STAB:
        case KEY_CATAB:
        case TAB:
            for (int i = 0; i < 4; i++)
                handleEvent((int)' ');
            break;
        default:
            updateHistory();
            if(column == COLS - LINE_NUMBER_SIZE - 1)
                handleEvent(ENTER);
            buffer->lines[row].insert(column, 1, char(event));
            moveRight();
            selfClosingBrackets((char)(event));
            if (markdownFlag && (char)event == '-' && buffer->lines[row].size() > column + 1 && !(buffer->lines[row][column] == ' '))
                handleEvent((int)' ');
            break;
        }
        break;
    }
}

bool Editor::validColumn(int column)
{
    return (column + 1 < COLS && column < buffer->lines[row].length());
}

bool Editor::validRow(int row)
{
    return (row + 1 < buffer->lines.size());
}

void Editor::moveLeft()
{
    if (column)
    {
        column--;
        move(row, column);
    }
    else
    {
        if (row)
        {
            row--;
            column = buffer->lines[row].length();
            move(row, column);
        }
    }
}

void Editor::moveRight()
{
    if (validColumn(column))
    {
        column++;
        move(row, column);
    }
    else
    {
        if (validRow(row))
        {
            row++;
            column = 0;
            move(row, column);
        }
    }
}

void Editor::moveUp()
{
    if (row)
    {
        row--;

        if (row < startIndex)
            startIndex = row;

        if (column >= buffer->lines[row].length())
            column = buffer->lines[row].length();

        move(row, column);
    }
}

void Editor::moveDown()
{
    if (validRow(row))
    {
        row++;
        if (row == startIndex + LINES - 1)
            startIndex++;

        if (column >= buffer->lines[row].length())
            column = buffer->lines[row].length();

        move(row, column);
    }
}

void Editor::printLineNumber(string lineNumber)
{
    attron(COLOR_PAIR(3));
    mvprintw(stoi(lineNumber) - startIndex - 1, 0, lineNumber.c_str());
    clrtoeol();
    attroff(COLOR_PAIR(3));
}
void Editor::printBuffer()
{
    if (isSplashScreen)
        return;

    LINE_NUMBER_SIZE = to_string(buffer->getNumOfLines()).size() + 2;

    for (int i = 0; i < LINES - 1; i++)
    {
        if (i + startIndex >= buffer->lines.size())
            mvaddch(i, 0, '~');
        else
        {
            printLineNumber(to_string((i + startIndex + 1)));
            if (markdownFlag && buffer->lines[i + startIndex].substr(0, 2) == "# ")
            {
                mvprintw(i, LINE_NUMBER_SIZE, buffer->lines[i + startIndex].substr(0, 2).c_str());
                attron(COLOR_PAIR(1));
                mvprintw(i, LINE_NUMBER_SIZE + 2, buffer->lines[i + startIndex].substr(2).c_str());
                attroff(COLOR_PAIR(1));
            }
            else if (markdownFlag && buffer->lines[i + startIndex].substr(0, 2) == "- ")
            {
                mvprintw(i, LINE_NUMBER_SIZE, buffer->lines[i + startIndex].substr(0, 2).c_str());
                attron(COLOR_PAIR(2));
                mvprintw(i, LINE_NUMBER_SIZE + 2, buffer->lines[i + startIndex].substr(2).c_str());
                attroff(COLOR_PAIR(2));
            }
            else
                mvprintw(i, LINE_NUMBER_SIZE, buffer->lines[i + startIndex].c_str());
        }
        clrtoeol();
    }
    move(row - startIndex, column + LINE_NUMBER_SIZE);
}

void Editor::selfClosingBrackets(char key)
{
    switch (key)
    {
    case '(':
        handleEvent((int)')');
        moveLeft();
        break;
    case '[':
        handleEvent((int)(']'));
        moveLeft();
        break;
    case '{':
        handleEvent(int('}'));
        moveLeft();
        break;
    default:
        break;
    }
}
void Editor::printSplashScreen()
{
    attron(A_BOLD);
    mvprintw(LINES / 2 - 6, COLS / 2 - 5, "femto v0.1");
    attroff(A_BOLD);
    mvprintw(LINES / 2 - 5, COLS / 2 - 22, "femto is open source and freely distributable");
    mvprintw(LINES / 2 - 3, COLS / 2 - 7, "i: Insert Mode");
    mvprintw(LINES / 2 - 2, COLS / 2 - 3, "q: Quit");
    mvprintw(LINES / 2 - 1, COLS / 2 - 3, "s: Save");
    mvprintw(LINES / 2, COLS / 2 - 9, "x: Delete Character");
    mvprintw(LINES / 2 + 1, COLS / 2 - 7, "d: Delete Line");
    mvprintw(LINES / 2 + 2, COLS / 2 - 11, "j: Swap Lines Downwards");
    mvprintw(LINES / 2 + 3, COLS / 2 - 10, "k: Swap Lines Upwards");
    mvprintw(LINES / 2 + 4, COLS / 2 - 10, "Home: Go to the start");
    mvprintw(LINES / 2 + 5, COLS / 2 - 9, "End: Go to the end");
    refresh();
}
void Editor::printStatusBar()
{
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, status.c_str());
    clrtoeol();
    if (getMode() == NORMAL)
        mvprintw(LINES - 1, COLS - 21, " PRESS Q TO QUIT ");
    else
        mvprintw(LINES - 1, COLS - 23, " PRESS ESC TO QUIT ");

    clrtoeol();
    attroff(A_REVERSE);
}

void Editor::saveFile()
{
    if (fileName == "")
    {
        int counter = 1;
        fileName = "untitled";

        if (auto directory = opendir("./"))
        {
            while (auto dummyFile = readdir(directory))
            {
                if (!dummyFile->d_name || dummyFile->d_name[0] == '.')
                    continue;

                if (fileName + to_string(counter) == dummyFile->d_name)
                    counter++;
            }

            closedir(directory);
        }

        fileName += to_string(counter);
    }

    ofstream outFile(fileName.c_str());
    if (outFile.is_open())
    {
        for (int i = 0; i < buffer->lines.size(); i++)
            outFile << buffer->lines[i] << endl;

        savedStatus = " Saved as: " + fileName;
    }
    else
        savedStatus = " Error: Cannot open file for writing!";

    outFile.close();
}

int Editor::getMode()
{
    return mode;
}
