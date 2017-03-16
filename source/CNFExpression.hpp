#pragma once

#include <istream>
#include <forward_list>

class CNFExpression {
public:
    std::forward_list<std::forward_list<int>> disjunctions;
    CNFExpression(std::istream& in);
    CNFExpression();
};