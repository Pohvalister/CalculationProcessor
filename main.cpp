#include <QCoreApplication>

#include <iostream>

#include "solvers.h"

int main(int argc, char *argv[])
{

    if (argc != 2){
        std::cerr << "Incorrect argument, usage:" << argv[0] << " INPUT_FILE\n";
        return -1;
    }

    Solver* solver = new LongLongSolver();
    std::cout<<(solver->solve(argv[1])).toStdString();

    return 0;
}
