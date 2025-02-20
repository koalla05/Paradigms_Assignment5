#include <iostream>
#include <string>
#include <cctype> // for isxdigit and isspace
#include <cmath>
#include <regex>
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
bool isAllLetters(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}


bool isOperator(string input) {
    if (input == "*" || input == "/" || input == "+" || input == "-" || input == "pow" || input == "abs" || input == "max" || input == "min" || input == "(" || input == ")") return true;
    return false;
}

bool isOperatorAr(string input) {
    if (input == "*" || input == "/" || input == "+" || input == "-" ) return true;
    return false;
}
bool isOperatorFunc(string input) {
    if (input == "pow" || input == "abs" || input == "max" || input == "min" ) return true;
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

        else if (ch == '(' && ( tokens.empty() || !isOperatorFunc(tokens.back()) )) {
            cout << "Error";
            exit(0);
        }

        else if (isOperator(string(1, ch))) {
            if (ch == '-' && !b.empty()) {
                tokens.push_back(b);
                tokens.push_back(string(1, ch));
                b.clear();
            }
            else if (ch == '-' && b.empty() && (tokens.empty() || isOperatorAr(tokens.back()) || tokens.back() == "(" || tokens.back() == "," )) {
                b += ch;
            }
            else if (ch == '-' && b.empty() && (isNumber(tokens.back())|| tokens.back() == ")")) {
                tokens.push_back(string(1, ch));
                b.clear();
            }
            else if (ch != '-' && !b.empty()) {
                tokens.push_back(b);
                tokens.push_back(string(1, ch));
                b.clear();
            }
            else if (isOperatorAr(tokens.back())) {
                cout << "Error";
                exit(0);
            }
            else {
                tokens.push_back(string(1, ch));
            }
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
            else {
                cout <<"Error";
                exit(0);
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
            else if (isAllLetters(element)) {
                cout << "Error";
                exit(0);
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
            s.push(to_string(result));
        }
    }
    if (s.size() > 1) {
        cout << "Error";
        exit(0);
    }
    return s.top();
}

void output(const vector<string>& input) {
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << " :: ";
    }
    cout << endl;
}

unordered_map<string, string> handleVar(const string& input, unordered_map<string, string> dict) {
    string b;

    size_t pos = input.find("=");
    if (pos == string::npos) {
        cout << "Error";
        exit(0);
    }

    string variable = input.substr(4, pos - 5);
    variable.erase(0, variable.find_first_not_of(' '));
    if (variable.size() < 4) {
        cout << "Error";
        exit(0);
    }

    string expression = input.substr(pos + 1);
    expression.erase(0, expression.find_first_not_of(' '));

    vector<string> tokens = tokenization(expression);
    vector<string> postfix = postFix(tokens);
    string result = calculate(postfix);

    dict[variable] = result;
    return dict;
}

tuple<unordered_map<string, string>, vector<string>> handleDef(const string& input, unordered_map<string, string> dict) {
    string b;

    size_t posF = input.find("{");
    if (posF == string::npos) {
        cout << "Error";
        exit(0);
    }
    size_t posF2 = input.find("}");
    if (posF2 == string::npos) {
        cout << "Error";
        exit(0);
    }

    string function = input.substr(4, posF - 4);
    function.erase(0, function.find_first_not_of(' '));

    string expression = input.substr(posF + 1);
    expression.erase(expression.find("}"), 1);

    size_t posBr = function.find('(');
    if (posBr == string::npos) {
        cout << "Error";
        exit(0);
    }

    size_t posBr2 = function.find(')');
    if (posBr2 == string::npos) {
        cout << "Error";
        exit(0);
    }

    string nameFunc = function.substr(0, posBr);
    if (nameFunc.size() < 4) {
        cout << "Error";
        exit(0);
    }
    dict[nameFunc] = expression;
    string parameters = function.substr(posBr + 1, posBr2 - posBr - 1);

    vector<string> argValues;
    string buffer;
    for (int i = 0; i< parameters.length(); i++) {
        if (parameters[i] != ','  && parameters[i] != ' ') buffer+= parameters[i];
        else {
            if (!buffer.empty()) argValues.push_back(buffer);
            buffer.clear();
        }
    }
    argValues.push_back(buffer);
    return make_tuple(dict, argValues);
}

int main() {
    string input;
    unordered_map<string, string> dictVar;
    unordered_map<string, string> dictFunc;
    vector<string> par;
    while (true) {
        getline(cin, input);

        if (input.substr(0, 4) == "var ") {
            dictVar =  handleVar(input, dictVar);
        } else if (input.substr(0, 4) == "def ") {

            tie(dictFunc, par) = handleDef(input, dictFunc);
        }
        else {
            string inputVar = input;
            for (const auto& pair : dictVar) {
                size_t pos = inputVar.find(pair.first);
                while (pos != string::npos) {
                    inputVar.replace(pos, pair.first.length(), pair.second);
                    pos = inputVar.find(pair.first, pos + pair.second.length());
                }
            }

            for (const auto& pair : dictFunc) {
                size_t pos = inputVar.find(pair.first);
                while (pos != string::npos) {
                    string parameters = inputVar.substr(inputVar.find('(') + 1, inputVar.find(')') - inputVar.find('(') - 1);
                    vector<string> argValues;
                    string b;
                    for (int i = 0; i< parameters.length(); i++) {
                        if (parameters[i] != ',' && parameters[i] != ' ') b += parameters[i];
                        else {
                            if (!b.empty()) argValues.push_back(b);
                            b.clear();
                        }
                    }
                    argValues.push_back(b);

                    unordered_map<string, string> paramMap;
                    for (int i = 0; i < par.size(); ++i) {
                        paramMap[par[i]] = argValues[i];
                    }

                    string funcExpr = dictFunc[pair.first];
                    for (const auto& param : paramMap) {
                        regex paramRegex("\\b" + param.first + "\\b");
                        funcExpr = regex_replace(funcExpr, paramRegex, param.second.c_str());
                    }
                    inputVar = funcExpr;
                    break;
                }
            }
            vector<string> tokens = tokenization(inputVar);
            vector<string> postfix = postFix(tokens);
            string result = calculate(postfix);
            cout << "Result: " << result << endl;
            break;
        }
    }
    return 0;
}
