#include <iostream>
#include <fstream>
#include "CNFExpression.hpp"
#include "DPLLTester.hpp"

int main() {
    
    auto cnf = CNFExpression(std::cin);

    bool t = DPLLTest(cnf);
    std::cout << (t ? "Satisfiable\n" : "Not satisfiable\n");

    return 0;
}