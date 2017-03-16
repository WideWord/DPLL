#pragma once

#include <istream>
#include <list>

class CNFExpression {
public:
    std::list<std::list<int>> disjunctions;
    CNFExpression(std::istream& in);
    CNFExpression();
};