#include <iostream>
#include <string>
#include <cctype> // for isxdigit and isspace
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

int priority(const string& op) {
    if (op == "+")
    {
        return 0;
    }

    if (op == "-")
    {
        return 0;
    }

    if (op == "*")
    {
        return 1;
    }

    if (op == "/")
    {
        return 1;
    }
}

vector<string> tokenization(const string& input) {
    vector<string> tokens;
    string b;
    for (size_t i = 0; i < input.length(); i++) {
        char ch = input[i];

        if (isxdigit(ch)) {
            b += ch;
        } else if (isspace(ch)) {
            if (!b.empty() && b != "-") {
                tokens.push_back(b);
                b.clear();
            }
        } else {
            if (!b.empty() && b != "-") {
                tokens.push_back(b);
                b.clear();
            }
            tokens.push_back(string(1, ch)); // Convert char to string and append
        }
    }

    if (!b.empty()) tokens.push_back(b);
    return tokens;
}

void processToken(string token, vector<string>& postFix, stack<string>& opStack) {
    bool isNumber = true;
    for (int i=0; i < token.length(); i++) {
        if (!isdigit(token[i])) isNumber = false;
    }

    if (isNumber) {
        postFix.push_back(token);
    }

    else {
        while (!opStack.empty() && priority(opStack.top()) >= priority(token)) {
            postFix.push_back(opStack.top());
            opStack.pop();
        }
        opStack.push(token);
    }
}

vector<string> postFix(vector<string> tokens) {
    vector<string> postFix;
    stack<string> opStack;
    for (int i = 0; i < tokens.capacity(); i++) {
        processToken(tokens[i], postFix, opStack);
    }

    while (!opStack.empty()) {
        postFix.push_back(opStack.top());
        opStack.pop();
    }

    return postFix;
}

void output(const vector<string>& input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << " ";
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Enter: " << endl;
    getline(cin, input);
    vector<string> tokens = tokenization(input);
    cout << "Tokenization:" << endl;
    output(tokens);

    cout << "PostFix: " << endl;
    vector<string> postfix = postFix(tokens);
    output(postfix);

    return 0;
}
