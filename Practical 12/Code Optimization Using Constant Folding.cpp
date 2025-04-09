#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

// Function to evaluate simple constant expressions
string evaluateExpression(const string& expr) {
    istringstream iss(expr);
    vector<string> tokens;
    string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    vector<string> newTokens;
    int i = 0;
    while (i < tokens.size()) {
        if (i + 2 < tokens.size() && isdigit(tokens[i][0]) && isdigit(tokens[i + 2][0])) {
            int left = stoi(tokens[i]);
            int right = stoi(tokens[i + 2]);
            char op = tokens[i + 1][0];
            int result;
            if (op == '+') result = left + right;
            else if (op == '-') result = left - right;
            else if (op == '*') result = left * right;
            else if (op == '/') result = left / right;
            newTokens.push_back(to_string(result));
            i += 3;
        } else {
            newTokens.push_back(tokens[i]);
            i++;
        }
    }

    ostringstream oss;
    for (const string& t : newTokens) {
        oss << t << " ";
    }
    return oss.str();
}

int main() {
    vector<string> testcases = {
        "5 + x - 3 * 2",
        "2 + 3 * 4 - 1",
        "x + ( 3 * 5 ) - 2",
        "( 22 / 7 ) * r * r"
    };

    for (const string& expr : testcases) {
        cout << "\nOriginal Expression: " << expr << "\n";
        cout << "Optimized Expression: " << evaluateExpression(expr) << "\n";
    }

    return 0;
}
