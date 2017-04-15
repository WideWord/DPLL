#pragma once

#include <istream>
#include <unordered_set>
#include <vector>
#include <unordered_map>

class Disjunction {
public:
	std::unordered_set<int> vars;
	bool active;

	void add(int);
	void remove(int);
	bool empty();
	int size();
	int first();

	Disjunction();	
};

class CNFExpression {
public:
    std::vector<Disjunction> disjunctions;
    std::vector<std::unordered_set<uint>> varsToDisjunctions;
    int* varsPerDisjunction;

    uint activeCount;

    int getVarToTest();
    int getPureVar();
    int getUnitPropagateVar();
    std::unordered_set<uint> getDisjunctionIndexesByVar(int);
    void activate(uint);
    void deactivate(uint);

    void add(uint, int);
    void remove(uint, int);

    CNFExpression(std::istream& in);
    CNFExpression();
};