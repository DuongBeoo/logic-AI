#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

using namespace std;

bool isValidExpression(const string &expression) {
    int balance = 0;
    for (char c : expression) {
        if (c == '(') {
            ++balance;
        } else if (c == ')') {
            --balance;
            if (balance < 0) return false;
        } else if (!isalnum(c) && c != ' ' && c != '¬' && c != '∧' && c != '∨' && c != '→' && c != '(' && c != ')') {
            return false;
        }
    }
    return balance == 0;
}

void extractVariables(const string &expression, vector<char> &variables) {
    for (char c : expression) {
        if (isalnum(c) && find(variables.begin(), variables.end(), c) == variables.end()) {
            variables.push_back(c);
        }
    }
    sort(variables.begin(), variables.end());
}

bool evaluateExpression(const string &expression, const map<char, bool> &values) {
    vector<bool> operandStack;
    vector<char> operatorStack;

    auto applyOperator = [](char op, bool left, bool right = false) {
        switch (op) {
            case '¬': return !left;
            case '∧': return left && right;
            case '∨': return left || right;
            case '→': return !left || right;
            default: throw invalid_argument("Toan tu khong hop le: " + string(1, op));
        }
    };

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (c == ' ') {
            continue;
        } else if (isalnum(c)) {
            if (values.find(c) == values.end()) {
                throw invalid_argument("Biến " + string(1, c) + " khong co gia tri.");
            }
            operandStack.push_back(values.at(c));
        } else if (c == '(') {
            operatorStack.push_back(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.back() != '(') {
                char op = operatorStack.back();
                operatorStack.pop_back();

                bool right = operandStack.back();
                operandStack.pop_back();

                if (op == '¬') {
                    operandStack.push_back(applyOperator(op, right));
                } else {
                    bool left = operandStack.back();
                    operandStack.pop_back();
                    operandStack.push_back(applyOperator(op, left, right));
                }
            }
            if (!operatorStack.empty() && operatorStack.back() == '(') {
                operatorStack.pop_back();
            }
        } else if (c == '¬' || c == '∧' || c == '∨' || c == '→') {
            while (!operatorStack.empty() && operatorStack.back() != '(') {
                char topOp = operatorStack.back();

                if ((c == '∧' || c == '∨' || c == '→') && (topOp == '¬' || topOp == '∧' || topOp == '∨' || topOp == '→')) {
                    operatorStack.pop_back();

                    bool right = operandStack.back();
                    operandStack.pop_back();

                    if (topOp == '¬') {
                        operandStack.push_back(applyOperator(topOp, right));
                    } else {
                        bool left = operandStack.back();
                        operandStack.pop_back();
                        operandStack.push_back(applyOperator(topOp, left, right));
                    }
                } else {
                    break;
                }
            }
            operatorStack.push_back(c);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.back();
        operatorStack.pop_back();

        bool right = operandStack.back();
        operandStack.pop_back();

        if (op == '¬') {
            operandStack.push_back(applyOperator(op, right));
        } else {
            bool left = operandStack.back();
            operandStack.pop_back();
            operandStack.push_back(applyOperator(op, left, right));
        }
    }

    if (operandStack.size() != 1) {
        throw invalid_argument("Bieu thuc khong hop le.");
    }

    return operandStack.back();
}

void generateTruthTable(const string &expression, const vector<char> &variables) {
    size_t numVariables = variables.size();
    size_t numRows = 1 << numVariables;

    for (char var : variables) {
        cout << var << " ";
    }
    cout << "Kết quả" << endl;

    for (size_t i = 0; i < numRows; ++i) {
        map<char, bool> values;

        for (size_t j = 0; j < numVariables; ++j) {
            values[variables[j]] = (i & (1 << (numVariables - j - 1))) != 0;
        }

        for (char var : variables) {
            cout << (values[var] ? "T " : "F ");
        }

        try {
            bool result = evaluateExpression(expression, values);
            cout << (result ? "T" : "F") << endl;
        } catch (const exception &e) {
            cout << "Loi!" << endl;
        }
    }
}

int main() {
    string expression;

    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Bieu thuc khong hop le." << endl;
        return 1;
    }

    vector<char> variables;
    extractVariables(expression, variables);

    generateTruthTable(expression, variables);

    return 0;
}
