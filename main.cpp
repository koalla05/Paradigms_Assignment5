#include <iostream>
#include <string>
#include <cctype> // for isxdigit and isspace
#include <string.h>
#include <vector>
using namespace std;

class Token {
public:
    vector<std::string> array;

    void append(const std::string& b) {
        array.push_back(b);
    }

    string getTokens() const {
        string result;
        for (const auto& token : array) {
            result += token;
        }
        return result;
    }
};

vector<string> Tokenization(const string& input) {
    Token tokens;
    string b = "";
    for (size_t i = 0; i < input.length(); i++) {
        char ch = input[i];

        if (isxdigit(ch)) {
            b += ch;
        } else if (isspace(ch)) {
            if (!b.empty() && b != "-") {
                tokens.append(b);
                b.clear();
            }
        } else {
            if (!b.empty() && b != "-") {
                tokens.append(b);
                b.clear();
            }
            tokens.append(string(1, ch)); // Convert char to string and append
        }
    }

    if (!b.empty()) tokens.append(b);
    return tokens.array;
}

void output(const vector<string>& input) {
    cout << "Tokenization:" << endl;
    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << endl;
    }
}

int main() {
    string input;
    cout << "Enter: " << endl;
    getline(cin, input);
    vector<string> result = Tokenization(input);
    output(result);
    return 0;
}
