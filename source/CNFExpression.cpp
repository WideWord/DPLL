#include "CNFExpression.hpp"
#include <istream>
#include <sstream>
#include <iostream>

int varsCount;

const ushort HAS_NONE = 0;
const ushort HAS_ID = 1;
const ushort HAS_NOT = 2;
const ushort HAS_BOTH = HAS_NOT | HAS_ID;

Disjunction::Disjunction() {
    active = true;
    varsMap = (new bool[varsCount*2+1]) + varsCount;

    for (int i=1; i<=varsCount; i++) {
        varsMap[i] = false;
        varsMap[-i] = false;
    }
}

void Disjunction::add(int var) {
    vars.insert(var);
    varsMap[var] = true;
}

void Disjunction::remove(int var) {
    vars.erase(var);
    varsMap[var] = false;
}

bool Disjunction::has(int var) {
    return varsMap[var];
}

bool Disjunction::empty() {
    return vars.empty();
}

int Disjunction::size() {
    return vars.size();
}

int Disjunction::first() {
    return *(vars.begin());
}

int CNFExpression::getVarToTest() {
    for (int i=0 ; i<disjunctions.size() ; i++) {
        if (!disjunctions[i].active) {
            continue;
        }

        if (!disjunctions[i].vars.empty()) {
            return *disjunctions[i].vars.begin();
        }
    }

    return 0;
}

ushort *varsPurity;

int CNFExpression::getPureVar() {
    for (uint i=1 ; i<=varsCount ; i++) {
        varsPurity[i] = HAS_NONE;
    }

    for (int i=0 ; i<disjunctions.size() ; i++) {
        if (!disjunctions[i].active) {
            continue;
        }
        for (auto& f: disjunctions[i].vars) {
            if (f>0) {
                varsPurity[f] = varsPurity[f] | HAS_ID;
            } else {
                varsPurity[-f] = varsPurity[-f] | HAS_NOT;
            }
        }
    }

    for (uint i=1 ; i<=varsCount ; i++) {
        if (varsPurity[i] == HAS_ID) {
            return i;
        }

        if (varsPurity[i] == HAS_NOT) {
            return -i;
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
            int disjunctionsCount;

            in >> cnf >> varsCount >> disjunctionsCount;
            varsPurity = new ushort[varsCount+1];
            
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

