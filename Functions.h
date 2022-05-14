#include <utility>
#include "iostream"
#include "vector"
#include "string"

using namespace std;

namespace Function {
    vector<string> load();//O(|changed words|)
    void save(vector<string> text);

    vector<string> Text;

    void addLine(const string& text) {
        Text.push_back(text);
    }

    void insertLine(const string& text, int location) {
        Text.insert(Text.begin() + location - 1, text);//O(n) 0(N/2)
    }

    void updateLine(string text, int location) {
        Text[location].erase();
        Text[location] = std::move(text);
    }

    string getLine(int line) {
        return Text[line];
    }

    void deleteLine(int line) {
        Text.erase(Text.begin() + line - 1);
    }

    vector<int> findAll(const string& text) // improve request : string automata
    {
        vector<int> ret;
        for (int i = 0; i < Text.size(); i++) {
            if (Text[i].find(text) != -1)
                ret.push_back(i);
        }
        // O(number of lines)
        return ret;
    }

    void Show() {
        for (const auto& i: Text) {
            for (auto j: i)
                cout << j;
            cout << endl;
        }
    }

    void findReplace(string text) // improve request : string automata
    {
        // automata time complexity : O(number of lines)
        for (auto &small: Text) {
            int x = small.find(text);
            while (x != -1) {
                int f = 0;
                for (int j = x; j < x + text.size(); j++)
                    small[j] = text[f++];

                x = small.find(text);
            }
        }
    }
};
