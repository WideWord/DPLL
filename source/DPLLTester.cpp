#include "DPLLTester.hpp"
#include "CNFExpression.hpp"
#include <algorithm>

bool SubDPLLTest(const CNFExpression& baseExpression, int var) {

    CNFExpression expression = baseExpression;
    auto& disjunctions = expression.disjunctions;

    auto prevIt = disjunctions.before_begin();
    for (auto it = disjunctions.begin(), itend = disjunctions.end(); it != itend; ++it) {
        auto& disjunction = *it;
        if (std::find(it->begin(), it->end(), var) != it->end()) {
            disjunctions.erase_after(prevIt);
        } else {
            it->remove(-var);
            if (it->empty()) {
                return false;
            }
            prevIt = it;
        }
    }

    if (disjunctions.empty()) {
        return true;
    }

    return DPLLTest(expression);
}

int DPLLUnitPropagate(const CNFExpression& cnf) {
    for (auto& d : cnf.disjunctions) {
        auto it = d.begin();
        ++it;
        if (it == d.end()) {
            return d.front();
        }
    }
    return 0;
}

bool DPLLTest(const CNFExpression& cnf) {

    int var = DPLLUnitPropagate(cnf);
    if (var != 0) {
        return SubDPLLTest(cnf, var);
    } else {
        var = cnf.disjunctions.front().front();
        if (SubDPLLTest(cnf, var)) {
            return true;
        } else {
            return SubDPLLTest(cnf, -var);
        }
    }


}