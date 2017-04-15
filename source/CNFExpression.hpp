#pragma once

#include <istream>
#include <unordered_set>
#include <vector>

class Disjunction {
public:
	std::unordered_set<int> vars;
	bool* idsMap;
	bool* notsMap;
	bool active;

	void add(int);
	void remove(int);
	bool has(int);
	bool empty();
	int size();
	int first();

	Disjunction();	
};

class CNFExpression {
public:
    std::vector<Disjunction> disjunctions;

    int getVarToTest();
    int getPureVar();

    CNFExpression(std::istream& in);
    CNFExpression();
};