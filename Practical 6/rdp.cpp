#include <iostream>
#include <string>

using namespace std;

string input;
int index = 0;

bool S();
bool L();
bool L_prime();

bool match(char expected) {
    if (index < input.length() && input[index] == expected) {
        index++;
        return true;
    }
    return false;
}

// S → ( L ) | a
bool S() {
    int temp = index;
    if (match('(')) {
        if (L() && match(')')) {
            return true;
        }
        index = temp;
    }
    if (match('a')) {
        return true;
    }
    return false;
}
// L → S L’
bool L() {
    if (S()) {
        return L_prime();
    }
    return false;
}
// L’ → , S L’ | ϵ
bool L_prime() {
    int temp = index;
    if (match(',')) {
        if (S() && L_prime()) {
            return true;
        }
        index = temp;
    }
    return true; // ϵ (epsilon) case, always succeeds
}

int main() {
    cout << "Enter a string: ";
    cin >> input;
    index = 0;
    if (S() && index == input.length()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
    return 0;
}
