#include "DPLLTester.hpp"
#include "CNFExpression.hpp"
#include <algorithm>
#include <iostream>
#include <list>
#include <stack>

std::stack<int> disjunctionsToActivate;
std::stack<int> disjunctionsToAddNotVar;

void restore(CNFExpression &expr, int var) {
    while(true) {
        int idx = disjunctionsToActivate.top();
        disjunctionsToActivate.pop();
        if (idx == -1) break;
        expr.disjunctions[idx].active = true;
    }

    while(true) {
        int idx = disjunctionsToAddNotVar.top();
        disjunctionsToAddNotVar.pop();
        if (idx == -1) break;
        expr.disjunctions[idx].add(-var);
    }
}

bool SubDPLLTest(CNFExpression &expr, int var) {
    int unactiveCount = 0;

    disjunctionsToActivate.push(-1);
    disjunctionsToAddNotVar.push(-1);

    for (uint i=0 ; i<expr.disjunctions.size() ; i++) {
        if (!expr.disjunctions[i].active) {
            unactiveCount++;
            continue;
        }

        if (expr.disjunctions[i].has(var)) {
            expr.disjunctions[i].active = false;
            disjunctionsToActivate.push(i);
            unactiveCount++;
        } else if (expr.disjunctions[i].has(-var)){
            expr.disjunctions[i].remove(-var);

            disjunctionsToAddNotVar.push(i);

            if (expr.disjunctions[i].empty()) {
                restore(expr, var);
                return false;
            }
        }
    }


    if (unactiveCount == expr.disjunctions.size()) {
        return true;
    }

    bool result = DPLLTest(expr);

    if (result) {
        return result;
    }

    restore(expr, var);

    return false;
}

int DPLLUnitPropagate(CNFExpression &cnf) {
    for (auto& d : cnf.disjunctions) {
        if (!d.active) {
            continue;
        }

        if (d.size() == 1) {
            return d.first();
        }
    }
    return 0;
}

bool DPLLTest(CNFExpression &cnf) {
    int var = DPLLUnitPropagate(cnf);

    if (var == 0) {
        var = cnf.getPureVar();
    }

    if (var != 0) {
        return SubDPLLTest(cnf, var);
    } else {
        var = cnf.getVarToTest();

        if (SubDPLLTest(cnf, var)) {
            return true;
        } else {
            return SubDPLLTest(cnf, -var);
        }
    }
}