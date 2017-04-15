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
        expr.activate(idx);
    }

    while(true) {
        int idx = disjunctionsToAddNotVar.top();
        disjunctionsToAddNotVar.pop();
        if (idx == -1) break;
        expr.add(idx, -var);
    }
}

bool SubDPLLTest(CNFExpression &expr, int var) {
    disjunctionsToActivate.push(-1);
    disjunctionsToAddNotVar.push(-1);
    
    for (const auto& di : expr.getDisjunctionIndexesByVar(-var)) {
        expr.remove(di, -var);

        disjunctionsToAddNotVar.push(di);

        if (expr.disjunctions[di].empty()) {
            restore(expr, var);
            return false;
        }  
    }

    for (const auto& di : expr.getDisjunctionIndexesByVar(var)) {
        expr.deactivate(di);
        disjunctionsToActivate.push(di);    
    }

    if (expr.activeCount == 0) {
        return true;
    }

    bool result = DPLLTest(expr);

    if (result) {
        return result;
    }

    restore(expr, var);

    return false;
}

bool DPLLTest(CNFExpression &cnf) {
    int var = cnf.getUnitPropagateVar();

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