#include "editor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <dirent.h>

#define BACKSPACE 127
#define ESC 27
#define ENTER 10
#define TAB 9
#define el '\n'

Editor::Editor(string fileName)
{
    row = 0;
    column = 0;
    mode = NORMAL;
    status = "Normal Mode";
    this->fileName = fileName;

    if(this->fileName.size() > 3 && this->fileName.substr(this->fileName.size()-3) == ".md")
        markdownFlag = true;

    buffer = new Buffer();

    if (!this->fileName.size())
        buffer->appendLine("");
    else
    {
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

void Editor::updateStatus()
{
    switch (mode)
    {
    case NORMAL:
        status = "Normal Mode";
        break;
    case INSERT:
        status = "-- INSERT --";
        savedFlag = false;
        break;
    case QUIT:
        status = "Exiting";
        break;
    }

    if (savedFlag)
        status = savedStatus;

    status += "\tROW: " + to_string(row) + "\tCOL: " + to_string(column) + "\tNumber of Lines: " + to_string(buffer->getNumOfLines());
}

void Editor::handleEvent(int event)
{
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
        case 'j':
            if(row) {
                swap(buffer->lines[row], buffer->lines[row - 1]);
                moveUp();
            }
            break;
        case 'k':
            if(row < buffer->lines.size() - 1) {
                swap(buffer->lines[row], buffer->lines[row + 1]);
                moveDown();
            }
            break;
        case 'q':
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
                buffer->lines[row].erase(buffer->lines[row].begin() + column);
                savedFlag = false;
            }
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
            if (!column)
            {
                if (row > 0)
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
            if (column == buffer->lines[row].length() && !(row == buffer->lines.size() - 1))
            {
                buffer->lines[row] += buffer->lines[row + 1];
                buffer->deleteLine(row + 1);
            }
            else
                buffer->lines[row].erase(column, 1);
            break;
        case KEY_ENTER:
        case ENTER:
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
            buffer->lines[row].insert(column, 4, ' ');
            column += 4;
            break;
        default:
            buffer->lines[row].insert(column, 1, char(event));
            column++;
            if (markdownFlag && !(column - 1) && (char(event) == '#' || char(event) == '-'))
                handleEvent((int)' ');
            break;
        }
        break;
    }
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
    if (column + 1 < COLS && column < buffer->lines[row].length())
    {
        column++;
        move(row, column);
    }
    else
    {
        if (row + 1 < LINES - 1 && row + 1 < buffer->lines.size())
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
        if (column >= buffer->lines[row].length())
            column = buffer->lines[row].length();

        move(row, column);
    }
}

void Editor::moveDown()
{
    if (row + 1 < LINES - 1 && row + 1 < buffer->lines.size())
    {
        row++;
        if (column >= buffer->lines[row].length())
            column = buffer->lines[row].length();

        move(row, column);
    }
}

void Editor::printBuffer()
{
    for (int i = 0; i < LINES - 1; i++)
    {
        if (i >= buffer->lines.size())
        {
            move(i, 0);
            clrtoeol();
        }
        else
        {
            if (markdownFlag)
            {
                if (buffer->lines[i].substr(0, 2) == "# ")
                {
                    mvprintw(i, 0, buffer->lines[i].substr(0, 2).c_str());
                    attron(COLOR_PAIR(1));
                    mvprintw(i, 2, buffer->lines[i].substr(2).c_str());
                    attroff(COLOR_PAIR(1));
                }
                else if (buffer->lines[i].substr(0, 2) == "- ")
                {
                    mvprintw(i, 0, buffer->lines[i].substr(0, 2).c_str());
                    attron(COLOR_PAIR(2));
                    mvprintw(i, 2, buffer->lines[i].substr(2).c_str());
                    attroff(COLOR_PAIR(2));
                }
                else
                    mvprintw(i, 0, buffer->lines[i].c_str());
            }
            else
                mvprintw(i, 0, buffer->lines[i].c_str());
        }
        clrtoeol();
    }
    move(row, column);
}

void Editor::printStatusBar()
{
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, status.c_str());
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
        {
            outFile << buffer->lines[i] << endl;
        }
        savedStatus = "File saved!";
    }
    else
    {
        savedStatus = "Error: Cannot open file for writing!";
    }
    outFile.close();
}

int Editor::getMode()
{
    return mode;
}