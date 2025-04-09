#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempCount = 1;

string newTemp() {
    return "t" + to_string(tempCount++);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

vector<string> infixToPostfix(const string &expr) {
    vector<string> postfix;
    stack<char> opStack;
    istringstream iss(expr);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            postfix.push_back(token);
        } else if (token == "(") {
            opStack.push('(');
        } else if (token == ")") {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(token[0])) {
                postfix.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(token[0]);
        }
    }
    while (!opStack.empty()) {
        postfix.push_back(string(1, opStack.top()));
        opStack.pop();
    }
    return postfix;
}

string generateQuadruples(const vector<string> &postfix) {
    stack<string> s;
    for (const string &token : postfix) {
        if (isdigit(token[0])) {
            s.push(token);
        } else {
            string op2 = s.top(); s.pop();
            string op1 = s.top(); s.pop();
            string res = newTemp();
            quadruples.push_back({token, op1, op2, res});
            s.push(res);
        }
    }
    return s.top();
}

void printQuadruples() {
    cout << "\nQuadruple Table:\n";
    cout << left << setw(10) << "Operator" << setw(10) << "Operand1" << setw(10) << "Operand2" << setw(10) << "Result" << endl;
    cout << string(40, '-') << endl;
    for (const auto &q : quadruples) {
        cout << left << setw(10) << q.op << setw(10) << q.arg1 << setw(10) << q.arg2 << setw(10) << q.result << endl;
    }
}

int main() {
    vector<string> testcases = {
        "9 + 42 * 8",
        "5 + 6 - 3",
        "7 - ( 8 * 2 )",
        "( 9 - 3 ) + ( 5 * 4 / 2 )",
        "( 3 + 5 * 2 - 8 ) / 4 - 2 + 6",
        "86 / 2 / 3"
    };

    for (const string &expr : testcases) {
        quadruples.clear();
        tempCount = 1;
        cout << "\nExpression: " << expr << "\n";
        vector<string> postfix = infixToPostfix(expr);
        generateQuadruples(postfix);
        printQuadruples();
    }
    return 0;
}
