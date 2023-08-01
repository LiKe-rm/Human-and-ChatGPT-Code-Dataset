#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <stdio.h>
#include "muParser.h"

using namespace std;
using namespace mu;

double Mega(const double& v) { return v * 1e-6; }
double Milli(const double& v) { return v * 1e-3; }
double Rnd(const double& v) { return rand() / (double)RAND_MAX * v; }
double Add(const double& v1, const double& v2) { return v1 + v2; }

void SelfTest() {
    cout << "Supported functions and operators:" << endl;
    cout << "\t- Functions: sin, cos, tan, asin, acos, atan, log, log10, exp, sqrt" << endl;
    cout << "\t- Operators: +, -, *, /, %, ^" << endl;
    cout << "\t- Constants: pi (M_PI), e (M_E)" << endl;
    cout << "\t- Custom operators: Mega (unary), Milli (unary), Rnd (unary), Add (binary)" << endl;
}

void DumpUsedVariables(const Parser& parser) {
    cout << "Variables used: ";
    const auto& usedVars = parser.GetUsedVar();
    for (const auto& var : usedVars) {
        cout << var << " ";
    }
    cout << endl;
}

double Calc() {
    Parser parser;
    char expr[1024];
    cout << "Enter expression: ";
    fgets(expr, 1024, stdin);
    if (!parser.SetExpr(expr)) {
        cout << "Failed to set expression: " << parser.GetErrorMsg() << endl;
        return 0;
    }
    DumpUsedVariables(parser);
    return parser.Eval();
}

int main() {
    try {
        SelfTest();
        srand(time(NULL));
        cout << "Result: " << Calc() << endl;
    } catch (const Parser::exception_type& e) {
        cout << "Parser exception: " << e.GetMsg() << endl;
    }
    return 0;
}
