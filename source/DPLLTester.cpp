#include "DPLLTester.hpp"
#include "CNFExpression.hpp"
#include <algorithm>
#include <iostream>
#include <list>

std::list<int> disjunctionsToActivate;
std::list<int> disjunctionsToAddNotVar;

void restore(CNFExpression *expr, int var) {
    while(true) {
        int idx = disjunctionsToActivate.back();
        disjunctionsToActivate.pop_back();
        if (idx == -1) break;
        expr->disjunctions[idx].active = true;
    }

    while(true) {
        int idx = disjunctionsToAddNotVar.back();
        disjunctionsToAddNotVar.pop_back();
        if (idx == -1) break;
        expr->disjunctions[idx].add(-var);
    }
}

bool SubDPLLTest(CNFExpression *expr, int var) {
    int unactiveCount = 0;

    disjunctionsToActivate.push_back(-1);
    disjunctionsToAddNotVar.push_back(-1);

    for (uint i=0 ; i<expr->disjunctions.size() ; i++) {
        if (!expr->disjunctions[i].active) {
            unactiveCount++;
            continue;
        }

        if (expr->disjunctions[i].has(var)) {
            expr->disjunctions[i].active = false;
            disjunctionsToActivate.push_back(i);
            unactiveCount++;
        } else if (expr->disjunctions[i].has(-var)){
            expr->disjunctions[i].remove(-var);

            disjunctionsToAddNotVar.push_back(i);

            if (expr->disjunctions[i].empty()) {
                restore(expr, var);
                return false;
            }
        }
    }


    if (unactiveCount == expr->disjunctions.size()) {
        return true;
    }

    bool result = DPLLTest(expr);

    if (result) {
        return result;
    }

    restore(expr, var);

    return false;
}

int DPLLUnitPropagate(CNFExpression *cnf) {
    for (auto& d : cnf->disjunctions) {
        if (!d.active) {
            continue;
        }

        if (d.size() == 1) {
            return d.first();
        }
    }
    return 0;
}

bool DPLLTest(CNFExpression *cnf) {
    int var = DPLLUnitPropagate(cnf);

    if (var != 0) {
        return SubDPLLTest(cnf, var);
    } else {
        var = cnf->getVarToTest();

        if (SubDPLLTest(cnf, var)) {
            return true;
        } else {
            return SubDPLLTest(cnf, -var);
        }
    }


}