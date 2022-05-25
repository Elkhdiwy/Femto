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
    vector<string> inText;
    vector<pair<int, int>> outKMP;

    void insertLine(string, int);
    void appendLine(string);
    void deleteLine(string);
    void deleteLine(int);
    vector<int> computePrefix(string &);
    void KMP(string &, string &, int);
    void findAll(string);
    void findReplace(string);
    bool tokenize(string, string);
    string remTabs(string); // substitute tabs with 4 spaces
    void updateLine(string, int);
    string getLine(int);
};

#endif