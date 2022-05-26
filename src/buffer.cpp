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

void Buffer::deleteLine(int n)
{
    lines.erase(lines.begin() + n);
}

void Buffer::deleteLine(string s)
{
    if (!s.size())
        return;

    if (tokenize(s, ":"))
    {
        lines.erase(lines.begin() + stoi(inText[0]) - 1, lines.begin() + stoi(inText[1]));
        return;
    }

    tokenize(s, ", ");
    for (int i = 0; i < inText.size(); ++i)
    {
        if (stoi(inText[i]) - i <= lines.size())
            lines.erase(lines.begin() + stoi(inText[i]) - i - 1);
    }

    inText.clear();
}

vector<int> Buffer::computePrefix(string pat)
{
    vector<int> F(pat.size());
    for(int i = 1,k = 0; i < pat.size(); ++i){
 
        while (k > 0 and pat[i] != pat[k])
            k = F[k - 1];
 
        if(pat[k] == pat[i])
            F[i] = ++k;
        else F[i] = k;
    }
    return F;
}

void Buffer::KMP(string &s, string &pat, int row)
{
    vector<int> F = computePrefix(pat);
    for(int i = 0,k = 0; i < s.size(); i++){
        while (k > 0 and pat[k] != s[i])
            k = F[k - 1];
 
        if(s[i] == pat[k])
            ++k;
 
        if(k == pat.size()){
            outKMP.push_back(make_pair(row, i-pat.size()+1));
            k = F[k - 1];
        }
    }
}
void Buffer::findAll(string pattern) // improve request : string automata
{
    if (!pattern.size())
        return;

    outKMP.clear();

    for (int i = 0; i < lines.size(); i++)
        KMP(lines[i], pattern, i);
}

void Buffer::findReplace(string pattern) // improve request : string automata
{
    if (!pattern.size())
        return;

    tokenize(pattern, ", ");

    findAll(inText[0]);
    reverse(outKMP.begin(), outKMP.end());
    for (auto i : outKMP)
    {
        lines[i.first].erase(i.second, inText[0].size());
        lines[i.first].insert(i.second, inText[1]);
    }
    inText.clear();
}

bool Buffer::tokenize(string s, string del = " ")
{
    int start = 0;
    int end = s.find(del);
    inText.clear();
    while (end != -1)
    {
        inText.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    inText.push_back(s.substr(start, end - start));
    return (inText.size() > 1);
}

void Buffer::updateLine(string text, int location)
{
    lines[location].erase();
    lines[location] = move(text);
}

string Buffer::getLine(int location)
{
    return lines[location];
}