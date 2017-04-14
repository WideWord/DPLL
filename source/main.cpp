#include <iostream>
#include <fstream>
#include "CNFExpression.hpp"
#include "DPLLTester.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void sigInt(int s){
    std::cout << "UNKNOWN\n";
    exit(0);
}

int main(int argc, char** argv) {

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = sigInt;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    if (argc < 2) {
        return 1;
    }

    std::ifstream in(argv[1]);

    auto cnf = CNFExpression(in);

    bool t = DPLLTest(cnf);
    std::cout << (t ? "SATISFIABLE\n" : "UNSATISFIABLE\n");

    return 0;
}