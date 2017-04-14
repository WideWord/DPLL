#include "CNFExpression.hpp"
#include <istream>
#include <sstream>
#include <iostream>

 Disjunction::Disjunction() {
    active = true;
}

void Disjunction::add(int var) {
    if (var > 0) {
        ids.insert(var);
    } else {
        nots.insert(-var);
    }
}

void Disjunction::remove(int var) {
    if (var > 0) {
        ids.erase(var);
    } else {
        nots.erase(-var);
    }
}

bool Disjunction::has(int var) {
    if (var > 0) {
        return ids.find(var) != ids.end();
    } else {
        return nots.find(-var) != nots.end();
    }
}

int CNFExpression::getVarToTest() {
    for (auto& d : disjunctions) {
        if (!d.active) {
            continue;
        }

        if (!d.ids.empty()) {
            return *d.ids.begin();
        }

        if (!d.nots.empty()) {
            return -(*d.nots.begin());
        }
    }

    return 0;
}

CNFExpression::CNFExpression(std::istream& in) {
    uint currentDisjunction = 0;

    while (true) {
        int ch;
        ch = in.get();

        if (in.eof()) break;


        if (ch == 'p') {
            std::string cnf;
            int vars, disjunctionsCount;

            in >> cnf >> vars >> disjunctionsCount;
            
            disjunctions.reserve(disjunctionsCount); 
            for (uint i=0 ; i<disjunctionsCount ; i++) {
                disjunctions.emplace_back();
            }
        } else if (ch == 'c' || ch == 'p') {
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
                currentDisjunction++;
            } else {
                disjunctions[currentDisjunction].add(var);
            }
        }

    }
}

CNFExpression::CNFExpression() {}

