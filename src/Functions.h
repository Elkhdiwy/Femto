#include <utility>
#include "iostream"
#include "vector"
#include "string"

using namespace std;

namespace Function
{
    vector<string> load(); // O(|changed words|)
    void save(vector<string> text);

    vector<string> Text;

    void addLine(const string &text)
    {
        Text.push_back(text);
    }

    void insertLine(const string &text, int location)
    {
        Text.insert(Text.begin() + location - 1, text); // O(n) 0(N/2)
    }

    void updateLine(string text, int location)
    {
        Text[location].erase();
        Text[location] = std::move(text);
    }

    string getLine(int line)
    {
        return Text[line];
    }
    void deleteLine(int line)
    {
        Text.erase(Text.begin() + line - 1);
    }
    
    vector<int> buildTable(string &w)
    {
        vector<int> t = vector<int>(w.length());
        int i = 2, j = 0;
        t[0] = -1;
        if (w.length() > 1)
            t[1] = 0;

        while (i < w.length())
        {
            if (w[i - 1] == w[j])
            {
                t[i] = j + 1;
                i++;
                j++;
            }
            else if (j > 0)
                j = t[j];
            else
            {
                t[i] = 0;
                i++;
            }
        }
        return t;
    }

    vector<pair<int, int>> KMP(string &s, string &w, vector<pair<int, int>> &ans, int line)
    {
        int m = 0, i = 0;
        vector<int> t = buildTable(w);
        while (m + i < s.length())
        {
            if (w[i] == s[m + i])
            {
                i++;
                if (i == w.length())
                {
                    ans.push_back({line, m});
                }
            }
            else
            {
                m += i - t[i];
                if (i > 0)
                    i = t[i];
            }
        }
        return ans;
    }
    vector<pair<int, int>> findAll(string &text) // improve request : string automata
    {
        vector<int> ret = buildTable(text);
        vector<pair<int, int>> ans;
        for (int i = 0; i < Text.size(); i++)
        {
            KMP(Text[i], text, ans, i);
        }
        // O(number of lines)
        return ans;
    }

    void Show()
    {
        for (const auto &i : Text)
        {
            for (auto j : i)
                cout << j;
            cout << endl;
        }
    }

    void findReplace(string text) // improve request : string automata
    {
        auto x = findAll(text);
        for (auto i : x)
        {
            Text[i.first].erase(i.second, i.second + text.size());
        }
    }
};
