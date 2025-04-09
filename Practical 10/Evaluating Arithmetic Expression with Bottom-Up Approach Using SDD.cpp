#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <sstream>

using namespace std;

class ArithmeticEvaluator {
private:
    string input;
    size_t pos;

    // Helper functions
    char peek() {
        while (pos < input.size() && isspace(input[pos])) {
            pos++;
        }
        if (pos < input.size()) return input[pos];
        return '\0';
    }

    void consume() {
        pos++;
    }

    bool match(char expected) {
        if (peek() == expected) {
            consume();
            return true;
        }
        return false;
    }

    double parseNumber() {
        string numStr;
        while (isdigit(peek()) || peek() == '.') {
            numStr += peek();
            consume();
        }
        return stod(numStr);
    }

    // Grammar rules with semantic actions
    double parse_L() {
        double val = parse_E();
        if (peek() != '\0') {
            throw runtime_error("Unexpected characters at end of input");
        }
        return val;
    }

    double parse_E() {
        double val = parse_T();
        while (true) {
            if (match('+')) {
                val += parse_T();
            } else if (match('-')) {
                val -= parse_T();
            } else {
                break;
            }
        }
        return val;
    }

    double parse_T() {
        double val = parse_F();
        while (true) {
            if (match('*')) {
                val *= parse_F();
            } else if (match('/')) {
                double divisor = parse_F();
                if (divisor == 0) throw runtime_error("Division by zero");
                val /= divisor;
            } else {
                break;
            }
        }
        return val;
    }

    double parse_F() {
        double base = parse_G();
        if (match('^')) {
            double exponent = parse_F();
            return pow(base, exponent);
        }
        return base;
    }

    double parse_G() {
        if (match('(')) {
            double val = parse_E();
            if (!match(')')) {
                throw runtime_error("Missing closing parenthesis");
            }
            return val;
        }
        if (isdigit(peek())) {
            return parseNumber();
        }
        throw runtime_error("Unexpected character");
    }

public:
    double evaluate(const string& expr) {
        input = expr;
        pos = 0;
        try {
            return parse_L();
        } catch (const exception& e) {
            throw runtime_error("Invalid expression");
        }
    }
};

int main() {
    ArithmeticEvaluator evaluator;

    vector<string> testCases = {
        "(3 + 5) * 2", "3 + 5 * 2", "3 + 5 * 2 ^ 2", "3 + (5 * 2)", "3 + 5 ^ 2 * 2",
        "3 * (5 + 2)", "(3 + 5) ^ 2", "3 ^ 2 ^ 3", "3 ^ 2 + 5 * 2", "3 + ^ 5",
        "(3 + 5 * 2", "(3 + 5 * 2 ^ 2 - 8) / 4 ^ 2 + 6"
    };

    cout << "Arithmetic Expression Evaluation:\n";
    cout << "--------------------------------\n";
    for (const string& testCase : testCases) {
        cout << "Input: " << testCase << " => ";
        try {
            double result = evaluator.evaluate(testCase);
            cout << "Result: " << result << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    // Interactive mode
    cout << "\nEnter expressions to evaluate (or 'quit' to exit):\n";
    while (true) {
        cout << "> ";
        string input;
        getline(cin, input);
        if (input == "quit") break;

        try {
            double result = evaluator.evaluate(input);
            cout << "Result: " << result << endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
