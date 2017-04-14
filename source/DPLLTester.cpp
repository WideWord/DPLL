#include "DPLLTester.hpp"
#include "CNFExpression.hpp"
#include <algorithm>
#include <iostream>
#include <list>

bool SubDPLLTest(CNFExpression *expr, int var) {
    int unactiveCount = 0;

    std::list<uint> disjunctionsToActivate;
    std::list<uint> disjunctionsToAddNotVar;

    for (uint i=0 ; i<expr->disjunctions.size() ; i++) {
        auto& disjunction = expr->disjunctions[i];

        if (!disjunction.active) {
            unactiveCount++;
            continue;
        }

        if (disjunction.has(var)) {
            disjunction.active = false;
            disjunctionsToActivate.push_back(i);
            unactiveCount++;
        } else {
            disjunction.remove(-var);

            if (disjunction.ids.empty() && disjunction.nots.empty()) {
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

    for (auto& idx : disjunctionsToActivate) {
        expr->disjunctions[idx].active = true;
    }

    for (auto& idx : disjunctionsToAddNotVar) {
        expr->disjunctions[idx].add(-var);
    }

    return false;
}

int DPLLUnitPropagate(CNFExpression *cnf) {
    for (auto& d : cnf->disjunctions) {
        if (!d.active) {
            continue;
        }

        if (d.ids.size() == 1 && d.nots.size() == 0) {
            return *d.ids.begin();
        } else if (d.nots.size() == 1 && d.ids.size() == 0) {
            return -(*d.nots.begin());
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
        if (var == 0) {
            std::cout << "WTF" << std::endl;
        }

        if (SubDPLLTest(cnf, var)) {
            return true;
        } else {
            return SubDPLLTest(cnf, -var);
        }
    }


}