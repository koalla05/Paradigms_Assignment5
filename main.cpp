#include <iostream>
#include <string>
#include <cctype> // for isxdigit and isspace
#include <cmath>
#include <sstream>
#include <stack>
#include <string.h>
#include <unordered_map>
#include <vector>
using namespace std;

bool isNumber(const string& input) {
    if (input.size() == 1 && !isdigit(input[0])) return false;
    if (!isdigit(input[0]) && input[0] != '-' ) return false;
    for (int i = 1; i < input.length(); ++i) {
        if (!isdigit(input[i]) && i!=0) return false;
    }
    return true;
}

bool isOperator(string input) {
    if (input == "*" || input == "/" || input == "*" || input == "-" || input == "pow" || input == "abs" || input == "max" || input == "min" || input == "(" || input == ")") return true;
    return false;
}

int priority(const string& op) {
    if (op == "(") return -1;

    if (op == "+") return 0;

    if (op == "-") return 0;

    if (op == "*") return 1;

    if (op == "/") return 1;

    if (op == "pow") return 2;

    if (op == "abs") return 2;

    if (op == "max") return 2;

    if (op == "min") return 2;

    return 100;
}


vector<string> tokenization(const string& input) {
    vector<string> tokens;
    string b;
    for (auto i = 0; i < input.length(); i++) {
        char ch = input[i];

        if (isxdigit(ch)) {
            b += ch;

        }
        else if (ch == ' ' && b != "-") {
            if (!b.empty()) {
                tokens.push_back(b);
                b.clear();
            }
        }
        else if (isOperator(string(1, ch)) && ch != '-' && !b.empty()) {
            tokens.push_back(b);
            tokens.push_back(string(1, ch));
            b.clear();
        }
        else if (isOperator(string(1, ch)) && ch == '-' && !b.empty()) {
            tokens.push_back(b);
            tokens.push_back(string(1, ch));
            b.clear();
        }
        else if (isOperator(string(1, ch)) && ch == '-' && b.empty() && (isNumber(tokens.back())|| tokens.back() == ")")) {
            tokens.push_back(string(1, ch));
            b.clear();
        }
        else if (isOperator(string(1, ch)) && ch == '-' && b.empty()) {
            b += ch;
        }
        else if (isalpha(ch)) {
            if (ch == 'p') b += ch;
            else if (ch == 'o' && !b.empty() && b.back() == 'p') b += ch;
            else if (ch == 'w' && !b.empty() && b.back() == 'o') {
                b += ch;
                tokens.push_back(b);
                b.clear();
            } else if (ch == 'm') b += ch;
            else if (ch == 'a' && !b.empty() && b.back() == 'm') b += ch;
            else if (ch == 'x' && !b.empty() && b.back() == 'a') {
                b += ch;
                tokens.push_back(b);
                b.clear();
            } else if (ch == 'i' && !b.empty() && b.back() == 'm') b += ch;
            else if (ch == 'n' && !b.empty() && b.back() == 'i') {
                b += ch;
                tokens.push_back(b);
                b.clear();
            } else if (ch == 'a') b += ch;
            else if (ch == 'b' && !b.empty() && b.back() == 'a') b += ch;
            else if (ch == 's' && !b.empty() && b.back() == 'b') {
                b += ch;
                tokens.push_back(b);
                b.clear();
            }
        } else {
            if (!b.empty() && b != "-") {
                tokens.push_back(b);
                b.clear();
            }
            if (ch != ' ') tokens.push_back(string(1, ch));
        }
    }

    if (!b.empty()) tokens.push_back(b);
    return tokens;
}


void processToken(string token, vector<string>& postFix, stack<string>& opStack) {
    if (isNumber(token)) {
        postFix.push_back(token);
    }

    else if (token == "(") opStack.push(token);
    else if (token == ")") {
        string op = opStack.top();
        opStack.pop();
        while (op != "(") {
            postFix.push_back(op);
            op = opStack.top();
            opStack.pop();
        }
        if (opStack.top() != "abs") {
            postFix.push_back(opStack.top());
            opStack.pop();
        }
    }
    else if (token == ",") {
        string op = opStack.top();
        while (op != "(") {
            postFix.push_back(op);
            opStack.pop();
            op = opStack.top();
        }
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
            if (element == "pow") {
                int num1 = stoi(s.top());
                s.pop();
                int num2 = stoi(s.top());
                s.pop();
                result = pow(num2, num1);
            }
            else if (element == "max") {
                int num1 = stoi(s.top());
                s.pop();
                int num2 = stoi(s.top());
                s.pop();
                result = max(num1, num2);
            }
            else if (element == "min") {
                int num1 = stoi(s.top());
                s.pop();
                int num2 = stoi(s.top());
                s.pop();
                result = min(num1, num2);
            }
            else if (element == "abs") {
                int num1 = stoi(s.top());
                s.pop();
                result = abs(num1);
            }
            else {
                int num1 = stoi(s.top());
                s.pop();
                int num2 = stoi(s.top());
                s.pop();

                if (element == "+") result = num1 + num2;
                else if (element == "*") result = num1 * num2;
                else if (element == "/") result = num2 / num1;
                else if (element == "-") result = num2 - num1;
            }
            s.push(std::to_string(result));
        }

    }

    return s.top();
}

void output(const vector<string>& input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << " :: ";
    }
    cout << endl;
}

tuple<unordered_map<string, string>, string> findExpressionVar(const string& input) {
    string b;
    unordered_map<string, string> dict;

    size_t pos = input.find("=");

    string variable = input.substr(4, pos - 5);
    variable.erase(0, variable.find_first_not_of(' '));

    string expression = input.substr(pos + 1);
    expression.erase(0, expression.find_first_not_of(' '));

    vector<string> tokens = tokenization(expression);
    // cout << "Tokenization:" << endl;
    // output(tokens);

    vector<string> postfix = postFix(tokens);
    // cout << "PostFix: " << endl;
    // output(postfix);

    // cout << "Calculation: " << endl;
    string result = calculate(postfix);
    cout << result << endl;

    dict[variable] = result;
    return make_tuple(dict, variable);
}

int main() {
    string input;
    string inputVar;
    getline(cin, input);
    if (input.substr(0, 4) == "var ") {
        unordered_map<string, string> dict;
        string var;
        tie(dict, var) = findExpressionVar(input);

        getline(cin, inputVar);

        size_t pos = inputVar.find(var);
        if (pos != string::npos) {
            inputVar.replace(pos, var.length(), dict[var]);
        } else {
            cout << "Variable '" << var << "' not found in input." << endl;
        }
    }

    input = inputVar;
    vector<string> tokens = tokenization(input);
    // cout << "Tokenization:" << endl;
    // output(tokens);

    vector<string> postfix = postFix(tokens);
    // cout << "PostFix: " << endl;
    // output(postfix);

    // cout << "Calculation: " << endl;
    string result = calculate(postfix);
    cout << result;

    return 0;
}
