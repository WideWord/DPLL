#include "CNFExpression.hpp"
#include <istream>
#include <sstream>
#include <iostream>

int varsCount;
uint disjunctionsCount;

const ushort HAS_NONE = 0;
const ushort HAS_ID = 1;
const ushort HAS_NOT = 2;
const ushort HAS_BOTH = HAS_NOT | HAS_ID;

Disjunction::Disjunction() {
    active = true;
}

void Disjunction::add(int var) {
    vars.insert(var);
}

void Disjunction::remove(int var) {
    vars.erase(var);
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

void CNFExpression::add(uint di, int var) {
    disjunctions[di].add(var);
    varsToDisjunctions[var+varsCount].insert(di);
    varsPerDisjunction[di]++;
}

void CNFExpression::remove(uint di, int var) {
    disjunctions[di].remove(var);
    varsToDisjunctions[var+varsCount].erase(di);
    varsPerDisjunction[di]--;
}

std::unordered_set<uint> CNFExpression::getDisjunctionIndexesByVar(int var) {
    return varsToDisjunctions[var+varsCount];
}

int CNFExpression::getPureVar() {
    for (uint i=1 ; i<=varsCount ; i++) {
        bool noIds = varsToDisjunctions[i+varsCount].empty();
        bool noNots = varsToDisjunctions[-i+varsCount].empty();

        if (!noIds && noNots) {
            return i;
        }

        if (!noNots && noIds) {
            return -i;
        }
    }

    return 0;
}

int CNFExpression::getUnitPropagateVar() {
    for (uint i=0 ; i<disjunctionsCount ; i++) {
        if (varsPerDisjunction[i] == 1) {
            return disjunctions[i].first();
        }
    }

    return 0;
}

void CNFExpression::activate(uint di) {
    disjunctions[di].active = true;
    activeCount++;
    varsPerDisjunction[di] = -varsPerDisjunction[di];
   
    for (auto& var : disjunctions[di].vars) {
        varsToDisjunctions[var+varsCount].insert(di);
    } 
}

void CNFExpression::deactivate(uint di) {
    disjunctions[di].active = false;
    activeCount--;
    varsPerDisjunction[di] = -varsPerDisjunction[di];   

    for (auto& var : disjunctions[di].vars) {
        varsToDisjunctions[var+varsCount].erase(di);
    } 
}

CNFExpression::CNFExpression(std::istream& in) {
    uint currentDisjunction = 0;

    while (true) {
        int ch;
        ch = in.get();

        if (in.eof()) break;


        if (ch == 'p') {
            std::string cnf;

            in >> cnf >> varsCount >> disjunctionsCount;
            varsPurity = new ushort[varsCount+1];
            
            disjunctions.reserve(disjunctionsCount);
            varsPerDisjunction = new int[disjunctionsCount]; 
            activeCount = disjunctionsCount;
            for (uint i=0 ; i<disjunctionsCount ; i++) {
                disjunctions.emplace_back();
                varsPerDisjunction[i] = 0;
            }
            varsToDisjunctions.reserve(varsCount*2+1);
            for (uint i=0 ; i<(varsCount*2+1) ; i++) {
                varsToDisjunctions.emplace_back();
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
                add(currentDisjunction, var);
            }
        }

    }
}

CNFExpression::CNFExpression() {}

