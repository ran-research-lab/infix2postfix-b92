#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include <stack>
#include <iostream>

using namespace std;

// Returns true if character is a digit
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

// Returns true if character is a + or a *
bool isOperator(char c) {
    return (c == '+' || c == '*');
}


// Returns true if opA has lower precedence than opB
// Notice that if both are + then it returns false
bool hasLowerPrecedence(char opA, char opB) {
    return (opA == '+' && opB == '*');
}

// Returns true if c is a left parenthesis
bool isLeftParenthesis(char c) {
    return c == '(';
}

// Returns true if c is a right parenthesis
bool isRightParenthesis(char c) {
    return c == ')';
}

// Given the integers a and b and a character
// that is either + or *, returns the result of the
// corresponding operation
int doOperation(int a, int b, char oper) {
    if (oper == '+' ) return a + b;
    else              return a * b;
}


// Given st, a non empty, valid infix expression that
// contains only digits, spaces and operators + or *,
// returns the equivalent postfix expression.

string infix2Postfix(const string &st) {
    stack<char> S;
    string res;
    for (auto c: st) {
        if (c == ' ') {}
        else if (isDigit(c)) {
            res = res + c + " ";
        }
        else if (isLeftParenthesis(c)) {
            S.push(c);
        }
        else if (isRightParenthesis(c)) {
            // pop out of the stack until the corresponding parenthesis is found
            while(!isLeftParenthesis( S.top() ) ) {
                res = res + S.top() + " ";
                S.pop();
            }
            S.pop();
        }
        else {
            // pop out of the stack until the top is either a left parenthesis or
            // an operator that has less precedence than c
            while(!S.empty() && !isLeftParenthesis(c) && hasLowerPrecedence(c, S.top())) {
                res = res + S.top() + " ";
                S.pop();
            }
            S.push(c);
        }
    }
    while( !S.empty() ) {
        res = res + S.top() + " ";
        S.pop();
    }
    return res;
}


// Test cases for the function evalPostfix

TEST_CASE( "evalPostfix", "[evalPostfix]" ) {
    CHECK(infix2Postfix("9 + 5") == "9 5 + ");
    CHECK(infix2Postfix("9 + 5 * 3") == "9 5 3 * + ");
    CHECK(infix2Postfix("(9 + 5) * 3") == "9 5 + 3 * ");
    CHECK(infix2Postfix("5 + (6 + 9 * 8) * 7") == "5 6 9 8 * + 7 * + ");
}