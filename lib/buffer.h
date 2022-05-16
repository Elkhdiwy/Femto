#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

using namespace std;

class Buffer
{
public:
    Buffer();
    vector<string> lines;

    void insertLine(string, int);
    void appendLine(string);
    void removeLine(int);
    void deleteLine(int);
    int getNumOfLines();

    string remTabs(string); // substitute tabs with 4 spaces
};

#endif