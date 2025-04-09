
#include <bits/stdc++.h>
using namespace std;
void computeFirst(const map<char, vector<string>>& grammar, map<char, set<char>>& first, char symbol);
void computeFollow(const map<char, vector<string>>& grammar, map<char, set<char>>& first, map<char, set<char>>& follow, char symbol);
void computeFirst(const map<char, vector<string>>& grammar, map<char, set<char>>& first, char symbol) {
    if (!first[symbol].empty()) return;

    for (const string& production : grammar.at(symbol)) {
        for (char ch : production) {
            if (islower(ch) || ch == '(' || ch == ')') {
                first[symbol].insert(ch);
                break;
            } else if (isupper(ch)) {
                computeFirst(grammar, first, ch);
                for (char f : first[ch]) {
                    if (f != 'e') first[symbol].insert(f);
                }
                if (first[ch].find('e') == first[ch].end()) break;
            } else if (ch == 'e') {
                first[symbol].insert('e');
                break;
            }
        }
    }
}
void computeFollow(const map<char, vector<string>>& grammar, map<char, set<char>>& first, map<char, set<char>>& follow, char symbol) {
    static bool initialized = false;
    if (!initialized) {
        follow['S'].insert('$');
        initialized = true;
    }

    for (const auto& pair : grammar) {
        char nonTerminal = pair.first;
        const vector<string>& productions = pair.second;

        for (const string& production : productions) {
            size_t pos = production.find(symbol);

            while (pos != string::npos) {
                bool addFollow = true;

                if (pos + 1 < production.size()) {
                    char next = production[pos + 1];

                    if (islower(next) || next == '(' || next == ')') {
                        follow[symbol].insert(next);
                        addFollow = false;
                    } else if (isupper(next)) {
                        for (char f : first[next]) {
                            if (f != 'e') follow[symbol].insert(f);
                        }
                        if (first[next].find('e') != first[next].end()) {
                            addFollow = true;
                        } else {
                            addFollow = false;
                        }
                    }
                }

                if (addFollow) {
                    for (char f : follow[nonTerminal]) {
                        follow[symbol].insert(f);
                    }
                }

                pos = production.find(symbol, pos + 1);
            }
        }
    }
}
int main() {

    map<char, vector<string>> grammar = {
        {'S', {"ABC", "D"}},
        {'A', {"a", "e"}},
        {'B', {"b", "e"}},
        {'C', {"(S)", "c"}},
        {'D', {"AC"}}
    };
map<char, set<char>> first, follow;
    for (const auto& pair : grammar) {
        char nonTerminal = pair.first;
        computeFirst(grammar, first, nonTerminal);
    }
    for (const auto& pair : grammar) {
        char nonTerminal = pair.first;
        computeFollow(grammar, first, follow, nonTerminal);
    }
    cout << "FIRST Sets:" << endl;
    for (const auto& pair : first) {
        cout << "FIRST(" << pair.first << ") = { ";
        for (char f : pair.second) {
            cout << f << " ";
        }
        cout << "}" << endl;
    }
    cout << "\nFOLLOW Sets:" << endl;
    for (const auto& pair : follow) {
        cout << "FOLLOW(" << pair.first << ") = { ";
        for (char f : pair.second) {
            cout << f << " ";
        }
        cout << "}" << endl;
    }
    return 0;
}
