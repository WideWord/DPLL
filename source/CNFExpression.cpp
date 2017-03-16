#include "CNFExpression.hpp"
#include <istream>
#include <sstream>

CNFExpression::CNFExpression(std::istream& in) {

    disjunctions.emplace_front();

    while (true) {
        int ch;
        ch = in.get();

        if (in.eof()) break;

        if (ch == 'p' || ch == 'c') {
            do {
                ch = in.get();
                if (in.eof()) break;
            } while (ch != '\n');
        } else if ((ch >= '0' && ch <= '9') || ch == '-') {
            std::stringstream ss;
            do {
                ss << (char)ch;
                ch = in.get();
                if (in.eof()) break;
            } while (ch >= '0' && ch <= '9');

            int var;
            ss >> var;
            if (var == 0) {
                disjunctions.emplace_front();
            } else {
                disjunctions.front().push_front(var);
            }
        }

    }

    if (disjunctions.front().empty()) {
        disjunctions.pop_front();
    }
}

CNFExpression::CNFExpression() {}

