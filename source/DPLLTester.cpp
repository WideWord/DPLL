#include "DPLLTester.hpp"
#include "CNFExpression.hpp"

bool DPLLTestSub(const CNFExpression& cnf, char v, bool value) {


    CNFExpression copy = cnf;

    for (auto it = copy.disjunctions.begin(); it != copy.disjunctions.end();) {
        bool itIncremented = false;
        for (auto it2 = it->begin(); it2 != it->end();) {
            if (it2->name == v) {
                if (it2->inverted != value) {
                    it = copy.disjunctions.erase(it);
                    itIncremented = true;
                    break;
                } else {
                    if (it->size() == 1) {
                        return false;
                    } else {
                        it2 = it->erase(it2);
                    }
                }
            } else {
                ++it2;
            }
        }
        if (!itIncremented) {
            ++it;
        }
    }

    if (copy.disjunctions.empty()) return true;
    else return DPLLTest(copy);
}

bool DPLLTest(CNFExpression cnf) {



    char v = 0;
    bool skipPositive = false;
    bool skipNegative = false;


    bool positiveVars['z' - 'a' + 1];
    bool negativeVars['z' - 'a' + 1];

    for (int i = 0; i < 'z' - 'a' + 1; ++i) {
        positiveVars[i] = false;
        negativeVars[i] = false;
    }

    for (auto& d : cnf.disjunctions) {
        if (d.empty()) return false;
        for (auto& vr : d) {
            if (vr.inverted) {
                negativeVars[vr.name - 'a'] = true;
            } else {
                positiveVars[vr.name - 'a'] = true;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (positiveVars[ch - 'a'] != negativeVars[ch - 'a']) {
            for (auto it = cnf.disjunctions.begin(); it != cnf.disjunctions.end();) {
                bool itIncremented = false;
                for (auto& var : *it) {
                    if (var.name == ch) {
                        it = cnf.disjunctions.erase(it);
                        itIncremented = true;
                        break;
                    }
                }
                if (!itIncremented) {
                    ++it;
                }
            }
        }
    }

    if (cnf.disjunctions.empty()) return true;

    for (auto& d : cnf.disjunctions) {
        if (d.size() == 1) {
            v = d.front().name;
            skipPositive = d.front().inverted;
            skipNegative = !skipPositive;
        }
    }

    if (v == 0) v = cnf.disjunctions.front().front().name;

    if (!skipPositive) {
        if (DPLLTestSub(cnf, v, true)) return true;
    }
    if (!skipNegative) {
        if (DPLLTestSub(cnf, v, false)) return true;
    }

    return false;
}