
// 5.) Create an advanced calculator in C++ that: Parses mathematical expressions entered as strings
// (e.g., "3 + 5 * (2 - 4)").
// • Supports basic operations (+, -, *, /) and parentheses for precedence.
// • Handles invalid inputs gracefully with proper error messages.
// • Demonstrates the calculator with a series of test cases.
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <stdexcept>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int applyOp(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw std::invalid_argument("Invalid operator");
    }
}

int evaluate(const std::string& expression) {
    std::stack<int> values;
    std::stack<char> ops;
    size_t i = 0;

    while (i < expression.size()) {
        if (expression[i] == ' ') {
            ++i;
            continue;
        }
        
        if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.size() && isdigit(expression[i])) {
                val = val * 10 + (expression[i] - '0');
                ++i;
            }
            values.push(val);
        }
        
        else if (expression[i] == '(') {
            ops.push('(');
            ++i;
        }
        
        else if (expression[i] == ')') {
            while (ops.top() != '(') {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.pop();
            ++i;
        }
        
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top(); values.pop();
                int val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
            ++i;
        }
    }

    while (!ops.empty()) {
        int val2 = values.top(); values.pop();
        int val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }
    
    return values.top();
}

int main() {
    std::string expression = "3 + 5 * (2 - 4)";
    try {
        std::cout << "Result: " << evaluate(expression) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}

