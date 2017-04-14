#pragma once

#include <istream>
#include <unordered_set>
#include <vector>

class Disjunction {
public:
	std::unordered_set<uint> ids;
	std::unordered_set<uint> nots;
	bool active;

	void add(int);
	void remove(int);
	bool has(int);

	Disjunction();	
};

class CNFExpression {
public:
    std::vector<Disjunction> disjunctions;

    int getVarToTest();

    CNFExpression(std::istream& in);
    CNFExpression();
};