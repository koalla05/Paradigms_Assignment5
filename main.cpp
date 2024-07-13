#include <iostream>
#include <string>
#include <cctype> // for isxdigit and isspace
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

bool isNumber(string input) {
    for (int i=0; i < input.length(); i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

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
    if (isNumber(token)) {
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

string calculate(vector<string> postFix) {
    stack<string> s;
    int result = 0;
    for (int i=0; i < postFix.size(); i++) {
        string element = postFix[i];
        if (isNumber(element)) s.push(element);
        else {
            int num1 = stoi(s.top());
            s.pop();
            int num2 = stoi(s.top());
            s.pop();

            if (element == "+") result = num1 + num2;
            else if (element == "*") result = num1 * num2;
            else if (element == "/") result = num2 / num1;
            else if (element == "-") result = num2 - num1;
            s.push(std::to_string(result));
        }

    }

    return s.top();
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

    cout << "Calculation: " << endl;
    string result = calculate(postfix);
    cout << result;
    return 0;
}
