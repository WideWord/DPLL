#pragma once

#include <vector>

class CNFExpression {
private:
    bool _isValid;
public:
    struct Variable {
        char name;
        bool inverted;
    };
    std::vector<std::vector<Variable>> disjunctions;

    CNFExpression();
    CNFExpression(const std::string& string);
    bool isValid() { return _isValid; }
};