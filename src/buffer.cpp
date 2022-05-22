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

vector<int> Buffer::computePrefix(string pattern)
{
    vector<int> longestPrefix = vector<int>(pattern.length());
    int i = 2, j = 0;
    longestPrefix[0] = -1;
    if (pattern.length() > 1)
        longestPrefix[1] = 0;

    while (i < pattern.length())
    {
        if (pattern[i - 1] == pattern[j])
        {
            longestPrefix[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0)
            j = longestPrefix[j];
        else
        {
            longestPrefix[i] = 0;
            i++;
        }
    }
    return longestPrefix;
}

void Buffer::KMP(string line, string pattern, int row)
{
    int m = 0, i = 0;
    vector<int> longestPrefix = computePrefix(pattern);
    while (m + i < line.length())
    {
        if (pattern[i] == line[m + i])
        {
            i++;
            if (i == pattern.length())
                outKMP.push_back({row, m});
        }
        else
        {
            m += i - longestPrefix[i];
            if (i > 0)
                i = longestPrefix[i];
        }
    }
}
void Buffer::findAll(string pattern) // improve request : string automata
{
    for (int i = 0; i < lines.size(); i++)
        KMP(lines[i], pattern, i);
}

void Buffer::findReplace(string pattern) // improve request : string automata
{
    tokenize(pattern, ",");
    findAll(inText[0]);
    for (auto i : outKMP)
    {
        lines[i.first].erase(i.second, inText[0].size());
        lines[i.first].insert(i.second, inText[1]);
    }
    inText.clear();
}

void Buffer::tokenize(string s, string del = " ")
{
    int start = 0;
    int end = s.find(del);
    while (end != -1)
    {
        inText.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    inText.push_back(s.substr(start, end - start));
}