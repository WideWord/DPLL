#include "CNFExpression.hpp"
#include <sstream>

CNFExpression::CNFExpression(const std::string& string) {
    std::stringstream in(string);

    disjunctions.emplace_back();

    bool inverted = false;

    while (true) {
        char inp;
        in >> inp;
        if (in.eof()) break;

        if (inp == ' ' || inp == '\n') {
            continue;
        } else if (inp == '*') {

            if (inverted || disjunctions.back().empty()) {
                _isValid = false;
                return;
            }
            disjunctions.emplace_back();
        } else if (inp == '!') {
            if (inverted) {
                _isValid = false;
                return;
            }
            inverted = true;
        } else if (inp >= 'a' && inp<= 'z') {
            Variable var;
            var.name = inp;
            var.inverted = inverted;
            inverted = false;
            disjunctions.back().push_back(var);
        } else {
            _isValid = false;
            return;
        }
    }

    if (disjunctions.back().empty()) {
        _isValid = false;
    } else {
        _isValid = true;
    }
}

CNFExpression::CNFExpression() {
    _isValid = true;
}