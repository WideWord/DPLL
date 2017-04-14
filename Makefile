
dpll: source/CNFExpression.cpp source/DPLLTester.cpp source/main.cpp source/DPLLTester.hpp source/CNFExpression.hpp
	g++ source/main.cpp source/CNFExpression.cpp source/DPLLTester.cpp -O3  --std=c++11 -o dpll
	
test: dpll
	./dpll fixtures/test.cnf
