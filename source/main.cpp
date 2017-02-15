#include <iostream>
#include "CNFExpression.hpp"
#include "DPLLTester.hpp"

int main() {

    while (true) {
        std::string expr;
        std::getline(std::cin, expr);

        if (std::cin.eof()) { break; }

        if (expr.length() == 0) continue;

        auto cnf = CNFExpression(expr);
        if (!cnf.isValid()) {
            std::cout << "Invalid CNF\n";
        } else {
            bool t = DPLLTest(cnf);
            std::cout << (t ? "Satisfiable\n" : "Not satisfiable\n");
        }
    }

    return 0;
}