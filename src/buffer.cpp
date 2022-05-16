#include "../lib/buffer.h"

Buffer::Buffer() {}

string Buffer::remTabs(string line)
{
    int tab = line.find("\t");
    if (tab == line.npos)
        return line;
    else
        return remTabs(line.replace(tab, 1, "    "));
}

void Buffer::insertLine(string line, int n)
{
    line = remTabs(line); 
    lines.insert(lines.begin() + n, line);
}

void Buffer::appendLine(string line)
{
    line = remTabs(line);
    lines.push_back(line);
}

void Buffer::deleteLine(int i)
{
    removeLine(i);
}

void Buffer::removeLine(int n)
{
    lines.erase(lines.begin() + n);
}

int Buffer::getNumOfLines()
{
    return lines.size();
}